#include "BCI_NeuroRace.h"

/* Data acquired for a calibration run. */
extern double calibrationData[CHANNELS][CALIBRATION_SECONDS][BINS];
// Prima dimensione: canali, 2.
// Seconda dimensione: secondi di acquisizione, 5.
// Terza dimensione: frequenze d'interesse, 6 (8, 10, 11, 13, 22, 26 ordinate
// così).

// Calibrazione divisa in fasi, una funzione per fase (?)
