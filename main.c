#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <curl/curl.h>

void SkipPeerVerification(CURL *curl) 
{
    // Connect to a site that isn't using a signed certificate.
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    printf("Peer Verification Skipped\n");
}

void printHelp(char *argv[]) {
    printf("Usage: %s <url> [options...]\n-s, --skip   Skip Peer Verification (skip signed SSL certificate)\n\nExample: %s https://api.ipify.org\n", argv[0], argv[0]);
}

int main(int argc, char *argv[]) 
{
    char a[7];
    if(argc == 1)
    {
        printf("%s: try '%s --help' for more information", argv[0], argv[0]);
        exit(EXIT_FAILURE);
    }
    if(strcmp(argv[1], "-h") == 0) {
        printHelp(&argv[0]);
        exit(EXIT_SUCCESS);
    }
    if(strcmp(argv[1], "--help") == 0) 
    {
        printHelp(&argv[0]);
        exit(EXIT_SUCCESS);
    }

    CURL *curl = curl_easy_init();
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    bool skiparg = false;


    if(argv[2] == NULL) 
    {
        printf("Peer Verification Not Skipped\n");
    } 
    else if(0 == strcmp(argv[2], "--skip")) 
    {
        SkipPeerVerification(&curl);
    } 
    else if(0 == strcmp(argv[2], "-s")) {
        SkipPeerVerification(&curl);
    }
    else {
        printf("Peer Verification Not Skipped\n");
    }

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
    }

    printf("Result: ");
    // Perform request; res gets return code
    res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
        fprintf(stderr, "Failed request performing.\n");
        // Always cleanup
        curl_easy_cleanup(curl);
    }
    // Fish shell doesn't write in newline automatically
    printf("\n");

    curl_global_cleanup();

    return 0;
}
