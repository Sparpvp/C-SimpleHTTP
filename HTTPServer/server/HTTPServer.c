#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/socket.h>
#include <sys/types.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

char *bin2hex(const unsigned char *input, size_t len)
{
    char *result;
    char *hexs = "0123456789ABCDEF";

    if (input == NULL || len <= 0)
        return NULL;

    int resultlength = (len*3)+1;

    result = malloc(resultlength);
    bzero(result, resultlength);

    for (int i=0; i<len; i++)
    {
        result[i*3]     = hexs[input[i] >> 4];
        result[(i*3)+1] = hexs[input[i] & 0x0F];
        result[(i+3)+2] = ' ';
    }

    return result;
}

void handleRequest(int s, int cs)
{
    uint8_t recvline[4096+1]; // Data exchange
    uint8_t buffer[4096+1];   // Data exchange
    int n;

    for(;;) 
    {
        struct sockaddr_in addr;
        socklen_t addr_len;

        printf("Waiting for a connection on port %d", 8080);
        fflush(stdout);
        cs = accept(s, (struct sockaddr*) NULL, NULL);

        memset(recvline, 0, 4096);

        while( (n = read(cs, recvline, sizeof(recvline)) ) > 0)
        {
            fprintf(stdout, "\n%s\n\n%s", bin2hex(recvline, n), recvline);

            if (recvline[n-1] == '\n')
                break;

            memset(recvline, 0, 4096);
        }

        if (n < 0) 
        {
            printf("Read() Error");
            exit(EXIT_FAILURE);
        }

        // Basic HTTP response
        snprintf((char*)buffer, sizeof(buffer), "HTTP/1.0 200 OK\r\n\r\nHello");

        write(cs, (char*)buffer, strlen((char*)buffer));
        close(cs);
    }
}

int main()
{
    int sock;                       // Socket for accepting connections
    int connectedSock;              // Socket for enstablished connection
    struct sockaddr_in serveraddr;  // Server info

    // Init socket for accepting connections and check for errors
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket() Error");
        exit(EXIT_FAILURE);
    }

    // Bind socket to the server address
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family      = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port        = htons(8080);

    if ((bind(sock, (const struct sockaddr*)&serveraddr, sizeof(serveraddr))) != 0)
    {
        printf("Bind() Error");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections.
    if ((listen(sock, 5)) != 0)
    {
        printf("Listen() Error");
        exit(EXIT_FAILURE);
    }
    else 
        printf("Server listening...\n");

    handleRequest(sock, connectedSock);

    printf("\nSomething's wrong... i can feel it\n"); // You shouldn't be here
    close(sock);
    close(connectedSock);

    return 0;
}