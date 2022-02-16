# C-SimpleHTTP
A simple HTTP protocol implementation in C  

# Usage
Below there's a full cli implementation of the wrapper.
```c++
#include "wrap.h"

int main(int argc, char *argv[])
{
    PrintUsage(argc, argv[0], argv[1]);

    Request request;
    Init(&request);

    CheckRequestType(&request, argv[1]);

    PeerSSLVerify(&request, argv[3], argv[4]);

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

# How do i run it?
First of all, this project is made in C, then you will need `GCC Compiler`.  
If you want to compile the C++ one, you will need `G++ Compiler`.  
There is a dependency too, curl, or more specify, its library `libcurl`.  

Then, compile it with:  
```
gcc main.c -o simplehttp -lcurl
```

For the C++ version, instead:
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
- Code refactor
- Windows HTTP Server Support
- Linux HTTP Client Support
 
