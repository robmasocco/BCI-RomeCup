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

#define PI_IP "192.168.2.143"
#define GAME_PORT 4444
#define BACKLOG 1

extern pid_t procPID;

extern sigset_t workerSet;

extern __thread void (*closeRoutine)(void);

extern sem_t dataLocks[CHANNELS][2];
extern sem_t startSampling, startCalibration, endCalibration;

extern pthread_mutex_t controlLock;

/* Socket data. */
int sock, gameSock;
int yes = 1;
struct sockaddr_in sockAddr, gameAddr;
socklen_t gameAddrLen;

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
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0) {
        fprintf(stderr, "ERROR: Failed to open socket.\n");
        perror("socket");
        kill(procPID, SIGTERM);
        pthread_exit(NULL);
    }
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes)) {
        fprintf(stderr, "ERROR: Failed to configure socket.\n");
        perror("setsockopt");
        kill(procPID, SIGTERM);
        pthread_exit(NULL);
    }
    memset(&sockAddr, 0, sizeof sockAddr);
    memset(&gameAddr, 0, sizeof gameAddr);
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = (uint16_t)htons(GAME_PORT);  // WTF
    inet_pton(AF_INET, PI_IP, &(sockAddr.sin_addr.s_addr));
    if (bind(sock, (struct sockaddr *)&sockAddr, sizeof sockAddr)) {
        fprintf(stderr, "ERROR: Failed to bind socket to Ethernet port.\n");
        perror("bind");
        kill(procPID, SIGTERM);
        pthread_exit(NULL);
    }
    if (listen(sock, BACKLOG)) {
        fprintf(stderr, "ERROR: Failed to set socket as listening.\n");
        perror("listen");
        kill(procPID, SIGTERM);
        pthread_exit(NULL);
    }
    printf("Socket opened.\n");
    // Wait for game to connect.
    gameSock = accept(sock, (struct sockaddr *)&gameAddr, &gameAddrLen);
    if (gameSock < 0) {
        fprintf(stderr, "ERROR: Failed to accept connection with game.\n");
        perror("accept");
        kill(procPID, SIGTERM);
        pthread_exit(NULL);
    }
    close(sock);
    printf("Connected with game.\n");
    // Wait for game calibration start signal.
    do {
        recvRes = recv(gameSock, &msg, 1, 0);
        if (recvRes == 0) {
            // Socket closed: terminate process.
            kill(procPID, SIGTERM);
        } else if (recvRes == -1) {
            fprintf(stderr,
                    "ERROR: Failed to receive message on socket.\n");
            perror("recv");
            kill(procPID, SIGTERM);
        }
    } while (msg != START_CALIBRATION);
    // Spawn calibrator thread.
    if (pthread_create(&calibratorTID, &calibratorData, calibrator, NULL)) {
        fprintf(stderr, "ERROR: Failed to spawn calibrator thread.\n");
        close(gameSock);
        kill(procPID, SIGTERM);
        pthread_exit(NULL);
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
        sendRes = send(gameSock, &msg, 1, MSG_NOSIGNAL);
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
