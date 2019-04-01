#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <complex.h>
#include <fftw3.h>
#include <bcm2835.h>

#include "BCI_NeuroSerial.h"

extern fftw_plan plans[CHANNELS];
extern fftw_complex *fftValues[CHANNELS];

extern unsigned char tempSamples[CHANNELS][NSAMPLES][3];
extern double *fftSamples[CHANNELS];

double rawSamples[CHANNELS][NSAMPLES];
double amplitudes[CHANNELS][BINS];

extern sem_t fftLocks[CHANNELS][2];
extern sem_t dataLocks[CHANNELS][2];

double convertBit(const unsigned char *bytes, int nByte, int enob, int invert);

/* Band-pass numeric filter data. */
#ifdef BANDPASS
__thread double x[4], xn[4];
void filtering(void);
#endif

__thread int chanIndex;

extern sigset_t workerSet;

extern __thread void (*closeRoutine)(void);

/* Functions in this file. */
void *fftWorker(void *index);
void fftWorkerTermination(void);

/* Thread that processes samples from a channel. */
void *fftWorker(void *index) {
    chanIndex = (int)index;
    closeRoutine = fftWorkerTermination;
    pthread_sigmask(SIG_SETMASK, &workerSet, NULL);

#ifdef BANDPASS
    // Reset filter states.
    x[0] = 0.0;
    x[1] = 0.0;
    x[2] = 0.0;
    x[3] = 0.0;
#endif

    // Process sampled data.
    for (;;) {
        // Wait for new data.
        sem_wait(&(fftLocks[chanIndex][0]));
        // Copy data from temporary storage.
        for (int i = 0; i < NSAMPLES; i++)

#ifdef BANDPASS
            rawSamples[chanIndex][i] = convertBit(tempSamples[chanIndex][i],
                                                  3, ENOB, 1);
#else
            fftSamples[chanIndex][i] = convertBit(tempSamples[chanIndex][i],
                                                  3, ENOB, 1);
#endif

        // Restart sampling.
        sem_post(&(fftLocks[chanIndex][1]));

#ifdef BANDPASS
        // Apply filtering to current sampling.
        filtering();
#endif

        // Do the FFT.
        fftw_execute(plans[chanIndex]);
        // Acquire channel with printer.
        sem_wait(&(dataLocks[chanIndex][0]));
        // Compute normalized amplitude spectrum for this channel.
        // 8 Hz.
        amplitudes[chanIndex][0] = cabs(fftValues[chanIndex][16]) /
                                   (double)NSAMPLES;
        // 10 Hz.
        amplitudes[chanIndex][1] = cabs(fftValues[chanIndex][20]) /
                                   (double)NSAMPLES;
        // 11 Hz.
        amplitudes[chanIndex][2] = cabs(fftValues[chanIndex][22]) /
                                   (double)NSAMPLES;
        // 13 Hz.
        amplitudes[chanIndex][3] = cabs(fftValues[chanIndex][26]) /
                                   (double)NSAMPLES;
        // 22 Hz.
        amplitudes[chanIndex][4] = cabs(fftValues[chanIndex][44]) /
                                   (double)NSAMPLES;
        // 26 Hz.
        amplitudes[chanIndex][5] = cabs(fftValues[chanIndex][52]) /
                                   (double)NSAMPLES;
        // Notify whoever needs the data.
        sem_post(&(dataLocks[chanIndex][1]));
    }
}

/* Termination procedure for FFT worker thread. */
void fftWorkerTermination(void) {
    pthread_exit(NULL);
}
