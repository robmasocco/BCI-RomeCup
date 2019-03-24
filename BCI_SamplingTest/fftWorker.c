#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <complex.h>
#include <fftw3.h>
#include <bcm2835.h>

#include "BCI_SamplingTest.h"

extern fftw_plan plans[CHANNELS];
extern fftw_complex *fftValues[CHANNELS];

extern unsigned char tempSamples[CHANNELS][NSAMPLES][3];
extern double *fftSamples[CHANNELS];

double rawSamples[CHANNELS][NSAMPLES];
double amplitudes[CHANNELS][FFTSAMPLES];

extern sem_t fftLocks[CHANNELS][2];
extern sem_t printerLocks[CHANNELS][2];

double convertBit(const unsigned char *bytes, int nByte, int enob, int invert);

#ifdef BANDPASS
__thread double x[4], xn[4];
void filtering(void);
#endif

__thread int chanIndex;

/* Thread that processes samples from a channel. */
void *fftWorker(void *index) {
    chanIndex = (int)index;

#ifdef BANDPASS
    // Reset filter states.
    x[0] = 0.0;
    x[1] = 0.0;
    x[2] = 0.0;
    x[3] = 0.0;
    // Set up the filter.
    for (int f = 0; f < FILTER_RUNS; f++) {
        sem_wait(&(fftLocks[chanIndex][0]));  // Wait for data.
        for (int i = 0; i < NSAMPLES; i++)
            rawSamples[chanIndex][i] = convertBit(tempSamples[chanIndex][i],
                                                  3, ENOB, 1);
        sem_post(&(fftLocks[chanIndex][1]));  // Restart sampling.
        filtering();
    }
#endif

    // Process the acquisitions.
    for (int a = 0; a < ACQUISITIONS; a++) {
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
        sem_wait(&(printerLocks[chanIndex][0]));
        // Compute normalized amplitude spectrum for this channel.
        for (int j = 0; j < FFTSAMPLES; j++)
            amplitudes[chanIndex][j] = cabs(fftValues[chanIndex][j]) /
                                       (double)NSAMPLES;
        // Notify the printer.
        sem_post(&(printerLocks[chanIndex][1]));
    }
    pthread_exit(NULL);
}
