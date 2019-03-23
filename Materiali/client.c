#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define SIZE 1024

void error(const char *msg);
int clientCmdLine(int argc, char *argv[], char **szAddress, char **szPort);
// definizione struttura poltrona

int main(int argc, char* argv[]) {
    // controllo argomenti
    char *address;
    char *porta;
    clientCmdLine(argc, argv, &address, &porta);
    // definizione variabili
    int sockfd;                  // client desc
    long port, n;                      // numero porta
    struct sockaddr_in serv_addr;   // server address
    struct hostent *server;         // host name
    char buffer[SIZE];              // buffer messaggio
    char *endptr;                   // per strtol()

    // prendo il numero di porta
    port = strtol(porta, &endptr, 0);
    if (*endptr)
        error("porta non riconosciuta");

    // creazione client socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("Client socket creation error");
    // prendo il nome del server
    server = gethostbyname(address);
    // inizializzazione socket
    bzero((char *) &serv_addr, sizeof(serv_addr));
    //inizializzo campi struttura client
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_aton(address, &serv_addr.sin_addr) <= 0) { // copio indirizzo da argvþ[] nel campo della struct
        // se la copia fallisce (ip = localhost invece che 120.0.0.1 per es)
        printf("client: indirizzo IP non valido.\nclient: risoluzione nome...");
        // calcolo indiizzo dal nome dato
        if ((server = gethostbyname(address)) == NULL) {
            printf("fallita.\n");
            exit(EXIT_FAILURE);
        }
        printf("riuscita.\n\n");
        // copia dell'indirizzo nel campo della struct
        serv_addr.sin_addr = *((struct in_addr *) server->h_addr);
    }

    // connetto al server
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("client: connection failed");


    // enter in the echo section
    while (1) {
        // inizializzo buffer
        bzero(buffer, SIZE);
        printf("Inserisci un messaggio:\n");
        // carico il messaggio da spedire
        fgets(buffer, SIZE, stdin);
        // invio il messaggio
        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0) { error("client: errore nell'invio"); }
        if (strncmp("close", buffer, 5) == 0) {
            printf("closing connection..\n");
            break;
        }
        // preparo alla lettura della risposta
        bzero(buffer, SIZE);
        // leggo risposta dal server
        n = read(sockfd, buffer, SIZE);
        if (n < 0)
            error("client: errore nella risposta dal server");
        printf("Server: %s\n", buffer);
        // controllo di terminazione del socket
    }
    close(sockfd);
    return 0;
}

void error(const char *msg){
  perror(msg);
  exit(EXIT_FAILURE);
}
int clientCmdLine(int argc, char *argv[], char **szAddress, char **szPort) {
    int n = 1;

    while (n < argc) {
        if (!strncmp(argv[n], "-a", 2) || !strncmp(argv[n], "-A", 2)) {
            *szAddress = argv[++n];
        } else if (!strncmp(argv[n], "-p", 2) || !strncmp(argv[n], "-P", 2)) {
            *szPort = argv[++n];
        } else if (!strncmp(argv[n], "-h", 2) || !strncmp(argv[n], "-H", 2)) {
            printf("Sintassi:\n\n");
            printf("    client -a (indirizzo server) -p (porta del server) [-h].\n\n");
            exit(EXIT_SUCCESS);
        }
        ++n;
    }
    if (argc == 1) {
        printf("Sintassi:\n\n");
        printf("    client -a (indirizzo server) -p (porta del server) [-h].\n\n");
        exit(EXIT_SUCCESS);
    }
    return 0;
}
