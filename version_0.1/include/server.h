#include "mysocket.h"
#include <sys/epoll.h>
#include "httpparse.h"
#include "httpresponse.h"
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#define POLL_SIZE 1024
namespace wrz_server
{
    class Web_Server
    {
        public:
            explicit Web_Server(int port=5000, const char* ip=nullptr):server_socket(port, ip)
            {
                server_socket.bind();
                server_socket.listen();
                this->epfd = epoll_create(1);
                this->ev.events = EPOLLIN;
                this->ev.data.fd = server_socket.listen_fd;
                epoll_ctl(this->epfd, EPOLL_CTL_ADD, server_socket.listen_fd, &(this->ev)); 

            }
            void run();

            int epfd;
            struct epoll_event events[POLL_SIZE];
            struct epoll_event ev;
            wrz_socket::ServerSocket server_socket;
        private:
            void header(const http::HttpRequest&, http::HttpResponse&);
            void static_file(http::HttpResponse&, const char*);
            void send(const http::HttpResponse&, int client_fd);
            void getMime(const http::HttpRequest&, http::HttpResponse&);
            

    };
}
