# C-SimpleHTTP
A simple HTTP protocol implementation in C (Curl Wrapper)  
There is a C++ one, too; but POST requests are not supported yet.

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
- HTTP Get **(C; C++)**
- HTTP Post **(Only C Wrapper)**

# TODO:
- HTTP Server with sockets, the "real implementation" of HTTP in C.
