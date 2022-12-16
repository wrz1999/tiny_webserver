#include "ntyreactor.h"
#include "def.h"
#include <sys/stat.h>
#include <sys/sendfile.h>
using namespace std;
// class ntyreactor;
void nty_event_set(ntyevent* ev, int fd, NCALLBACK callback, void *arg);
int nty_event_add(int epfd, int events, ntyevent *ev);
int nty_event_del(int epfd, ntyevent *ev);
int readline(char *allbuf, int idx, char *linebuf);
int http_request(ntyevent *ev);
int http_response(ntyevent *ev);
int accept_cb(int fd, int events, void* arg);
int recv_cb(int fd, int events, void *arg);
int send_cb(int fd, int events, void *arg);
int init_sock(short port);
