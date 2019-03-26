#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#include "BCI_NeuroRace.h"
#include "CommProtocol.h"

extern sigset_t workerSet;

extern __thread void (*closeRoutine)(void);

extern sem_t startCalibration, endCalibration;
extern sem_t dataLocks[CHANNELS][2];

extern pthread_mutex_t controlLock;

extern int gameSock;

extern double amplitudes[CHANNELS][BINS];

/* Data acquired for a calibration run. */
double calibrationData[CHANNELS][CALIBRATION_SECONDS][BINS];

/* Functions for the calibration phases. */
void (*calibrationPhases[CALIBRATION_RUNS])(void);

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
    char msg = END_CALIBRATION;
    ssize_t recvRes, sendRes;
    // Wait for calibration start signal.
    sem_wait(&startCalibration);

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
    sendRes = send(gameSock, &msg, 1, MSG_NOSIGNAL);
    if (sendRes != 1) {
        fprintf(stderr, "ERROR: Failed to send message on socket.\n");
        perror("send");
        raise(SIGTERM);
    }
#endif

    // Do the calibration phases.
    for (int i = 0; i < CALIBRATION_RUNS; i++) {
        acquireData();
        calibrationPhases[i]();
        sendRes = send(gameSock, &msg, 1, MSG_NOSIGNAL);
        if (sendRes != 1) {
            fprintf(stderr, "ERROR: Failed to send message on socket.\n");
            perror("send");
            raise(SIGTERM);
        }
    }
    // Send calibration end signal.
    sem_post(&endCalibration);

    // NORMAL CALIBRATION LOOP //
    for (;;) {
        // Wait for calibration start message.
        recvRes = recv(gameSock, &msg, 1, 0);
        if (recvRes == 0) {
            raise(SIGTERM);
        } else if (recvRes == -1) {
            fprintf(stderr, "ERROR: Failed to receive message on socket.\n");
            perror("recv");
            raise(SIGTERM);
        }
        // Acquire data processing right.
        pthread_mutex_lock(&controlLock);
        // Do the calibration phases.
        for (int i = 0; i < CALIBRATION_RUNS; i++) {
            msg = END_CALIBRATION;
            acquireData();
            calibrationPhases[i]();
            sendRes = send(gameSock, &msg, 1, MSG_NOSIGNAL);
            if (sendRes != 1) {
                fprintf(stderr, "ERROR: Failed to send message on socket.\n");
                perror("send");
                raise(SIGTERM);
            }
        }
        // Release data processing right.
        pthread_mutex_unlock(&controlLock);
    }
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
