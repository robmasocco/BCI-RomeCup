#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>

#include "BCI_NeuroSerial.h"

extern double amplitudes[CHANNELS][BINS];

//extern double lim_eight;
extern double lim_ten;
extern double lim_eleven;
extern double lim_thirteen;

double unifiedCh[BINS];

/* Fa la media aritmetica tra i due canali dei valori relativi ad ogni
 * frequenza, salvandoli in unifiedCh.
 */
void mergeChannels(void) {
	for (int i = 0; i < BINS; i++) {
		if (amplitudes[0][i] > amplitudes[1][i])
		    unifiedCh[i] = amplitudes[0][i];
		else
            unifiedCh[i] = amplitudes[1][i];
	}
}

/*  Unica funzione che restituisce -1 (sx), 0 (centro) o 1 (dx).  */
int control(void) {

	mergeChannels();

	// DEBUG
	//printf("8 Hz = %g\n", unifiedCh[0]);
    printf("10 Hz = %g\n", unifiedCh[1]);
    printf("11 Hz = %g\n", unifiedCh[2]);
    printf("13 Hz = %g\n", unifiedCh[3]);

	//if ((unifiedCh[0] >= lim_eight) && (unifiedCh[1] >= lim_ten)) {
    if (unifiedCh[1] >= lim_ten) {
	    printf("SLEEP\n");
        return 0;

    } else {
		if (unifiedCh[2] > unifiedCh[3]) {
			if (unifiedCh[2] < lim_eleven) {
			    printf("11 NE\n");
                return 0;
            } else {
                return -1;
            }
		} else {
			if (unifiedCh[3] < lim_thirteen) {
			    printf("13 NE\n");
                return 0;
            } else {
                return 1;
            }
		}
	}

}
