#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "wrap.h"

int main(int argc, char *argv[])
{
    PrintUsage(argc, argv[0], argv[1]);

    Request request;
    Init(&request);

    CheckRequestType(&request, argv[1]);

    PeerSSLVerify(&request, argv[3], argv[4]);

    // HTTP/GET
    if (request.rt == GET)
        if (request.curl)
            SendGET(&request, argv[2]);

    // HTTP/POST
    if (request.rt == POST)
        if (request.curl)
            SendPOST(&request, argv[3], argv[2]);

    return 0;
}