#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#include "BCI_SamplingTest.h"

extern sem_t printerLocks[CHANNELS][2];

extern double amplitudes[CHANNELS][FFTSAMPLES];

extern double *fftSamples[CHANNELS];

FILE *outFile, *outFile2;

void *printer(void *arg) {
    UNUSED(arg);
    // Open output file.
    outFile = fopen("samplingOut.txt", "w+");
    outFile2 = fopen("signal.txt", "w+");
    // Print sampling values.
    for (int k = 0; k < ACQUISITIONS; k++) {
        // Wait for new data.
        for (int i = 0; i < CHANNELS; i++)
            sem_wait(&(printerLocks[i][1]));
        // Print results in the files.
        // Print ADCs samples of current acquisition.
        for (int i = 0; i < CHANNELS; i++) {
            for (int j = 0; j < NSAMPLES; j++) {
                fprintf(outFile2, "%lg\t", fftSamples[i][j]);
            }
            fputc('\n', outFile2);
        }
        fprintf(outFile2, "\n\n");
        // Print amplitude spectrum of current acquisition.
        for (int i = 0; i < CHANNELS; i++) {
            for (int j = 0; j < FFTSAMPLES; j++) {
                fprintf(outFile, "%lg\t", amplitudes[i][j]);
            }
            fputc('\n', outFile);
        }
        fprintf(outFile, "\n\n");
        // Print results in the console.
        fprintf(stdout,  "Run %d: "
                         "8 Hz: (%lg, %lg) - "
                         "10 Hz: (%lg, %lg) - "
                         "11 Hz: (%lg, %lg) - "
                         "13 Hz: (%lg, %lg) - "
                         "22 Hz: (%lg, %lg) - "
                         "26 Hz: (%lg, %lg)\n",
                         k + 1,
                         amplitudes[0][16], amplitudes[1][16],
                         amplitudes[0][20], amplitudes[1][20],
                         amplitudes[0][22], amplitudes[1][22],
                         amplitudes[0][26], amplitudes[1][26],
                         amplitudes[0][44], amplitudes[1][44],
                         amplitudes[0][52], amplitudes[1][52]);
        // Release data channels.
        for (int i = 0; i < CHANNELS; i++)
            sem_post(&(printerLocks[i][0]));
    }
    fclose(outFile);
    fclose(outFile2);
    pthread_exit(NULL);
}
