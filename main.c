#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

void SkipPeerVerification() 
{
    #ifdef SKIP_PEER_VERIFICATION
        // Connect to a site that isn't using a signed certificate.
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, OL);
    #endif
    printf("Peer Verification Skipped\n");
}

int main(int argc, char *argv[]) 
{
    if(argc == 1)
    {
        printf("No Arguments Specified...\nUsage: ./executable URL\nExample: ./executable https://api.ipify.org");
        exit(EXIT_FAILURE);
    }

    CURL *curl = curl_easy_init();
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
    }

    char *input[1];
    input[0] = (char *)malloc(4 * sizeof(char));
    printf("Skip Peer Verification?\n(Connecting to a site that isn't using a signed SSL certificate)\n\n(Y; N)-> ");
    scanf("%s", input[0]);

    if (strcmp(input[0], "Y") == 0) 
    {
        SkipPeerVerification();
    } 
    else if (strcmp(input[0], "y") == 0)
    {
        SkipPeerVerification();
    }
    else if (strcmp(input[0], "Yes") == 0)
    {
        SkipPeerVerification();
    }
    else if (strcmp(input[0], "yes") == 0)
    {
        SkipPeerVerification();
    }
    else
    {
        printf("Peer Verification Not Skipped\n");
    }
    free(input[0]);

    printf("Result: ");
    // Perform request; res gets return code
    res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
        fprintf(stderr, "Failed request performing.\n");
        // Always cleanup
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return 0;
}