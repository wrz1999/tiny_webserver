
#pragma once
#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
namespace wrz_socket{
    class ClientSocket;
    class ServerSocket
    {
        public:
            ServerSocket(int port_t=5000, const char* ip_t=nullptr);
            ~ServerSocket();
            void bind();
            void listen();
            void close();
            int accept(ClientSocket &client);

            struct sockaddr_in servaddr;
            int listen_fd;
            int port;
            const char* server_ip;
    };

    class ClientSocket
    {
        public:
            ~ClientSocket();
            int fd;
            struct sockaddr_in client_addr;
            socklen_t client_len;
            
    };
}
