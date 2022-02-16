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
```c++
#include "wrap.h"

int main()
{
    Request request;
    Init(&request);

    SendGET(&request, "https://api.shadowserver.org/net/asn?prefix=212271");

    return 0;
}
```  

# How do i run it?
First of all, this project is made in C, then you will need `GCC Compiler`.  
If you want to compile the C++ example, you will need `G++ Compiler`.  
There is a dependency too, curl, or more specify, its library `libcurl`.  

Then, compile it with:  
```
gcc main.c -o simplehttp -lcurl
```

If you want to compile the C++ example, instead:
```
g++ main.cpp -o simplehttp -lcurl
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
- [ ] Windows HTTP Server Support
- [ ] Linux HTTP Client Support
 
