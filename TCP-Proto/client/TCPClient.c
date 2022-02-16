#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/socket.h>
#include <sys/types.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

void sendData(int cs)
{
    char buffer[512]; // Buffer for sending and receiving data
    int n;

    for (;;)
    {
        bzero(buffer, sizeof(buffer));
        printf("Say something: ");
        n = 0;
        while ((buffer[n++] = getchar()) != '\n')
            ;
        
        write(cs, buffer, sizeof(buffer));
        bzero(buffer, sizeof(buffer));
        read(cs, buffer, sizeof(buffer));
        printf("Server says: %s", buffer);

        if ((strncmp(buffer, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    unsigned short int port;    // Port client will connect to
    int sock;                   // Client socket
    struct hostent *hostname;   // Server hostname information
    struct sockaddr_in server;  // Server address

    // Check arguments
    if(argc != 3)
    {
        fprintf(stderr, "Invalid argument count.\nUsage: %s <hostname> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1)
    {
        printf("Socket() Error");
        exit(EXIT_FAILURE);
    }

    // First argument should be the hostname
    hostname = gethostbyname(argv[1]);
    if (hostname == (struct hostent*) 0)
    {
        printf("gethostbyname() Error");
        exit(EXIT_FAILURE);
    }

    // Second argument should be the port
    port = (unsigned short int)atoi(argv[2]);

    // Bind socket to the server address
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(port);

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) != 0)
    {
        printf("Connect() Error");
        exit(EXIT_FAILURE);
    }
    else
        printf("Connected to the server.\n");
    
    sendData(sock);

    // Close socket
    close(sock);

    return 0;
}