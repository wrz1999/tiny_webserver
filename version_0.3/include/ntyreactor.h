#ifndef REACTOR_H_
#define REACTOR_H_


#include "eventblock.h"
#include <sys/epoll.h>
#include <errno.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include<fcntl.h>
#include "export_fun.h"
using namespace std;
class ntyreactor
{
public:
    int epfd;
    int blkcnt;
    eventblock *evblk;


    ntyreactor();
    ntyevent* ntyreactor_find_event_idx(int sockfd);
    int ntyreactor_alloc();
    int ntyreactor_addlistener(int sockfd, NCALLBACK acceptor);
    ~ntyreactor();
    int ntyreactor_run(int index);
};

#endif