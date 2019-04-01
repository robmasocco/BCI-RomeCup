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

extern sem_t dataLocks[CHANNELS][2];
extern sem_t startSampling, startCalibration;

/* Serial port data. */
char *serialPort = "/dev/serial0";
int serial;

/* Function to determine input for the game. */
int control(void);

/* Data of thread spawned by controller thread. */
pthread_t calibratorTID;
extern pthread_attr_t calibratorData;
void *calibrator(void *arg);

/* Functions in this file. */
void *controller(void *arg);
void controllerTermination(void);

/* Thread that processes signals and generates game input. */
void *controller(void *arg) {
    UNUSED(arg);
    pthread_sigmask(SIG_SETMASK, &workerSet, NULL);
    closeRoutine = controllerTermination;
    int controlRes;
    char msg;
    // Open serial port.
    serial = serialOpen(serialPort, SERIAL_BAUD);
    // Spawn calibrator thread.
    if (pthread_create(&calibratorTID, &calibratorData, calibrator, NULL)) {
        fprintf(stderr, "ERROR: Failed to spawn calibrator thread.\n");
        serialClose(serial);
        kill(procPID, SIGTERM);
    }
    // Start sampling.
    sem_post(&startSampling);
    // Start calibration.
    sem_post(&startCalibration);
    // Wait for calibration to end.
    if (pthread_join(calibratorTID, NULL)) {
        fprintf(stderr, "ERROR: Failed to join calibrator thread.\n");
        serialClose(serial);
        kill(procPID, SIGTERM);
    }
    // Control loop.
    for (;;) {
        // Wait for data to be ready.
        for (int i = 0; i < CHANNELS; i++)
            sem_wait(&(dataLocks[i][1]));
        // Compute control.
        controlRes = control();
        if (controlRes == -1) {
            msg = LEFT;
        } else if (controlRes == 1) {
            msg = RIGHT;
        } else msg = CENTER;
        // Release data channels.
        for (int i = 0; i < CHANNELS; i++)
            sem_post(&(dataLocks[i][0]));
        // Send control message over serial port.
        serialPutchar(serial, msg);
        printf("Sent control: '%c'.\n", msg);
    }
}

/* Termination procedure for controller thread. */
void controllerTermination(void) {
    serialClose(serial);
    pthread_exit(NULL);
}
