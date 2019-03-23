#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <fftw3.h>

#define SAMPLES 500

double amplitudes[(SAMPLES / 2) + 1];

fftw_plan plan;
double *fftSamples;
fftw_complex *fftValues;

FILE *dataFile, *outFile;

int main(void) {
    fftSamples = fftw_alloc_real(SAMPLES);
    dataFile = fopen("sample.txt", "r");
    for (int i = 0; i < SAMPLES; i++) {
        fscanf(dataFile, "%lg\t", fftSamples + i);
    }
    fclose(dataFile);
    fftValues = fftw_alloc_complex((SAMPLES / 2) + 1);
    plan = fftw_plan_dft_r2c_1d(SAMPLES, fftSamples, fftValues, FFTW_MEASURE);
    fftw_execute(plan);
    for (int j = 0; j < ((SAMPLES / 2) + 1); j++) {
        amplitudes[j] = cabs(fftValues[j] * (2.0 / SAMPLES));
    }
    outFile = fopen("out.txt", "w+");
    for (int k = 0; k < ((SAMPLES / 2) + 1); k++) {
        fprintf(outFile, "%lg\n", amplitudes[k]);
    }
    fclose(outFile);
    fftw_destroy_plan(plan);
    fftw_free(fftSamples);
    fftw_free(fftValues);
    exit(EXIT_SUCCESS);
}
