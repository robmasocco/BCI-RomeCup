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

extern double convertBit(unsigned char *bytes, int nByte, int enob, int invert);

void filtering(void);

__thread double x[4], xn[4];
__thread int chanIndex;

void *fftWorker(void *index) {
    chanIndex = (int)index;
    // Reset filter states.
    /*x[0] = 0.0;
    x[1] = 0.0;
    x[2] = 0.0;
    x[3] = 0.0;*/
    /*x[4] = 0.0;
    x[5] = 0.0;
    x[6] = 0.0;
    x[7] = 0.0;*/
    // Set up the filter by acquiring and filtering a set of samples.
    /*sem_wait(&(fftLocks[chanIndex][0]));  // Wait for data.
    for (int i = 0; i < NSAMPLES; i++)
        rawSamples[chanIndex][i] = convertBit(tempSamples[chanIndex][i],
                                              3, ENOB, 1);
    sem_post(&(fftLocks[chanIndex][1]));  // Restart sampling.
    filtering();*/
    // Process the acquisitions.
    for (int a = 0; a < ACQUISITIONS; a++) {
        // Wait for new data.
        sem_wait(&(fftLocks[chanIndex][0]));
        // Copy data from temporary storage.
        for (int i = 0; i < NSAMPLES; i++)
            /*rawSamples[chanIndex][i] = convertBit(tempSamples[chanIndex][i],
                                                  3, ENOB, 1);*/
            fftSamples[chanIndex][i] = convertBit(tempSamples[chanIndex][i],
                                                  3, ENOB, 1);
        // Restart sampling.
        sem_post(&(fftLocks[chanIndex][1]));
        // Apply filtering to current sampling.
        //filtering();
        // Do the FFT.
        fftw_execute(plans[chanIndex]);
        // Acquire channel with printer.
        sem_wait(&(printerLocks[chanIndex][0]));
        // Compute amplitude spectrum for this channel.
        for (int j = 0; j < FFTSAMPLES; j++)
            amplitudes[chanIndex][j] = cabs(fftValues[chanIndex][j]);
        // Notify the printer.
        sem_post(&(printerLocks[chanIndex][1]));
    }
    pthread_exit(NULL);
}

void filtering(void) {
    for (int k = 0; k < NSAMPLES; k++) {
        // Compute states dynamic.
        xn[0] = (1.047972048879746 * x[0]) + (-0.753869378152208 * x[1]) +
                (0.521134146729929 * x[2]) + (-0.299899053931107 * x[3]);
        xn[1] = 1.0 * x[0];
        xn[2] = 0.5 * x[1];
        xn[3] = 0.25 * x[2];
        // Add input.
        xn[0] += (1.0 * rawSamples[chanIndex][k]);
        // Compute filter outputs.
        fftSamples[chanIndex][k] = (0.051926380144877 * x[0]) +
                                   (0.278557250291417 * x[1]) +
                                   (0.290157822447976 * x[2]) +
                                   (0.058040767908851 * x[3]);
        // Update states.
        x[0] = xn[0];
        x[1] = xn[1];
        x[2] = xn[2];
        x[3] = xn[3];
    }
}
