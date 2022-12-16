
#include<cstring>
#include<cstdlib>
#include<cstdio>

#include<pthread.h>

#define LL_ADD(item, list) do{\
    item->prev = NULL; \
    item->next = list; \
    list = item; \
}while(0)

#define LL_REMOVE(item, list) do{\
    if(item->prev != NULL) item->prev->next = item->next;\
    if(item->next != NULL) item->next->prev = item->prev;\
    if(list == item) list = item->next;\
    item->prev = item->next = NULL;\
}while(0)


typedef struct  NWORKER
{
    pthread_t thread;
    int terminate;
    struct NWORKQUEUE *workqueue;
    struct NWORKER *prev;
    struct NWORKER *next;
} nWorker;

typedef struct NJOB
{
    void (*job_function)(struct  NJOB *job);
    void *user_data;
    struct NJOB *prev;
    struct NJOB *next;
} nJob;

typedef struct NWORKQUEUE
{
    struct NWORKER *workers;
    struct NJOB *waiting_jobs;
    pthread_mutex_t jobs_mtx;
    pthread_cond_t jobs_cond;
} nWorkQueue;

typedef nWorkQueue nThreadPool;


static void *ntyWorkerThread(void *ptr);
int ntyThreadPoolCreate(nThreadPool *workqueue, int numWorkers);
void ntyThreadPoolQueue(nThreadPool *workqueue, nJob *job);
