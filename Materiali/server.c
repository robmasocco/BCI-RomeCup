#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define SIZE 1024

void error(const char *msg);
int serverCmdLine(int argc, char *argv[], char **szPort);



int main(int argc, char *argv[]) {
    // controllo sugli input
    char *endptr;
    serverCmdLine(argc, argv, &endptr);
    // definizione variabili
    int sockfd, newsockfd;
    long portno, n;
    char buffer[SIZE];
    struct sockaddr_in serv_addr, client_addr;
    socklen_t clientlen;

    // creazione server socket per protocollo TCP
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("Error opening socket.");
    }

    // fillo i byte dell'indirizzo del server a 0
    bzero((char *) &serv_addr, sizeof(serv_addr));
    // prendo il numero di porta
    portno = strtol(endptr, &endptr, 0);
    // inizializzo campi struttura server
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);     // htons per la conversione a formato network

    // bindo il socket server
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("binding failure");
    // metto il socket server in ascolto
    if (listen(sockfd, 1) < 0)
        error("listen error");
    // calcolo dimensione dell'indirizzo del client
    clientlen = sizeof(client_addr);
    // controllo che viene fatta l'accettazione della connessione.
    printf("In attesa di connessione dal client\n");
    newsockfd = accept(sockfd, (struct sockaddr *) &client_addr, &clientlen);
    if (newsockfd < 0) { error("Error on accept"); }

    //enter in the echo section
    while (1) {
        // svuoto il buffer
        bzero(buffer, SIZE);
        printf("server: in attesa da client.\n");
        // leggo il messaggio in arrivo
        n = read(newsockfd, buffer, SIZE);
        if (n < 0) { error("read error"); }
        printf("Client: %s\n", buffer);
        if (strncmp("close", buffer, 5) == 0) {
            printf("closing connection..\n");
            break;
        }
        bzero(buffer, SIZE);
        strcpy(buffer, "send a massage\n");
        n = write(newsockfd, buffer, strlen(buffer));
        if (n < 0) { error("write error"); }
    }
    close(newsockfd);
    close(sockfd);
    return 0;
}
void error(const char *msg){
  perror(msg);
  exit(-1);
}

int serverCmdLine(int argc, char *argv[], char **szPort){
    int n = 1;

    while ( n < argc )
	{
		if ( !strncmp(argv[n], "-p", 2) || !strncmp(argv[n], "-P", 2) )
			*szPort = argv[++n];
		else
			if ( !strncmp(argv[n], "-h", 2) || !strncmp(argv[n], "-H", 2) ) {
			    printf("Sintassi:\n\n");
	    		    printf("    server -p (porta) [-h]\n\n");
			    exit(EXIT_SUCCESS);
			}
		++n;
    }
    if (argc==1) {
	printf("Sintassi:\n\n");
    	printf("    server -p (porta) [-h]\n\n");
	exit(EXIT_SUCCESS);
    }
    return 0;
}
