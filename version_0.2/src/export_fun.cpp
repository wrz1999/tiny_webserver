#include "../include/export_fun.h"

void nty_event_set(ntyevent* ev, int fd, NCALLBACK callback, void *arg)
{
    ev->fd = fd;
    ev->callback = callback;
    ev->events = 0;
    ev->arg = arg;
}
int nty_event_add(int epfd, int events, ntyevent *ev)
{
    struct epoll_event ep_ev = {0, {0}};
    ep_ev.data.ptr = ev;
    ep_ev.events = ev->events = events;
    int op;
    if(ev->status == 1)
    {
        op = EPOLL_CTL_MOD;
    }
    else
    {
        op = EPOLL_CTL_ADD;
        ev->status = 1;
    }
    if(epoll_ctl(epfd, op, ev->fd, &ep_ev) < 0)
    {
        printf("event add failed [fd=%d], events[%d]\n", ev->fd, events);
        return -1;
    }
    return 0;
    
}

int nty_event_del(int epfd, ntyevent *ev)
{
    struct epoll_event ep_ev = {0, {0}};
    if(ev->status != 1)
    {
        return -1;
    }
    ep_ev.data.ptr = ev;
    ev->status = 0;
    epoll_ctl(epfd, EPOLL_CTL_DEL, ev->fd, &ep_ev);
    return 0;
}



int readline(char *allbuf, int idx, char *linebuf) {
    uint len = strlen(allbuf);
    for (; idx < len; idx++) {
        if (allbuf[idx] == '\r' && allbuf[idx + 1] == '\n') {
            return idx + 2;
        }
        else {
            *(linebuf++) = allbuf[idx];
        }
    }
    return -1;
}

int http_request(ntyevent *ev) {
    char line_buffer[1024] = {0};
    printf("[ev->buffer]%s",ev->buffer);
    readline(ev->buffer, 0, line_buffer);
    if (strstr(line_buffer, "GET")) {
        ev->method = HTTP_METHOD_GET;
        //uri
        int i = 0;
        while (line_buffer[sizeof("GET ") + i] != ' ') i++;
        line_buffer[sizeof("GET ") + i] = '\0';
        if(strcmp(line_buffer+sizeof("GET "), "") == 0)
        {
            printf("初始化");
            sprintf(ev->resource, "./%s/%s", HTTP_WEBSERVER_HTML_ROOT, "index.html");
        }
        else
        {
            sprintf(ev->resource, "./%s/%s", HTTP_WEBSERVER_HTML_ROOT, line_buffer + sizeof("GET "));
        }
        
        //Content-Type
        if (strstr(line_buffer + sizeof("GET "), ".")) {
            char *type = strchr(line_buffer + sizeof("GET "), '.') + 1;
            if (strcmp(type, "html") == 0 || strcmp(type, "css") == 0) {
                sprintf(ev->Content_Type, "text/%s", type);
            }
            else if (strcmp(type, "jpg") == 0 || strcmp(type, "png") == 0 || strcmp(type, "ico") == 0) {
                sprintf(ev->Content_Type, "image/%s", type);
            }
        }
        else {
            sprintf(ev->Content_Type, "text/html");
        }
    }
}

int http_response(ntyevent *ev) {
    if (ev == NULL) return -1;
    memset(ev->buffer, 0, BUFFER_LENGTH);
    int filefd = open(ev->resource, O_RDONLY);
    if (filefd == -1) { // return 404
        ev->ret_code = 404;
        ev->length = sprintf(ev->buffer,
                             "HTTP/1.1 404 Not Found\r\n"
                             "Content-Type: %s;charset=utf-8\r\n"
                             "Content-Length: 83\r\n\r\n"
                             "<html><head><title>404 Not Found</title></head><body><H1>404</H1></body></html>\r\n\r\n",
                             ev->Content_Type);
    }
    else {
        struct stat stat_buf;
        fstat(filefd, &stat_buf);
        close(filefd);

        if (S_ISDIR(stat_buf.st_mode)) {
            ev->ret_code = 404;
            ev->length = sprintf(ev->buffer,
                                 "HTTP/1.1 404 Not Found\r\n"
                                 "Content-Type: %s;charset=utf-8\r\n"
                                 "Content-Length: 83\r\n\r\n"
                                 "<html><head><title>404 Not Found</title></head><body><H1>404</H1></body></html>\r\n\r\n",
                                 ev->Content_Type);
        }
        else if (S_ISREG(stat_buf.st_mode)) {
            ev->ret_code = 200;
            ev->length = sprintf(ev->buffer,
                                 "HTTP/1.1 200 OK\r\n"
                                 "Content-Type: %s;charset=utf-8\r\n"
                                 "Content-Length: %ld\r\n\r\n",
                                 ev->Content_Type, stat_buf.st_size);
        }
    }
    return ev->length;
}

int accept_cb(int fd, int events, void* arg)
{
    ntyreactor* reactor = (ntyreactor *)arg;
    if(reactor == NULL)
    {
        return -1;
    }
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);

    int clientfd;
    if((clientfd = accept(fd, (struct sockaddr *)&client_addr, &len)) == -1)
    {
        cout << "accept: " << strerror(errno) << endl;
        return -1;
    }
    if((fcntl(clientfd, F_SETFL, O_NONBLOCK)) < 0)
    {
        cout << __func__ << ": fcntl nonblocking failed, " << MAX_EPOLL_EVENTS << endl;
        return -1;
    }
    ntyevent *event = reactor->ntyreactor_find_event_idx(clientfd);
    nty_event_set(event, clientfd, recv_cb, reactor);
    nty_event_add(reactor->epfd, EPOLLIN, event);
    printf("new connect [%s:%d], pos[%d]\n",
           inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), clientfd); 
    return 0;
}

int recv_cb(int fd, int events, void *arg)
{
    ntyreactor* reactor = (ntyreactor*) arg;
    ntyevent *ev = reactor->ntyreactor_find_event_idx(fd);
    int len = recv(fd, ev->buffer, BUFFER_LENGTH, 0);
    nty_event_del(reactor->epfd, ev);
    if(len > 0)
    {
        ev->length = len;
        ev->buffer[len] = '\0';
        printf("[socket fd=%d recv]\n%s\n", fd, ev->buffer); //http
        http_request(ev);
        nty_event_set(ev, fd, send_cb, reactor);
        nty_event_add(reactor->epfd, EPOLLOUT, ev);
    }
    else if(len == 0)
    {
        cout << "关闭 close" << endl;
        close(ev->fd);
    }
    else
    {
        cout << "关闭 2 close" << endl;
        close(ev->fd);
    }
    return len;
}

int send_cb(int fd, int events, void *arg)
{
    ntyreactor* reactor = (ntyreactor *)arg;
    ntyevent *ev = reactor->ntyreactor_find_event_idx(fd);
    http_response(ev);

    int res_head_len = send(fd, ev->buffer, ev->length, 0);
    if(res_head_len > 0)
    {
        if(ev->ret_code == 200)
        {
            int filefd = open(ev->resource, O_RDONLY);
            struct stat stat_buf;
            fstat(filefd, &stat_buf);
            off_t offset = 0;
            while(offset != stat_buf.st_size)
            {
                int n = sendfile(fd, filefd, &offset, (stat_buf.st_size - offset));
                if(n == -1 && errno == EAGAIN)
                {
                    usleep(5000);
                    continue;
                }
            }
            printf("[resource: %s count:%ld]\r\n", ev->resource, offset);
            close(filefd);
        }
        nty_event_del(reactor->epfd, ev);
        nty_event_set(ev, fd, recv_cb, reactor);
        nty_event_add(reactor->epfd, EPOLLIN, ev);  
    } 
    else
    {
        cout << "关闭 3 close" << endl;
        nty_event_del(reactor->epfd, ev);
        close(ev->fd);
    }
    
    return 0;
}

int init_sock(short port)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(fd, F_SETFL, O_NONBLOCK);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);
    bind(fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(listen(fd, 20) < 0)
    {
        printf("listen failed : %s\n", strerror(errno));
    }
    return fd;
}