
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#define BUFFER_LENGTH           4096
#define MAX_EPOLL_EVENTS        1024
#define SERVER_PORT             8080
#define PORT_COUNT              5
#define HTTP_METHOD_GET        0
#define HTTP_METHOD_POST    1
#define HTTP_WEBSERVER_HTML_ROOT    "html"

typedef int (*NCALLBACK)(int, int, void*);