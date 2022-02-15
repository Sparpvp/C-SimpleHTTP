#pragma once

#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <locale>

#define BUFFER_LEN 10000
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#pragma warning(disable:6031)

namespace http {
    class Request
    {
    private:
        WSADATA wsaData;
        SOCKET Socket;
        SOCKADDR_IN SockAddr;
        struct hostent* host = NULL;
        std::locale local;
        int lineCount = 0, rowCount = 0, i = 0, nDataLength;
        char buffer[BUFFER_LEN];
        std::string response;

    public:
        std::string SendGET(std::string&& url, int&& port)
        {
            if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
                std::cout << "WSAStartup failed.\n";
                getchar();
                exit(EXIT_FAILURE);
            }
            const std::string get_http = "GET / HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n";

            Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            host = gethostbyname(url.c_str());

            SockAddr.sin_port = htons(port);
            SockAddr.sin_family = AF_INET;
            SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

            if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0) {
                std::cout << "Could not connect";
                getchar();
                exit(EXIT_FAILURE);
            }

            // Send GET HTTP req
            send(Socket, get_http.c_str(), strlen(get_http.c_str()), (size_t)0);

            // Receive Data
            while ((nDataLength = recv(Socket, buffer, 10000, 0)) > 0) {
                int i = 0;
                while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r') {
                    response += buffer[i];
                    i += 1;
                }
            }
            closesocket(Socket);
            WSACleanup();

            return response;
        }
    };
}

