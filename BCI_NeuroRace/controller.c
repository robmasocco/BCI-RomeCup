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
#include <netinet/udp.h>
#include <arpa/inet.h>

#include "BCI_NeuroRace.h"
#include "CommProtocol.h"

extern pid_t procPID;

extern sigset_t workerSet;

extern __thread void (*closeRoutine)(void);

extern sem_t dataLocks[CHANNELS][2];
extern sem_t startSampling, startCalibration, endCalibration;

extern pthread_mutex_t controlLock;

/* Socket data. */
int gameSock;
int yes = 1;
struct sockaddr_in sockAddr, gameAddr, recvGameAddr;
socklen_t gameAddrLen, recvGameAddrLen;

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
    ssize_t recvRes, sendRes;
    // Open and configure socket.
    gameSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (gameSock < 0) {
        fprintf(stderr, "ERROR: Failed to open socket.\n");
        perror("socket");
        kill(procPID, SIGTERM);
    }
    if (setsockopt(gameSock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes)) {
        fprintf(stderr, "ERROR: Failed to configure socket.\n");
        perror("setsockopt");
        close(gameSock);
        kill(procPID, SIGTERM);
    }
    memset(&sockAddr, 0, sizeof sockAddr);
    memset(&gameAddr, 0, sizeof gameAddr);
    gameAddrLen = sizeof gameAddr;
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = (uint16_t)htons(GAME_PORT);
    inet_pton(AF_INET, PI_IP, &(sockAddr.sin_addr.s_addr));
    gameAddr.sin_family = AF_INET;
    gameAddr.sin_port = (uint16_t)htons(GAME_PORT);
    inet_pton(AF_INET, GAME_IP, &(gameAddr.sin_addr.s_addr));
    gameAddrLen = sizeof gameAddr;
    if (bind(gameSock, (struct sockaddr *)&sockAddr, sizeof sockAddr)) {
        fprintf(stderr, "ERROR: Failed to bind socket to Ethernet port.\n");
        perror("bind");
        close(gameSock);
        kill(procPID, SIGTERM);
    }
    printf("Socket opened.\n");
    // Wait for game to connect.
    msg = READY;
    sendRes = sendto(gameSock, &msg, 1, 0, (struct sockaddr *)&gameAddr,
            gameAddrLen);
    if (sendRes != 1) {
        fprintf(stderr, "ERROR: Failed to send connection message to game.\n");
        perror("sendto");
        close(gameSock);
        kill(procPID, SIGTERM);
    }
    printf("Sent handshake message to game.\n");
    // Wait for game calibration start signal.
    do {
        recvRes = recvfrom(gameSock, &msg, 1, 0, (struct sockaddr *)
                &recvGameAddr, &recvGameAddrLen);
        if (recvRes != 1) {
            fprintf(stderr,
                    "ERROR: Failed to receive message on socket.\n");
            perror("recv");
            close(gameSock);
            kill(procPID, SIGTERM);
        }
    } while (msg != START_CALIBRATION);
    // Spawn calibrator thread.
    if (pthread_create(&calibratorTID, &calibratorData, calibrator, NULL)) {
        fprintf(stderr, "ERROR: Failed to spawn calibrator thread.\n");
        close(gameSock);
        kill(procPID, SIGTERM);
    }
    // Start sampling.
    sem_post(&startSampling);
    // Start calibration.
    sem_post(&startCalibration);
    // Wait for first calibration to end.
    sem_wait(&endCalibration);
    // Control loop.
    for (;;) {
        // Acquire data processing right.
        pthread_mutex_lock(&controlLock);
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
        // Release data processing right.
        pthread_mutex_unlock(&controlLock);
        // Send control message.
        sendRes = sendto(gameSock, &msg, 1, 0, (struct sockaddr *)&gameAddr,
                         gameAddrLen);
        if (sendRes != 1) {
            fprintf(stderr, "ERROR: Failed to send message on socket.\n");
            perror("send");
            kill(procPID, SIGTERM);
        }
        printf("Sent control: '%c'.\n", msg);
    }
}

/* Termination procedure for controller thread. */
void controllerTermination(void) {
    pthread_kill(calibratorTID, SIGUSR1);
    pthread_join(calibratorTID, NULL);
    pthread_exit(NULL);
}
