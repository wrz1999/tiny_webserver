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


int base64_encode(char *in_str, int in_len, char *out_str) {
    BIO *b64, *bio;
    BUF_MEM *bptr = NULL;
    size_t size = 0;

    if (in_str == NULL || out_str == NULL)
        return -1;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_write(bio, in_str, in_len);
    BIO_flush(bio);

    BIO_get_mem_ptr(bio, &bptr);
    memcpy(out_str, bptr->data, bptr->length);
    out_str[bptr->length - 1] = '\0';
    size = bptr->length;

    BIO_free_all(bio);
    return size;
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

// int http_request(ntyevent *ev) {
//     char line_buffer[1024] = {0};
//     printf("[ev->buffer]%s",ev->buffer);
//     readline(ev->buffer, 0, line_buffer);
//     if (strstr(line_buffer, "GET")) {
//         ev->method = HTTP_METHOD_GET;
//         //uri
//         int i = 0;
//         while (line_buffer[sizeof("GET ") + i] != ' ') i++;
//         line_buffer[sizeof("GET ") + i] = '\0';
//         if(strcmp(line_buffer+sizeof("GET "), "") == 0)
//         {
//             printf("初始化");
//             sprintf(ev->resource, "./%s/%s", HTTP_WEBSERVER_HTML_ROOT, "index.html");
//         }
//         else
//         {
//             sprintf(ev->resource, "./%s/%s", HTTP_WEBSERVER_HTML_ROOT, line_buffer + sizeof("GET "));
//         }
        
//         //Content-Type
//         if (strstr(line_buffer + sizeof("GET "), ".")) {
//             char *type = strchr(line_buffer + sizeof("GET "), '.') + 1;
//             if (strcmp(type, "html") == 0 || strcmp(type, "css") == 0) {
//                 sprintf(ev->Content_Type, "text/%s", type);
//             }
//             else if (strcmp(type, "jpg") == 0 || strcmp(type, "png") == 0 || strcmp(type, "ico") == 0) {
//                 sprintf(ev->Content_Type, "image/%s", type);
//             }
//         }
//         else {
//             sprintf(ev->Content_Type, "text/html");
//         }
//     }
// }

// int http_response(ntyevent *ev) {
//     if (ev == NULL) return -1;
//     memset(ev->buffer, 0, BUFFER_LENGTH);
//     int filefd = open(ev->resource, O_RDONLY);
//     if (filefd == -1) { // return 404
//         ev->ret_code = 404;
//         ev->length = sprintf(ev->buffer,
//                              "HTTP/1.1 404 Not Found\r\n"
//                              "Content-Type: %s;charset=utf-8\r\n"
//                              "Content-Length: 83\r\n\r\n"
//                              "<html><head><title>404 Not Found</title></head><body><H1>404</H1></body></html>\r\n\r\n",
//                              ev->Content_Type);
//     }
//     else {
//         struct stat stat_buf;
//         fstat(filefd, &stat_buf);
//         close(filefd);

//         if (S_ISDIR(stat_buf.st_mode)) {
//             ev->ret_code = 404;
//             ev->length = sprintf(ev->buffer,
//                                  "HTTP/1.1 404 Not Found\r\n"
//                                  "Content-Type: %s;charset=utf-8\r\n"
//                                  "Content-Length: 83\r\n\r\n"
//                                  "<html><head><title>404 Not Found</title></head><body><H1>404</H1></body></html>\r\n\r\n",
//                                  ev->Content_Type);
//         }
//         else if (S_ISREG(stat_buf.st_mode)) {
//             ev->ret_code = 200;
//             ev->length = sprintf(ev->buffer,
//                                  "HTTP/1.1 200 OK\r\n"
//                                  "Content-Type: %s;charset=utf-8\r\n"
//                                  "Content-Length: %ld\r\n\r\n",
//                                  ev->Content_Type, stat_buf.st_size);
//         }
//     }
//     return ev->length;
// }

int handshake(ntyevent* ev)
{
    char line_buff[1024] = {0};
    char sha_key[32] = {0};
    char sec_key[32] = {0};
    int idx = 0;
    //找到Sec-WebSocket-Key行
    while(!strstr(line_buff, "Sec-WebSocket-Key"))
    {
        memset(line_buff, 0, 1024);
        idx = readline(ev->buffer, idx, line_buff);
        if(idx == -1)
        {
            return -1;
        }
    }

    strcpy(line_buff, line_buff+strlen("Sec-WebSocket-Key: "));
    strcat(line_buff,GUID);
    SHA1((const unsigned char *)line_buff, strlen(line_buff), (unsigned char*)sha_key);
    base64_encode(sha_key, strlen(sha_key), sec_key);
    memset(ev->buffer, 0, BUFFER_LENGTH);
    ev->length = sprintf(ev->buffer, "HTTP/1.1 101 Switching Protocols\r\n"
                                     "Upgrade: websocket\r\n"
                                     "Connection: Upgrade\r\n"
                                     "Sec-WebSocket-Accept: %s\r\n\r\n", sec_key);
    printf("[handshake response]\n%s\n", ev->buffer);
    return 0;
}

void umask(char *payload, int length, char *mask_key)
{
    int i = 0;
    for(i = 0; i < length; i++)
    {
        payload[i] ^= mask_key[i % 4];
    }
}

char* decode_packet(ntyevent *ev, int *real_len, int *virtual_len)
{
    ws_ophdr *hdr = (ws_ophdr *)ev->buffer;
    printf("decode_packet fin:%d rsv1:%d rsv2:%d rsv3:%d opcode:%d mark:%d\n",
           hdr->fin,
           hdr->rsv1,
           hdr->rsv2,
           hdr->rsv3,
           hdr->opcode,
           hdr->mask);
    char* payload = NULL;
    *virtual_len = hdr->payload_len;
    if(hdr->opcode == 8)
    {
        ev->state_machine = WS_END;
        close(ev->fd);
        return NULL;
    }
    if(hdr->payload_len < 126)
    {
        payload = ev->buffer + sizeof(ws_ophdr) + 4;
        if(hdr->mask)
        {
            umask(payload, hdr->payload_len, ev->buffer+2);
        }
        *real_len = hdr->payload_len;
    }
    else if(hdr->payload_len == 126)
    {
        payload = ev->buffer + sizeof(ws_ophdr) + sizeof(ws_ophdr126);
        ws_ophdr126 *hdr126 = (ws_ophdr126*)(ev->buffer + sizeof(ws_ophdr));
        hdr126->payload_len = ntohs(hdr126->payload_len);
        if(hdr->mask)
        {
            umask(payload, hdr126->payload_len, hdr126->mask_key);
        }
        *real_len = hdr126->payload_len;
    }
    else if(hdr->payload_len = 127)
    {
        payload = ev->buffer + sizeof(ws_ophdr) + sizeof(ws_ophdr127);
        ws_ophdr127 *hdr127 = (ws_ophdr127 *)(ev->buffer + sizeof(ws_ophdr));
        if(hdr->mask)
        {
            umask(payload, hdr127->payload_len, hdr127->mask_key);
        }
        *real_len = hdr127->payload_len;
    }
    printf("virtual len=%d  real_len=%d\n", hdr->payload_len, *real_len);
    return payload;
}

int encode_packet(ntyevent *ev, int real_len, int virtual_len, char *buf)
{
    ws_ophdr head = {0};
    head.fin = 1;
    head.opcode = 1;
    head.payload_len = virtual_len;
    memcpy(ev->buffer, &head, sizeof(ws_ophdr));

    int head_offset = 0;
    if(virtual_len < 126)
    {
        head.payload_len = real_len;
        head_offset = sizeof(ws_ophdr);
    }
    else if(virtual_len == 126)
    {
        ws_ophdr126 hdr126 = {0};
        hdr126.payload_len = htons(real_len);
        memcpy(ev->buffer + sizeof(ws_ophdr), &hdr126, sizeof(unsigned short));
        head_offset = sizeof(ws_ophdr) + sizeof(unsigned short);
    }
    else if(virtual_len == 127)
    {
        ws_ophdr127 hdr127 = {0};
        hdr127.payload_len = real_len;
        memcpy(ev->buffer + sizeof(ws_ophdr) + sizeof(ws_ophdr127), &hdr127, sizeof(long long));
        head_offset = sizeof(ws_ophdr) + sizeof(long long);
    }
    printf("encode_packet fin:%d rsv1:%d rsv2:%d rsv3:%d opcode:%d mark:%d \n",
        head.fin,
        head.rsv1,
        head.rsv2,
        head.rsv3,
        head.opcode,
        head.mask);
    memcpy(ev->buffer + head_offset, buf, real_len);
    return head_offset + real_len;
}

int transmission(ntyevent *ev)
{
    char *payload_buffer = NULL;
    int real_len = 0;
    int virtual_len;
    payload_buffer = decode_packet(ev, &real_len, &virtual_len);
    printf("real_len=[%d] , buf=[%s]\n", real_len, payload_buffer);
    ev->length = encode_packet(ev, real_len, virtual_len, payload_buffer);
}

int websocket_request(ntyevent *ev)
{
    if(ev->state_machine == WS_HANDSHAKE)
    {
        handshake(ev);
        ev->state_machine = WS_TRANSMISSION;
    }
    else if(ev->state_machine == WS_TRANSMISSION)
    {
        transmission(ev);
    }
    else
    {

    }
    return 0;
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
    event->state_machine = WS_HANDSHAKE;
    nty_event_add(reactor->epfd, EPOLLIN, event);
    printf("new connect [%s:%d], pos[%d]\n",
           inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), clientfd); 
    return 0;
}

int recv_cb(int fd, int events, void *arg)
{
    ntyreactor* reactor = (ntyreactor*) arg;
    ntyevent *ev = reactor->ntyreactor_find_event_idx(fd);
    memset(ev->buffer, 0, BUFFER_LENGTH);
    
#if 0
    long len = recv(fd, ev->buffer, BUFFER_LENGTH, 0);

#elif 1
    int len = 0;
    int n = 0;
    while(1)
    {
        n = recv(fd, ev->buffer + len, BUFFER_LENGTH - len, 0);
        printf("[recv data len = %d]\n", n);
        if(n != -1)
        {
            len += n;
        }
        else
        {
            break;
        }
    }
#endif
    nty_event_del(reactor->epfd, ev);
    if(len > 0)
    {
        ev->length = len;
        ev->buffer[len] = '\0';
        //printf("[socket fd=%d recv]\n%s\n", fd, ev->buffer); //http
        //http_request(ev);
        websocket_request(ev);
        
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
    
    printf("[send buffer]\n%s\n", ev->buffer);
    //http_response(ev);

    int res_head_len = send(fd, ev->buffer, ev->length, 0);
    if(res_head_len > 0)
    {
    //     if(ev->ret_code == 200)
    //     {
    //         int filefd = open(ev->resource, O_RDONLY);
    //         struct stat stat_buf;
    //         fstat(filefd, &stat_buf);
    //         off_t offset = 0;
    //         while(offset != stat_buf.st_size)
    //         {
    //             int n = sendfile(fd, filefd, &offset, (stat_buf.st_size - offset));
    //             if(n == -1 && errno == EAGAIN)
    //             {
    //                 usleep(5000);
    //                 continue;
    //             }
    //         }
    //         printf("[resource: %s count:%ld]\r\n", ev->resource, offset);
    //         close(filefd);
    //     }
   
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