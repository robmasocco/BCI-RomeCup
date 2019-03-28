#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#define PI_IP "192.168.2.111"
#define GAME_PORT 4444
#define BACKLOG 1

/* New shit. */
#define CALIBRATION_DURATION 5
#define CONTROL_DURATION 1

/* Socket data. */
int sock, gameSock;
int yes = 1;
struct sockaddr_in sockAddr, gameAddr;
socklen_t gameAddrLen;

/* Function to determine input for the game. */
int control(void) {
    static int firstTime = 1;
    if (firstTime) {
        firstTime = 0;
        srand(time(NULL));
    }
    int comms[] = {-1, 0, 1};
    return comms[rand() % 3];
}

void terminator(int sig) {
    (void)sig;
    printf("Leeezzo!\n");
    exit(EXIT_SUCCESS);
}

/* Shitty copypaste of one and a half threads. */
int main(void) {
    signal(SIGINT, terminator);
    signal(SIGTERM, terminator);
    int controlRes;
    char msg;
    ssize_t recvRes, sendRes;
    // Open and configure socket.
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0) {
        fprintf(stderr, "ERROR: Failed to open socket.\n");
        perror("socket");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes)) {
        fprintf(stderr, "ERROR: Failed to configure socket.\n");
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    memset(&sockAddr, 0, sizeof sockAddr);
    memset(&gameAddr, 0, sizeof gameAddr);
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = (uint16_t)htons(GAME_PORT);  // WTF
    inet_pton(AF_INET, PI_IP, &(sockAddr.sin_addr.s_addr));
    if (bind(sock, (struct sockaddr *)&sockAddr, sizeof sockAddr)) {
        fprintf(stderr, "ERROR: Failed to bind socket to Ethernet port.\n");
        perror("bind");
        exit(EXIT_FAILURE);
    }
    if (listen(sock, BACKLOG)) {
        fprintf(stderr, "ERROR: Failed to set socket as listening.\n");
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("Socket opened.\n");
    // Wait for game to connect.
    gameSock = accept(sock, (struct sockaddr *)&gameAddr, &gameAddrLen);
    if (gameSock < 0) {
        fprintf(stderr, "ERROR: Failed to accept connection with game.\n");
        perror("accept");
        exit(EXIT_FAILURE);
    }
    close(sock);
    printf("Connected with game.\n");
    // Wait for game calibration start signal.
    do {
        recvRes = recv(gameSock, &msg, 1, 0);
        if (recvRes == 0) {
            // Socket closed: terminate process.
            exit(EXIT_FAILURE);
        } else if (recvRes == -1) {
            fprintf(stderr,
                    "ERROR: Failed to receive message on socket.\n");
            perror("recv");
            exit(EXIT_FAILURE);
        }
    } while (msg != 'S');

    // NOW THE REAL COPYPASTE SHIT STARTS //

    msg = 'E';
    printf("First calibration started.\n");
    // Simulate filter startup.
    sleep(2);
    sendRes = send(gameSock, &msg, 1, MSG_NOSIGNAL);
    if (sendRes != 1) {
        fprintf(stderr, "ERROR: Failed to send message on socket.\n");
        perror("send");
        exit(EXIT_FAILURE);
    }
    printf("Filters setup completed.\n");
    // Simulate calibration steps.
    for (int i = 0; i < 7; i++) {
        // Wait for game calibration start message.
        do {
            recvRes = recv(gameSock, &msg, 1, 0);
            if (recvRes == 0) {
                // Socket closed: terminate process.
                exit(EXIT_FAILURE);
            } else if (recvRes == -1) {
                fprintf(stderr,
                        "ERROR: Failed to receive message on socket.\n");
                perror("recv");
                exit(EXIT_FAILURE);
            }
        } while (msg != 'S');
        sleep(CALIBRATION_DURATION);
        sendRes = send(gameSock, &msg, 1, MSG_NOSIGNAL);
        if (sendRes != 1) {
            fprintf(stderr, "ERROR: Failed to send message on socket.\n");
            perror("send");
            exit(EXIT_FAILURE);
        }
        printf("Calibration phase %d done.\n", i + 1);
    }
    printf("Initial calibration completed.\n");
    // Simulate control.
    for (;;) {
        sleep(CONTROL_DURATION);
        controlRes = control();
        if (controlRes == -1) {
            msg = 'L';
        } else if (controlRes == 1) {
            msg = 'R';
        } else msg = 'C';
        // Send control message.
        sendRes = send(gameSock, &msg, 1, MSG_NOSIGNAL);
        if (sendRes != 1) {
            fprintf(stderr, "ERROR: Failed to send message on socket.\n");
            perror("send");
            exit(EXIT_FAILURE);
        }
        printf("Sent control: '%c'.\n", msg);
    }
    return 0;
}
