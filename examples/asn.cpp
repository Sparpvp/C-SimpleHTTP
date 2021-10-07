#include <stdlib.h>
#include <string>
#include <cstring>
#include <iostream>
#include <curl/curl.h>
#include <regex>

std::string removeNonNumeric(std::string s) 
{
    std::string replace = "[]\"";
    for(char c : replace)
    {
        s.erase(std::remove(s.begin(), s.end(), c), s.end());
    }

    replace = ",";
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(replace)) != std::string::npos) {
        token = s.substr(0, pos);
        std::cout << token << std::endl;
        s.erase(0, pos + replace.length());
    }

    return s;
}


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
    std::cout << "Usage: " << argv[0] << " <asnNumber>\nExample: " << argv[0] << " 212271\n";
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

    if(curl) 
    {
        std::string url = "https://api.shadowserver.org/net/asn?prefix=";
        url += argv[1];
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Save data in string
        std::string response;

        // Set some useful parameters for query, including saving data to string
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Performs request; res gets return code
        res = curl_easy_perform(curl);
        std::string regexed = removeNonNumeric(response);
        std::cout << regexed;

        if(res != CURLE_OK) 
            fprintf(stderr, "Failed request performing.\n");

        // Cleanup
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return 0;
}