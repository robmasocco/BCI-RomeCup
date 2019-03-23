/*	Socket master	*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>		/* Socket definitions */
#include <sys/types.h>        	/* Socket type */
#include <arpa/inet.h>        	/* Inet funtions */
#include <unistd.h>           	/* UNIX functions */
#include <string.h>		/* Strings functiones */


/*  Global constants  */

#define MAX_LINE	256	

int ParseCmdLine(int argc, char *argv[], char **szPort);	/* Parsing della linea di comando */


int main(int argc, char *argv[])
{
    	short int port;			/* port number */
    	struct sockaddr_in servaddr;	/* socket address structure */
    	struct sockaddr_in their_addr;
    	char buffer[MAX_LINE];		/* character buffer */
    	char *endptr;			/* for strtol() */
    	int sin_size;  
	int sock_list, sock_conn;	/* Socket per listen e connect */


	/* Get command line arguments */

    	ParseCmdLine(argc, argv, &endptr);

	/* Set the port */

	port = strtol(endptr, &endptr, 0);
	if(*endptr){
	    printf("Porta non riconosciuta.\n");
	    exit(EXIT_FAILURE);
	}
    
	printf("Server in ascolto sulla porta %d\n",port);

	/* Create the listening socket */

 	if( (sock_list = socket(AF_INET, SOCK_STREAM, 0)) < 0 ){
        	printf("Errore nella creazione del socket.\n");
        	exit(EXIT_FAILURE);
   	}

	/* Set all bytes in socket address structure to
           zero, and fill in the relevant data members */

    	memset(&servaddr, 0, sizeof(servaddr));
    	servaddr.sin_family      = AF_INET;
    	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
   	servaddr.sin_port        = htons(port);

	/* Bind our socket addresss to the
           listening socket, and call listen() */

    	if ( bind(sock_list, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0 ) {
                printf("Errore durante la bind.\n");
                exit(EXIT_FAILURE);
    	}

   	if ( listen(sock_list, 0) < 0 ) {
                printf("Errore durante la listen.\n");
                exit(EXIT_FAILURE);
    	}

	/* Attesa di connessione con client e accept() */			

	printf("\n\nIn attesa di connessione dal client...\n");

	sin_size = sizeof(struct sockaddr_in);
	if( (sock_conn = accept(sock_list, (struct sockaddr *)&their_addr, &sin_size)) < 0){
		printf("Errore durante l'accept.\n");
		exit(EXIT_FAILURE);
	}
	
	printf("Connessione effettuata da %s\n\n", inet_ntoa(their_addr.sin_addr));
	/* Inizio comunicazione con il client */
	
	while(1){
		memset(buffer, 0, sizeof(buffer));	//buffer cleaning	
		read(sock_conn , buffer, MAX_LINE);	
								
		if( strcmp(buffer, "quit\n") == 0 ){
			printf("End of comunication\n");
			return 0;
		} 
		
		printf("%s\n", buffer);		
		write(sock_conn, buffer, strlen(buffer));
	}
}


/* Parsing della linea di comando */

int ParseCmdLine(int argc, char *argv[], char **szPort)
{
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
