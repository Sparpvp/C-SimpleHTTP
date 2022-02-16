#pragma once

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")
#elif __linux__
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#endif
#include <iostream>
#include <locale>
#include <sstream>

#define BUFFER_LEN 10000
#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

namespace http
{
    class Request
    {
    public:
        Request(std::string &&url)
        {
            mParseUrl((char *)url.c_str());
        }

    private:
#ifdef _WIN32
        WSADATA wsaData;
        SOCKET Socket;
        SOCKADDR_IN SockAddr;
        struct hostent *host = NULL;
        std::locale local;
        int lineCount = 0, rowCount = 0, i = 0, nDataLength;
        char buffer[BUFFER_LEN];
#elif __linux__
        int sock, sendbytes;
        struct sockaddr_in client;
        struct hostent *host;
        char buffer[BUFFER_LEN];
#endif
        std::string serverName, filepath, filename;
        void mParseUrl(char *mUrl)
        {
            std::string::size_type n;
            std::string url = mUrl;

            if (url.substr(0, 7) == "http://")
                url.erase(0, 7);

            if (url.substr(0, 8) == "https://")
                url.erase(0, 8);

            n = url.find('/');
            if (n != std::string::npos)
            {
                serverName = url.substr(0, n);
                filepath = url.substr(n);
                n = filepath.rfind('/');
                filename = filepath.substr(n + 1);
            }
            else
            {
                serverName = url;
                filepath = "/";
                filename = "";
            }
        }

    public:
#ifdef _WIN32
        std::string response;
        std::string SendGET(int &&port)
        {
            if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
            {
                std::cout << "WSAStartup failed.\n";
                getchar();
                exit(EXIT_FAILURE);
            }

            std::stringstream ss;
            ss << "GET " << filepath << " "
               << "HTTP/1.1\r\n"
               << "Host: " << serverName << "\r\n"
               << "Connection: close\r\n\n";
            const std::string get_http = ss.str();

            Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            host = gethostbyname((const char *)serverName.c_str());

            SockAddr.sin_port = htons(port);
            SockAddr.sin_family = AF_INET;
            SockAddr.sin_addr.s_addr = *((unsigned long *)host->h_addr);

            if (connect(Socket, (SOCKADDR *)(&SockAddr), sizeof(SockAddr)) != 0)
            {
                std::cout << "Could not connect";
                getchar();
                exit(EXIT_FAILURE);
            }

            // Send GET HTTP req
            send(Socket, get_http.c_str(), strlen(get_http.c_str()), (size_t)0);

            // Receive Data
            while ((nDataLength = recv(Socket, buffer, 10000, 0)) > 0)
            {
                int i = 0;
                while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r')
                {
                    response += buffer[i];
                    i += 1;
                }
            }
            closesocket(Socket);
            WSACleanup();

            return response;
        }
#elif __linux__
        std::string response;
        std::string SendGET(int &&port)
        {
            host = gethostbyname((const char *)serverName.c_str());
            if ((host == NULL) || (host->h_addr == NULL))
            {
                std::cout << "Error retrieving DNS information." << std::endl;
                exit(1);
            }

            bzero(&client, sizeof(client));
            client.sin_family = AF_INET;
            client.sin_port = htons(port);
            memcpy(&client.sin_addr, host->h_addr, host->h_length);

            sock = socket(AF_INET, SOCK_STREAM, 0);
            if (sock < 0)
            {
                std::cout << "Error creating socket." << std::endl;
                exit(1);
            }

            if (connect(sock, (struct sockaddr *)&client, sizeof(client)) < 0)
            {
                close(sock);
                std::cout << "Could not connect" << std::endl;
                exit(1);
            }

            std::stringstream ss;
            ss << "GET " << filepath << " "
               << "HTTP/1.1\r\n"
               << "Host: " << serverName << "\r\n"
               << "Connection: close\r\n\n";
            std::string request = ss.str();

            if (send(sock, request.c_str(), request.length(), 0) != (int)request.length())
            {
                std::cout << "Error sending request." << std::endl;
                exit(1);
            }

            while (read(sock, &buffer, 1) > 0)
                response += buffer;

            return response;
        }
#endif
    };
}
