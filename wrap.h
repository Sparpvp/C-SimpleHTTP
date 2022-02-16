#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <curl/curl.h>

enum RequestType
{
    GET,
    POST
};
typedef enum RequestType RequestType;

struct Request
{
    CURL *curl;
    CURLcode res;
    bool skiparg;
    RequestType rt;
};
typedef struct Request Request;

void CheckRequestType(Request *r, char *arg)
{
    if (0 == strcmp(arg, "-p") || 0 == strcmp(arg, "--post"))
        r->rt = POST;
    else
        r->rt = GET;
}

void PrintMissingArguments(char *arg)
{
    printf("%s: Missing arguments... try '%s --help' for more information\n", arg, arg);
    exit(EXIT_FAILURE);
}

void PrintHelp(char *arg)
{
    printf("Usage: %s [Required Options] <url> [Optional Settings...] \n-g, --get\t\tSend HTTP GET Request\n-p, --post \"<data>\"\tSend HTTP POST Request\n[Optional] -s, --skip\tSkip Peer Verification (skip signed SSL certificate verify)\n\nExample: %s -g https://api.ipify.org\n", arg, arg);
    exit(EXIT_SUCCESS);
}

void PrintUsage(int argc, char *arg0, char *arg1)
{
    if (argc == 1)
        PrintMissingArguments(arg0);
    if (strcmp(arg1, "-h") == 0 || strcmp(arg1, "--help") == 0)
        PrintHelp(arg1);
}

void PeerSSLVerify(Request *r, char *arg3, char *arg4)
{
    if (r->rt == GET && arg3 == NULL || r->rt == POST && arg4 == NULL)
    {
        printf("SSL Peer certification verify not skipped\n");
        return;
    }

    // Connect to a site that isn't using a signed certificate.
    if (r->rt == GET && 0 == strcmp(arg3, "-s"))
        curl_easy_setopt(r->curl, CURLOPT_SSL_VERIFYPEER, 0L);
    else if (r->rt == GET && 0 == strcmp(arg3, "--skip"))
        curl_easy_setopt(r->curl, CURLOPT_SSL_VERIFYPEER, 0L);
    else if (r->rt == POST && 0 == strcmp(arg4, "-s"))
        curl_easy_setopt(r->curl, CURLOPT_SSL_VERIFYPEER, 0L);
    else if (r->rt == POST && 0 == strcmp(arg4, "--skip"))
        curl_easy_setopt(r->curl, CURLOPT_SSL_VERIFYPEER, 0L);

    printf("SSL Peer certification verify skipped\n");
}

void Init(Request *r)
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    r->curl = curl_easy_init();
    r->skiparg = false;
}

void SendGET(Request *r, char *url)
{
    curl_easy_setopt(r->curl, CURLOPT_URL, url);
    printf("Response: ");
    // Perform request; res gets return code
    r->res = curl_easy_perform(r->curl);
    if (r->res != CURLE_OK)
    {
        fprintf(stderr, "Failed request performing.\n");
        // Always cleanup
        curl_easy_cleanup(r->curl);
    }
    // Fish shell (and some others) doesn't write in newline automatically
    printf("\n");
}

void SendPOST(Request *r, char *url, char *postData)
{
    // Specify Link for the POST request
    curl_easy_setopt(r->curl, CURLOPT_URL, url);

    // Specify POST data
    curl_easy_setopt(r->curl, CURLOPT_POSTFIELDS, postData);

    // Perform the request, res will get the return code
    r->res = curl_easy_perform(r->curl);

    if (r->res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(r->res));

    curl_easy_cleanup(r->curl);

    printf("Request sent!\n");
}