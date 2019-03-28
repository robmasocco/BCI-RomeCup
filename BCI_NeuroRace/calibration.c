#include <math.h>
#include "BCI_NeuroRace.h"

double lim_eight = HUGE_VAL;
double lim_ten = HUGE_VAL;
double lim_eleven = HUGE_VAL;
double lim_thirteen = HUGE_VAL;
double max_eleven = 0;
double max_thirteen = 0;


/* Data acquired for a calibration run. */
extern double calibrationData[CHANNELS][CALIBRATION_SECONDS][BINS];
// Prima dimensione: canali, 2.
// Seconda dimensione: secondi di acquisizione, 5.
// Terza dimensione: frequenze d'interesse, 6 (8, 10, 11, 13, 22, 26 Hz ordinate
// così).


void min(double A[][][], int j) {
	double m;
	for(int i = 0, i < 2, i++) {
		for(int t = 0; t < 5; t++) {
			if(A[i][t][j] < m)
				m = A[i][t][j];
		}
	}
	return m;
}


void max(double A[][][], int j) {
	double M;
	for(int i = 0, i < 2, i++) {
		for(int t = 0; t < 5; t++) {
			if(A[i][t][j] > M)
				M = A[i][t][j];
		}
	}
	return M;
}


void closedEyes() {
	lim_eight = min(calibrationData, 0);
	lim_ten = min(calibrationData, 1);
}


void ledSx() {
// 11 Hz
	lim_eleven = min(calibrationData, 2);
}


void ledDx() {
// 13 Hz
	lim_thirteen = min(calibrationData, 3);
}


void lookAtScreen() {
	max_eleven = max(calibrationData, 2);
	max_thirteen = max(calibrationData, 3);

	lim_eleven = (lim_eleven + max_eleven)/2.0;
	lim_thirteen = (lim_thirteen + max_thirteen)/2.0;
}