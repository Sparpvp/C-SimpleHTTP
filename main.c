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
    printf("Usage: %s [options...] <url> \n-g, --get\tExecute HTTP GET Request\n-p, --post \"<data>\"\tExecute HTTP POST Request\n[Optional] -s, --skip\tSkip Peer Verification (skip signed SSL certificate)\n\nExample: %s -g https://api.ipify.org\n", argv[0], argv[0]);
}

int main(int argc, char *argv[]) 
{
    char a[7];
    if(argc == 1)
    {
        printf("%s: Missing arguments... try '%s --help' for more information", argv[0], argv[0]);
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

    
    if(argv[3] == NULL || argv[4] == NULL) 
    {
        skiparg = true;
        goto skip;
    }
    if(0 == strcmp(argv[3], "-s") || 0 == strcmp(argv[4], "-s")) {
        SkipPeerVerification(curl);
    }
    if(0 == strcmp(argv[3], "--skip") || 0 == strcmp(argv[4], "-s")) 
    {
        SkipPeerVerification(curl);
    }
    skip:
    if(skiparg)
    {
        printf("Peer Verification Not Skipped\n");
    }
    if(0 == strcmp(argv[1], "-g")) 
    {
        if(curl)
        {
            curl_easy_setopt(curl, CURLOPT_URL, argv[2]);
            printf("Result: ");
            // Perform request; res gets return code
            res = curl_easy_perform(curl);
            if(res != CURLE_OK) 
            {
                fprintf(stderr, "Failed request performing.\n");
                // Always cleanup
                curl_easy_cleanup(curl);
            }
            // Fish shell doesn't write in newline automatically
            printf("\n");
        }
    }
    if(0 == strcmp(argv[1], "--get")) 
    {
        if(curl) 
        {
            curl_easy_setopt(curl, CURLOPT_URL, argv[2]);
            printf("Result: ");
            // Perform request; res gets return code
            res = curl_easy_perform(curl);
            if(res != CURLE_OK) 
            {
                fprintf(stderr, "Failed request performing.\n");
                // Always cleanup
                curl_easy_cleanup(curl);
            }
            // Fish shell doesn't write in newline automatically
            printf("\n");
        }
    }
    if(0 == strcmp(argv[1], "-p")) 
    {
        if(curl) 
        {
            curl_easy_setopt(curl, CURLOPT_URL, argv[3]);
            
            // Specify POST data
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, argv[2]);
        
            // Perform the request, res will get the return code
            res = curl_easy_perform(curl);
            
            if(res != CURLE_OK)
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

            curl_easy_cleanup(curl);    
        }
    }
    if(0 == strcmp(argv[1], "--post")) 
    {
        if(curl) 
        {
            curl_easy_setopt(curl, CURLOPT_URL, argv[3]);
            
            // Specify POST data
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, argv[2]);
        
            // Perform the request, res will get the return code
            res = curl_easy_perform(curl);
            
            if(res != CURLE_OK)
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

            curl_easy_cleanup(curl);    
        }
    }

    curl_global_cleanup();

    return 0;
}
