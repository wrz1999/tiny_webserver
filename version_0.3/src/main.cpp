#include "../include/ntyreactor.h"
#include "../include/export_fun.h"
#include "../include/thread_pool.h"
#include "../include/deadlock_sucess.h"
using namespace std;

typedef struct 
{
    ntyreactor *reactor;
    int index;
}end_type;
void thread_fun(nJob *job)
{
    end_type* e = (end_type*)job->user_data;
    ntyreactor *reactor = e->reactor;
    // ntyreactor *reactor = (ntyreactor*)job->user_data;
    cout << e->index << endl;
    reactor->ntyreactor_run(e->index);
    
    delete reactor;
    free(job);
}

int main(int argc, char *argv[])
{
    unsigned short port = SERVER_PORT;
    if(argc == 2)
    {
        port = atoi(argv[1]);
    }

    // init_hook();
	// start_check();


    nThreadPool pool;
    ntyThreadPoolCreate(&pool, 80);
    int i;
    int sockfds[PORT_COUNT] = {0};
    end_type *e = (end_type*)malloc(sizeof(end_type));
    for(i = 0; i < PORT_COUNT; i++)
    {  
    
        ntyreactor* reactor = new ntyreactor;
        sockfds[i] = init_sock(port + i);
        cout << "sockfd:"<<sockfds[i] << endl;
        reactor->ntyreactor_addlistener(sockfds[i], accept_cb);
        nJob *job = (nJob*)malloc(sizeof(nJob));
        if(job == NULL)
        {
            perror("malloc");
            exit(1);
        }
        job->job_function = thread_fun;
        e->reactor = reactor;
        e->index = i;
        job->user_data = e;
        ntyThreadPoolQueue(&pool, job);
    }
    //reactor->ntyreactor_run();
    for(i = 0; i < PORT_COUNT; i++)
    {
        //close(sockfds[i]); //
    }
    getchar();
    return 0;
}