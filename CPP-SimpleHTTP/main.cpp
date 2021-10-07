#include <stdlib.h>
#include <string>
#include <cstring>
#include <iostream>
#include <curl/curl.h>

size_t size = 0;
size_t write_to_string(void *ptr, size_t size, size_t count, void *stream) {
  ((std::string*)stream)->append((char*)ptr, 0, size*count);
  return size*count;
}

void SkipPeerVerification(CURL *curl) 
{
    // Connect to a site that isn't using a signed certificate.
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    std::cout << "Peer Verification Skipped\n";
}

void printHelp(char *argv[]) {
    std::cout << "Usage: " << argv[0] << " <url> [options...]\n-s, --skip\tSkip Peer Verification (skip signed SSL certificate)\n\nExample: " << argv[0] << " https://api.ipify.org\n";
}

int main(int argc, char *argv[]) 
{
    if(argc == 1)
    {
        std::cout << argv[0] << ":" << " try" << " '" << argv[0] << "' " << "--help for more information" << std::endl;
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
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    bool skiparg = false;


    if(argv[2] == NULL) 
    {
        std::cout << "Peer Verification Not Skipped\n";
    } 
    else if(0 == strcmp(argv[2], "--skip")) 
    {
        SkipPeerVerification(&curl);
    } 
    else if(0 == strcmp(argv[2], "-s")) {
        SkipPeerVerification(&curl);
    }
    else 
    {
        std::cout << "Peer Verification Not Skipped\n";
    }

    if(curl) 
    {
        curl_easy_setopt(curl, CURLOPT_URL, argv[1]);

        // Save data in string
        std::string response;

        // Set some useful parameters for query, including saving data to string
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Performs request; res gets return code
        res = curl_easy_perform(curl);

        std::cout << "Result: " << response << std::endl;

        if(res != CURLE_OK) 
            fprintf(stderr, "Failed request performing.\n");

        // Cleanup
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return 0;
}
