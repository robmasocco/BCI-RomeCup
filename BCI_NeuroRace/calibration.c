#include <stdio.h>
#include <math.h>
#include "BCI_NeuroRace.h"

//double lim_eight = -1;
double lim_ten = -1;
double lim_eleven = HUGE_VAL;
double lim_thirteen = HUGE_VAL;
double max_eleven = 0;
double max_thirteen = 0;

/* Data acquired for a calibration run. */
extern double calibrationData[CHANNELS][CALIBRATION_SECONDS][BINS];

double min(double A[CHANNELS][CALIBRATION_SECONDS][BINS], int j) {
    double m = HUGE_VAL;
    for (int i = 0; i < CHANNELS; i++) {
        for (int t = 0; t < CALIBRATION_SECONDS; t++) {
            if (A[i][t][j] < m)
                m = A[i][t][j];
        }
    }
    return m;
}

double max(double A[CHANNELS][CALIBRATION_SECONDS][BINS], int j) {
    double M = -1;
    for (int i = 0; i < CHANNELS; i++) {
        for (int t = 0; t < CALIBRATION_SECONDS; t++) {
            if (A[i][t][j] > M)
                M = A[i][t][j];
        }
    }
    return M;
}

void closedEyes() {
    //double a;
    double b;
    //a = min(calibrationData, 0);
    b = min(calibrationData, 1);
    //if (a > lim_eight)
        //lim_eight = a;
    if (b > lim_ten)
        lim_ten = b;
    //printf("lim_eight = %g\n", lim_eight);
    printf("lim_ten = %g\n", lim_ten);
}

void ledSx() {
    // 11 Hz
    lim_eleven = min(calibrationData, 2);
    printf("lim_eleven = %g\n", lim_eleven);
}

void ledDx() {
    // 13 Hz
    lim_thirteen = min(calibrationData, 3);
    printf("lim_thirteen = %g\n", lim_thirteen);
}

void lookAtScreen() {
    max_eleven = max(calibrationData, 2);
    max_thirteen = max(calibrationData, 3);
    printf("max_eleven = %g\n", max_eleven);
    printf("max_thirteen = %g\n", max_thirteen);

    lim_eleven = (lim_eleven + max_eleven)/2.0;
    lim_thirteen = (lim_thirteen + max_thirteen)/2.0;
    printf("lim_eleven = %g\n", lim_eleven);
    printf("lim_thirteen = %g\n", lim_thirteen);
}
