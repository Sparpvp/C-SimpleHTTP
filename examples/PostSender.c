#include "wrap.h"

int main()
{
    Request request;
    Init(&request);

    SendPOST(&request, "https://webhook.site/c4d4e0c2-013c-440b-9f65-fc98a8bd3811", "Some Data!");

    return 0;
}