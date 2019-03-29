#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>

#include "BCI_NeuroRace.h"

// Array ordinato per canali e frequenze rispettivamente.
// Contiene le ampiezze a 1 sec.
// Le frequenze sono rispettivamente 8, 10, 11, 13, 22 e 26 Hz (BINS = 6).
extern double amplitudes[CHANNELS][BINS];

// Valori globali ottenuti dalla calibrazione.
extern double lim_eight;
extern double lim_ten;
extern double lim_eleven;
extern double lim_thirteen;

double unifiedCh[BINS];


/*  Fa la media aritmetica tra i due canali dei valori relativi ad ogni frequenza,
	salvandoli in unifiedCh.  */
void mergeChannels(void) {
	for (int i = 0; i < BINS; i++) {
		unifiedCh[i] = (amplitudes[0][i] + amplitudes[1][i])/2.0;
	}
}


/*  Unica funzione che restituisce -1 (sx), 0 (centro) o 1 (dx).  */
int control(void) {

	mergeChannels();

	if ((unifiedCh[0] < lim_eight) || (unifiedCh[1] < lim_ten))
		return 0;

	else {
		if (unifiedCh[2] > unifiedCh[3]) {
			if (unifiedCh[2] < lim_eleven)
				return 0;
			else 
				return -1;
		}
		else {
			if (unifiedCh[3] < lim_thirteen)
				return 0;
			else
				return 1;
		}
	}

}