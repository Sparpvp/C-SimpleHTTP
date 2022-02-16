# C-SimpleHTTP
A simple HTTP protocol implementation made in C.  
Here you can find a wrapper of libcurl and no-bloat TCP/HTTP Server & Client.

# Full CLI Tool Usage
Below there's a full cli implementation of the wrapper.
```c++
#include "wrap.h"

int main(int argc, char *argv[])
{
    PrintUsage(argc, argv[0], argv[1]);

    Request request;
    Init(&request);

    CheckRequestType(&request, argv);

    PeerSSLVerify(&request, argv);

    // HTTP/GET
    if (request.rt == GET)
        if (request.curl)
            SendGET(&request, argv[2]);

    // HTTP/POST
    if (request.rt == POST)
        if (request.curl)
            SendPOST(&request, argv[3], argv[2]);

    return 0;
}
```  

# Fast HTTP GET 
Absolute NO-BLOAT Implementation of HTTP Protocol with sockets.
```c++
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
```  

# Fast HTTP POST
While there isn't the ABSOLUTE NO BLOAT implementation of HTTP POST with sockets, you can use the wrapper.
```c++
#include "wrap.h"

int main()
{
    Request request;
    Init(&request);

    SendPOST(&request, "https://webhook.site/c4d4e0c2-013c-440b-9f65-fc98a8bd3811", "Some Data!");

    return 0;
}
```

# How do i run this?
First of all, since this project is mostly made in C, you will need `GCC Compiler`.  
There's some C++ code too, to compile it, you will need `G++ Compiler`.  
For the wrapper, you will need to link `libcurl`.  

Wrapper compile command:  
```
gcc main.c -o simplehttp -lcurl
```

The rest of the project is compilable by:
```
gcc <name>.c
```
For the C++ source, instead:
```
g++ <name>.cpp
```

# Features Supported
- Wrapper:
    - HTTP GET
    - HTTP POST
- HTTP Implementation:
    - HTTP Server 
    - HTTP Client
- TCP Implementation
    - TCP Server
    - TCP Client

# TODO:
- [x] Code refactor
- [ ] Windows HTTP Server Support & HTTP Server abstraction
- [x] Linux HTTP Client Support
 
