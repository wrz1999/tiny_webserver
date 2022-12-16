#include "../include/ntyreactor.h"
#include "../include/export_fun.h"
using namespace std;

int main(int argc, char *argv[])
{
    unsigned short port = SERVER_PORT;
    if(argc == 2)
    {
        port = atoi(argv[1]);
    }
    ntyreactor* reactor = new ntyreactor;
    int i;
    int sockfds[PORT_COUNT] = {0};
    for(i = 0; i < PORT_COUNT; i++)
    {
        sockfds[i] = init_sock(port + i);
        reactor->ntyreactor_addlistener(sockfds[i], accept_cb);

    }
    reactor->ntyreactor_run();
    delete reactor;
    // free(reactor);
    for(i = 0; i < PORT_COUNT; i++)
    {
        close(sockfds[i]);
    }
    return 0;
}