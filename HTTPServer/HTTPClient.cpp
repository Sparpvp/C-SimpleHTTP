#include "pkg/Request.hpp"

int main()
{
    // Initialize Object
    http::Request *request = new http::Request("webhook.site/c4d4e0c2-013c-440b-9f65-fc98a8bd3811");

    // Send HTTP/GET Request
    request->SendGET(80);
    std::cout << request->response;

    return 0;
}