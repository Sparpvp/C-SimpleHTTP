#include "pkg/Request.hpp"

int main() 
{
    // Initialize Object
    http::Request* request = new http::Request();

    // Send HTTP/GET Request
    request->SendGET("www.google.com", 80);
 
    getchar();
    return 0;
}