#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void copyMemory(char *buf, const char *msg, size_t __size)
{
    size_t len = __size + 1;
    if ((size_t)512 < __size)
    {
        printf("Buffer overflow: message is bigger than 512 bytes (buffer length).\nExiting...");
        exit(EXIT_FAILURE);
    }
    memcpy(buf, msg, len);
}

int main()
{
    char buffer[512];
    char message[] = "Pwanga!";
    copyMemory(buffer, message, sizeof(message));
    printf("buffer: %s\n\n", buffer);
}