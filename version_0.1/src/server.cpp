#include "../include/server.h"
#include "../include/mysocket.h"
# define MAX_SIZE 2000
using namespace http;
void wrz_server::Web_Server::run()
{
    char buff[MAX_SIZE];
    while (1)
    {
        int nready = epoll_wait(this->epfd, this->events, POLL_SIZE, 5);
        if(nready == -1)
        {
            continue;
        }
        int i = 0;

        for(i = 0; i < nready; i++)
        {
            int clientfd = this->events[i].data.fd;
            if(clientfd == this->server_socket.listen_fd)
            {
                wrz_socket::ClientSocket client;
                int client_fd = this->server_socket.accept(client);
                if(client_fd == -1)
                {
                    std::cout << "error client_fd!" << std::endl;
                    continue;
                }
                std::cout << "连接一个client" << std::endl;
                this->ev.events = EPOLLIN;
                this->ev.data.fd = client.fd;
                epoll_ctl(this->epfd, EPOLL_CTL_ADD, client.fd, &(this->ev));
            }
            else if(this->events[i].events & EPOLLIN)
            {
                // int n = ::recv(clientfd, buff, MAX_SIZE, 0);
                // if(n > 0)
                // {
                //     buff[n] = '\0';
                //     // std::cout << "[rev message]:"<<buff << std::endl;
                //     std::string http_str = buff;
              
                //     std::cout << buff << std::endl;
                //     char message[] = "HTTP SERVER!!";
                //     // ::send(clientfd, buff, n, 0);
                // }
                // else if(n == 0)
                // {
                //     this->ev.events = EPOLLIN;
                //     this->ev.data.fd = clientfd;
                //     epoll_ctl(this->epfd, EPOLL_CTL_DEL, clientfd, &ev);
                //     ::close(clientfd);
                // }
                int check_index = 0, read_index = 0, start_line = 0;
                http::HttpRequestParser::PARSE_STATE  parse_state = http::HttpRequestParser::PARSE_REQUESTLINE;
                while(true)
                {
                    http::HttpRequest  request;
                    int ret = recv(clientfd, buff + read_index, MAX_SIZE - read_index, 0);
                    if (ret == -1)
                    {
                        this->ev.events = EPOLLIN;
                        this->ev.data.fd = clientfd;
                        epoll_ctl(this->epfd, EPOLL_CTL_DEL, clientfd, &ev);
                        ::close(clientfd);
                        std::cout << "reading faild" << std::endl;
                        exit(0);
                    }
                    else if(ret == 0)
                    {
                        this->ev.events = EPOLLIN;
                        this->ev.data.fd = clientfd;
                        epoll_ctl(this->epfd, EPOLL_CTL_DEL, clientfd, &ev);
                        ::close(clientfd);
                        break;
                    }
                    else
                    {
                        read_index += ret;
                        http::HttpRequestParser::HTTP_CODE  retcode = http::HttpRequestParser::parse_content(
                        buff, check_index, read_index, parse_state, start_line, request);
                        if (retcode == http::HttpRequestParser::NO_REQUEST) {
                            continue;
                        }

                        if (retcode == http::HttpRequestParser::GET_REQUEST) {
                            HttpResponse response(true);
                            header(request, response);
                            getMime(request, response);
                            static_file(response, "/Users/lichunlin/CLionProjects/webserver/version_0.1");
                            send(response, clientfd);
                        } else {
                            std::cout << "Bad Request" << std::endl;
                        }
                    }
                }
            }

        }

    }

    return;
}

// void wrz_server::Web_Server::do_request(const ClientSocket & clientSocket) {

//     char buffer[BUFFERSIZE];

//     bzero(buffer, BUFFERSIZE);
//     int check_index = 0, read_index = 0, start_line = 0;
//     ssize_t recv_data;
//     http::HttpRequestParser::PARSE_STATE  parse_state = http::HttpRequestParser::PARSE_REQUESTLINE;

//     while (true) {
//         http::HttpRequest  request;

//         recv_data = recv(clientSocket.fd, buffer + read_index, BUFFERSIZE - read_index, 0);
//         if (recv_data == -1) {
//             std::cout << "reading faild" << std::endl;
//             exit(0);
//         }
//         if (recv_data == 0) {
//             std::cout << "connection closed by peer" << std::endl;
//             break;
//         }
//         read_index += recv_data;

//         http::HttpRequestParser::HTTP_CODE  retcode = http::HttpRequestParser::parse_content(
//                 buffer, check_index, read_index, parse_state, start_line, request);

//         if (retcode == http::HttpRequestParser::NO_REQUEST) {
//             continue;
//         }

//         if (retcode == http::HttpRequestParser::GET_REQUEST) {
//             HttpResponse response(true);
//             header(request, response);
//             getMime(request, response);
//             static_file(response, "/Users/lichunlin/CLionProjects/webserver/version_0.1");
//             send(response, clientSocket);
//         } else {
//             std::cout << "Bad Request" << std::endl;
//         }
//     }
// }

void wrz_server::Web_Server::header(const HttpRequest &request,  HttpResponse &response) {
    if (request.mVersion == HttpRequest::HTTP_11) {
        response.setVersion(HttpRequest::HTTP_11);
    } else {
        response.setVersion(HttpRequest::HTTP_10);
    }
    response.addHeader("Server", "LC WebServer");
}


// 获取Mime 同时设置path到response
void wrz_server::Web_Server::getMime(const http::HttpRequest &request, http::HttpResponse &response) {
    std::string filepath = request.mUri;
    std::string mime;
    int pos;
    if ((pos = filepath.rfind('?')) != std::string::npos) {
        filepath.erase(filepath.rfind('?'));
    }

    if (filepath.rfind('.') != std::string::npos){
        mime = filepath.substr(filepath.rfind('.'));
    }
    decltype(http::Mime_map)::iterator it;

    if ((it = http::Mime_map.find(mime)) != http::Mime_map.end()) {
        response.setMime(it->second);
    } else {
        response.setMime(http::Mime_map.find("default")->second);
    }
    response.setFilePath(filepath);
}

void wrz_server::Web_Server::static_file(HttpResponse &response, const char *basepath) {
    struct stat file_stat;
    char file[strlen(basepath) + strlen(response.filePath().c_str())+1];
    strcpy(file, basepath);
    strcat(file, response.filePath().c_str());

    if (stat(file, &file_stat) < 0) {
        response.setStatusCode(HttpResponse::k404NotFound);
        response.setStatusMsg("Not Found");
        response.setFilePath(std::string(basepath)+"/404.html");
        return;
    }

    if(!S_ISREG(file_stat.st_mode)){
        response.setStatusCode(HttpResponse::k403forbiden);
        response.setStatusMsg("ForBidden");
        response.setFilePath(std::string(basepath)+"/403.html");
        return;
    }

    response.setStatusCode(HttpResponse::k200Ok);
    response.setStatusMsg("OK");
    response.setFilePath(file);
    return;
}

void wrz_server::Web_Server::send(const http::HttpResponse &response, int client_fd) {
    char header[MAX_SIZE];
    bzero(header, '\0');
    const char *internal_error = "Internal Error";
    struct stat file_stat;
    response.appenBuffer(header);
    if (stat(response.filePath().c_str(), &file_stat) < 0) {
        sprintf(header, "%sContent-length: %d\r\n\r\n", header, strlen(internal_error));
        sprintf(header, "%s%s", header, internal_error);
        ::send(client_fd, header, strlen(header), 0);
        return;
    }

    int filefd = ::open(response.filePath().c_str(), O_RDONLY);
    if (filefd < 0) {
        sprintf(header, "%sContent-length: %d\r\n\r\n", header, strlen(internal_error));
        sprintf(header, "%s%s", header, internal_error);
        ::send(client_fd, header, strlen(header), 0);
        return;
    }

    sprintf(header,"%sContent-length: %d\r\n\r\n", header, file_stat.st_size);
    ::send(client_fd, header, strlen(header), 0);
    void *mapbuf = mmap(NULL, file_stat.st_size, PROT_READ, MAP_PRIVATE, filefd, 0);
    ::send(client_fd, mapbuf, file_stat.st_size, 0);
    munmap(mapbuf, file_stat.st_size);
    close(filefd);
    return;
err:
    sprintf(header, "%sContent-length: %d\r\n\r\n", header, strlen(internal_error));
    sprintf(header, "%s%s", header, internal_error);
    ::send(client_fd, header, strlen(header), 0);
    return;
}