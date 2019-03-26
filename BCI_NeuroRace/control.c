// Includete quello che vi serve.

#include "BCI_NeuroRace.h"

// Array ordinato per canali e frequenze rispettivamente.
// Contiene le ampiezze a 1 sec.
// Le frequenze sono rispettivamente 8, 10, 11, 13, 22 e 26 Hz (BINS = 6).
extern double amplitudes[CHANNELS][BINS];

// Unica funzione che restituisce -1 (sx), 0 (centro) o 1 (dx).
