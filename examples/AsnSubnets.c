#include "wrap.h"

int main()
{
    Request request;
    Init(&request);

    SendGET(&request, "https://api.shadowserver.org/net/asn?prefix=212271"); // Response saved in request.response

    return 0;
}