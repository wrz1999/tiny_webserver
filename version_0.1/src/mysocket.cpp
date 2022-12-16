#include "../include/mysocket.h"

wrz_socket::ServerSocket::ServerSocket(int port_t, const char* ip_t):port(port_t),server_ip(ip_t)
{
    memset(&(this->servaddr), 0, sizeof(this->servaddr));
    this->servaddr.sin_family = AF_INET;
    this->servaddr.sin_port = htons(this->port);
    if(ip_t != nullptr)
    {
        ::inet_pton(AF_INET, ip_t, &(this->servaddr.sin_addr));
    }
    else
    {
        this->servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    this->listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->listen_fd == -1){
        std::cout << "creat socket error in file <" << __FILE__ << "> "<< "at " << __LINE__ << std::endl;
        exit(0);
    }

}

void wrz_socket::ServerSocket::bind()
{
    int ret = ::bind(this->listen_fd, (struct sockaddr*)&this->servaddr, sizeof(this->servaddr));
    if (ret == -1) {
        std::cout << "bind error in file <" << __FILE__ << "> "<< "at " << __LINE__ << std::endl;
        exit(0);
    }
}

void wrz_socket::ServerSocket::listen()
{
    int ret = ::listen(this->listen_fd, 10);
    if (ret == -1) {
        std::cout << "listen error in file <" << __FILE__ << "> "<< "at " << __LINE__ << std::endl;
        exit(0);
    }
}

int wrz_socket::ServerSocket::accept(ClientSocket &client)
{
    int client_fd = ::accept(this->listen_fd, (struct sockaddr*)&(client.client_addr), &(client.client_len));
    if (client_fd < 0) {
        std::cout << "accept error in file <" << __FILE__ << "> "<< "at " << __LINE__ << std::endl;
        exit(0);
    }
    client.fd = client_fd;
    return client_fd;
}
wrz_socket::ServerSocket::~ServerSocket()
{
    ::close(this->listen_fd);
}
wrz_socket::ClientSocket::~ClientSocket()
{
    // ::close(this->fd);
}