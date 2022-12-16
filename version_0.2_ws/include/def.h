
#ifndef DEF_H_
#define DEF_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <openssl/sha.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

#define BUFFER_LENGTH           4096
#define MAX_EPOLL_EVENTS        1024
#define SERVER_PORT             8080
#define PORT_COUNT              100
#define HTTP_METHOD_GET        0
#define HTTP_METHOD_POST    1
#define HTTP_WEBSERVER_HTML_ROOT    "html"
#define GUID "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"
typedef int (*NCALLBACK)(int, int, void*);

enum {
    WS_HANDSHAKE = 0,
    WS_TRANSMISSION = 1,
    WS_END = 2
};

# endif