#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/socket.h>
#include <sys/types.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

void handleRequest(int cs)
{
    char buffer[512];   // Buffer for sending and receiving data
    int n;

    for(;;) 
    {
        bzero(buffer, 512);

        read(cs, buffer, sizeof(buffer));

        printf("Client says: %s\tResponse:  ", buffer);
        bzero(buffer, 512);
        n = 0;

        while ((buffer[n++] = getchar()) != '\n')
            ;
        
        write(cs, buffer, sizeof(buffer));

        if (strncmp("exit", buffer, 4) == 0) {
            printf("Server Exits...\n");
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    unsigned short int port;    // Port server binds to
    int sock;                   // Socket for accepting connections
    int connectedSock;          // Socket for enstablished connection
    int namelen;                // Length of client name
    struct sockaddr_in client;  // Client address information
    struct sockaddr_in server;  // Server address information

    // Check arguments
    if(argc != 2)
    {
        fprintf(stderr, "Invalid argument count.\nUsage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // First argument should be the port
    port = (unsigned short int)atoi(argv[1]);

    // Init socket for accepting connections and check for errors
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket() Error");
        exit(EXIT_FAILURE);
    }

    // Bind socket to the server address
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);

    // Error checking
    if ((bind(sock, (const struct sockaddr*)&server, sizeof(server))) != 0)
    {
        printf("Bind() Error");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections. Specify backlog as 1
    if ((listen(sock, 5)) != 0)
    {
        printf("Listen() Error");
        exit(EXIT_FAILURE);
    }
    else 
        printf("Server listening...\n");

    // Accept a connection
    namelen = sizeof(client);
    connectedSock = accept(sock, (struct sockaddr*)&client, &namelen);
    if (connectedSock < 0)
    {
        printf("Accept() Error");
        exit(EXIT_FAILURE);
    }
    else   
        printf("Server accepted the client...\n");
    
    handleRequest(connectedSock);

    // Close sock(s)
    close(sock);
    close(connectedSock);

    printf("\nGoodbye! Server closed.\n");

    return 0;
}