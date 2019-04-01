#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <wiringSerial.h>

#include "BCI_NeuroSerial.h"
#include "CommProtocol.h"

extern pid_t procPID;

extern sigset_t workerSet;

extern __thread void (*closeRoutine)(void);

extern sem_t startCalibration;
extern sem_t dataLocks[CHANNELS][2];

extern int serial;

extern double amplitudes[CHANNELS][BINS];

/* Data acquired for a calibration run. */
double calibrationData[CHANNELS][CALIBRATION_SECONDS][BINS];

/* Functions and data for the calibration phases. */
void closedEyes(void);
void ledSx(void);
void ledDx(void);
void lookAtScreen(void);
void (*calibrationPhases[CALIBRATION_RUNS])(void) = {closedEyes,
                                                     ledSx,
                                                     closedEyes,
                                                     ledDx,
                                                     closedEyes,
                                                     lookAtScreen,
                                                     closedEyes};
char *calibrationPrints[] = {"Chiudi gli occhi per 6 secondi.\n",
                             "Guarda il LED a sinistra per 6 secondi.\n",
                             "Chiudi gli occhi per 6 secondi.\n",
                             "Guarda il LED a destra per 6 secondi.\n",
                             "Chiudi gli occhi per 6 secondi.\n",
                             "Guarda lo schermo per 6 secondi.\n",
                             "Chiudi gli occhi per 6 secondi.\n"};

/* Functions in this file. */
void *calibrator(void *arg);
void calibratorTermination(void);
void acquireData(void);

/* Thread that calls a set of calibration routines for the system. */
void *calibrator(void *arg) {
    UNUSED(arg);
    pthread_sigmask(SIG_SETMASK, &workerSet, NULL);
    closeRoutine = calibratorTermination;
    memset(&calibrationData, 0, sizeof calibrationData);
    // Wait for internal calibration start signal.
    sem_wait(&startCalibration);
    printf("First calibration started.\n");

    // INITIAL CALIBRATION //

#ifdef BANDPASS
    // Zero phase: acquire some data to set up the filter.
    // Just make the FFT workers run pointlessly.
    for (int f = 0; f < FILTER_RUNS; f++) {
        for (int c = 0; c < CHANNELS; c++)
            sem_wait(&(dataLocks[c][1]));
        for (int c = 0; c < CHANNELS; c++)
            sem_post(&(dataLocks[c][0]));
    }
    printf("Filters setup completed.\n");
#else
    // Jump to phase one.
    sendRes = sendto(gameSock, &msg, 1, 0, (struct sockaddr *)&gameAddr,
            gameAddrLen);
    if (sendRes != 1) {
        fprintf(stderr, "ERROR: Failed to send message on socket.\n");
        perror("send");
        kill(procPID, SIGTERM);
    }
#endif

    // Do the calibration phases.
    for (int i = 0; i < CALIBRATION_RUNS; i++) {
        // Do the calibration step.
        printf("%s", calibrationPrints[i]);
        acquireData();
        calibrationPhases[i]();
        printf("Calibration phase %d done.\n", i + 1);
    }
    printf("Initial calibration completed.\n");
    pthread_exit(NULL);
}

/* Function to acquire and store data for a calibration phase. */
void acquireData(void) {
    for (int s = 0; s < CALIBRATION_SECONDS; s++) {
        // Wait for data to be ready.
        for (int c = 0; c < CHANNELS; c++)
            sem_wait(&(dataLocks[c][1]));
        // Copy data.
        for (int c = 0; c < CHANNELS; c++) {
            for (int b = 0; b < BINS; b++) {
                calibrationData[c][s][b] = amplitudes[c][b];
            }
        }
        // Release data channels.
        for (int c = 0; c < CHANNELS; c++)
            sem_post(&(dataLocks[c][0]));
    }
}

/* Termination procedure for calibrator thread. */
void calibratorTermination(void) {
    pthread_exit(NULL);
}
