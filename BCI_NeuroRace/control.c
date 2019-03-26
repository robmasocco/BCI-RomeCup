#include "BCI_NeuroRace.h"

// Array ordinato per canali e frequenze. Contiene le ampiezze a 1 sec.
// Le frequenze sono rispettivamente 8, 10, 11, 13, 22 e 26 Hz.
extern double amplitudes[CHANNELS][BINS];

// Unica funzione che restituisce -1, 0 o 1.
