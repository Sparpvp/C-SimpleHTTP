# C-SimpleHTTP
A simple HTTP protocol implementation in C  
There is a C++ (wrapper-only) one, too; but some features aren't supported yet.

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
 
