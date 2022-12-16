#include "../include/ntyreactor.h"

ntyreactor::ntyreactor()
{
    this->epfd = epoll_create(1);
    if(this->epfd <= 0)
    {
        cout << "create epfd in" << __func__ << "err " << strerror(errno) << endl;
        return;
    }
    ntyevent* evs = new ntyevent[MAX_EPOLL_EVENTS];
    if(evs == NULL)
    {
        cout << "ntyreactor_alloc ntyevents failed" << endl;
        return;
    }
    memset(evs, 0, (MAX_EPOLL_EVENTS) * sizeof(ntyevent));
    eventblock *block = new eventblock;
    if(block == NULL)
    {
        cout << "ntyreactor_alloc eventblock failed" << endl;
        return;
    }
    memset(block, 0, sizeof(block));
    block->events = evs;
    block->next = NULL;
    this->evblk = block;
    this->blkcnt = 1;
    return;
}
ntyevent* ntyreactor::ntyreactor_find_event_idx(int sockfd)
{
    
    int blkidx = sockfd / MAX_EPOLL_EVENTS;
    int i = 0;
    while (blkidx >= this->blkcnt)
    {
        this->ntyreactor_alloc();
    }
    eventblock* blk = this->evblk;
    while(i < blkidx && blk != NULL)
    {
        blk = blk->next;
    }
    return &blk->events[sockfd % MAX_EPOLL_EVENTS];
}

int ntyreactor::ntyreactor_alloc()
{
    if(this->evblk == NULL)
    {
        return -1;
    }
    eventblock *blk = this->evblk;
    while(blk->next != NULL)
    {
        blk = blk->next;
    }
    ntyevent *evs = new ntyevent[MAX_EPOLL_EVENTS];
    if(evs == NULL)
    {
        return -2;
    }
    memset(evs, 0, (MAX_EPOLL_EVENTS)*sizeof(ntyevent));

    eventblock *block = new eventblock;
    if(block == NULL)
    {
        cout << "ntyreactor_alloc eventblock failed" << endl;
        return -2;
    }
    memset(block, 0, sizeof(eventblock));
    block->events = evs;
    block->next = NULL;

    blk->next = block;
    this->blkcnt++;
    return 0;
}


ntyreactor::~ntyreactor()
{
    close(this->epfd);

    eventblock* blk = this->evblk;
    eventblock* blk_next = NULL;
    while(blk != NULL)
    {
        blk_next = blk->next;
        // free(blk->events);
        // free(blk);
        delete[] blk->events;
        delete blk;
        blk = blk_next;
    }

}
int ntyreactor::ntyreactor_addlistener(int sockfd, NCALLBACK acceptor)
{
    if(this->evblk == NULL)
    {
        return -1;
    }
    ntyevent *event = this->ntyreactor_find_event_idx(sockfd);

    nty_event_set(event, sockfd, acceptor, this);
    nty_event_add(this->epfd, EPOLLIN, event);
    return 0;
}

int ntyreactor::ntyreactor_run()
{
    if(this->epfd < 0)
    {
        return -1;
    }
    if(this->evblk == NULL)
    {
        return -1;
    }
    struct epoll_event events[MAX_EPOLL_EVENTS];
    int i;
    while(1)
    {
        int nready = epoll_wait(this->epfd, events, MAX_EPOLL_EVENTS, 1000);
        if(nready < 0)
        {
            printf("epoll_wait error, exit\n");
            continue;
        }
        for(i = 0; i < nready; i++)
        {
            ntyevent* ev = (ntyevent*)events[i].data.ptr;
            if((events[i].events & EPOLLIN) && (ev->events & EPOLLIN))
            {
                ev->callback(ev->fd, events[i].events, ev->arg);
            }
            if ((events[i].events & EPOLLOUT) && (ev->events & EPOLLOUT)) {
                ev->callback(ev->fd, events[i].events, ev->arg);
            }
        }
    }
    return 0;
}