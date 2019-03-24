#ifdef BANDPASS

#include "BCI_NeuroRace.h"

extern double rawSamples[CHANNELS][NSAMPLES];
extern double *fftSamples[CHANNELS];

extern __thread int chanIndex;

extern __thread double x[4], xn[4];

/* Band-pass filter [1 Hz, 50 Hz] for sampled input. */
void filtering(void) {
    for (int k = 0; k < NSAMPLES; k++) {
        // Compute states dynamic.
        xn[0] = (3.886817541733970 * x[0]) + (-2.833268425402735 * x[1]) +
                (1.836303920113719 * x[2]) + (-0.892888545537901 * x[3]);
        xn[1] = 2.0 * x[0];
        xn[2] = 1.0 * x[1];
        xn[3] = 0.5 * x[2];
        // Add input.
        xn[0] += (0.125 * rawSamples[chanIndex][k]);
        // Compute filter outputs.
        fftSamples[chanIndex][k] = (0.023755396766471 * x[0]) +
                                   (-0.012317935674329 * x[1]) +
                                   (-0.010997223801104 * x[2]) +
                                   (0.022874922184395 * x[3]);
        // Update states.
        x[0] = xn[0];
        x[1] = xn[1];
        x[2] = xn[2];
        x[3] = xn[3];
    }
}

#endif
