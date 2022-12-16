#include "../include/deadlock_sucess.h"


#if 1 // graph


struct vertex *create_vertex(struct source_type type) {

	struct vertex *tex = (struct vertex *)malloc(sizeof(struct vertex ));

	tex->s = type;
	tex->next = NULL;

	return tex;

}


int search_vertex(struct source_type type) {

	int i = 0;

	for (i = 0;i < tg->num;i ++) {

		if (tg->list[i].s.type == type.type && tg->list[i].s.id == type.id) {
			return i;
		}

	}

	return -1;
}

void add_vertex(struct source_type type) {

	if (search_vertex(type) == -1) {

		tg->list[tg->num].s = type;
		tg->list[tg->num].next = NULL;
		tg->num ++;

	}

}


int add_edge(struct source_type from, struct source_type to) {

	add_vertex(from);
	add_vertex(to);

	struct vertex *v = &(tg->list[search_vertex(from)]);

	while (v->next != NULL) {
		v = v->next;
	}

	v->next = create_vertex(to);

}


int verify_edge(struct source_type i, struct source_type j) {

	if (tg->num == 0) return 0;

	int idx = search_vertex(i);
	if (idx == -1) {
		return 0;
	}

	struct vertex *v = &(tg->list[idx]);

	while (v != NULL) {

		if (v->s.id == j.id) return 1;

		v = v->next;
		
	}

	return 0;

}


int remove_edge(struct source_type from, struct source_type to) {

	int idxi = search_vertex(from);
	int idxj = search_vertex(to);

	if (idxi != -1 && idxj != -1) {

		struct vertex *v = &tg->list[idxi];
		struct vertex *remove;

		while (v->next != NULL) {

			if (v->next->s.id == to.id) {

				remove = v->next;
				v->next = v->next->next;

				free(remove);
				break;

			}

			v = v->next;
		}

	}

}


void print_deadlock(void) {

	int i = 0;

	printf("deadlock : ");
	for (i = 0;i < k-1;i ++) {

		printf("%ld --> ", tg->list[path[i]].s.id);

	}

	printf("%ld\n", tg->list[path[i]].s.id);

}

int DFS(int idx) {

	struct vertex *ver = &tg->list[idx];
	if (visited[idx] == 1) {

		path[k++] = idx;
		print_deadlock();
		deadlock = 1;
		
		return 0;
	}

	visited[idx] = 1;
	path[k++] = idx;

	while (ver->next != NULL) {

		DFS(search_vertex(ver->next->s));
		k --;
		
		ver = ver->next;

	}

	
	return 1;

}


int search_for_cycle(int idx) {

	

	struct vertex *ver = &tg->list[idx];
	visited[idx] = 1;
	k = 0;
	path[k++] = idx;

	while (ver->next != NULL) {

		int i = 0;
		for (i = 0;i < tg->num;i ++) {
			if (i == idx) continue;
			
			visited[i] = 0;
		}

		for (i = 1;i <= MAX;i ++) {
			path[i] = -1;
		}
		k = 1;

		DFS(search_vertex(ver->next->s));
		ver = ver->next;
	}

}





#endif







void check_dead_lock(void) {

	int i = 0;

	deadlock = 0;
	for (i = 0;i < tg->num;i ++) {
		if (deadlock == 1) break;
		search_for_cycle(i);
	}

	if (deadlock == 0) {
		printf("no deadlock\n");
	}

}


static void *thread_routine(void *args) {

	while (1) {

		sleep(5);
		check_dead_lock();

	}

}


void start_check(void) {

	tg = (struct task_graph*)malloc(sizeof(struct task_graph));
	tg->num = 0;
	tg->lockidx = 0;
	
	pthread_t tid;

	pthread_create(&tid, NULL, thread_routine, NULL);

}


#if 1

int search_lock(uint64 lock) {

	int i = 0;
	
	for (i = 0;i < tg->lockidx;i ++) {
		
		if (tg->locklist[i].lock_id == lock) {
			return i;
		}
	}

	return -1;
}

int search_empty_lock(uint64 lock) {

	int i = 0;
	
	for (i = 0;i < tg->lockidx;i ++) {
		
		if (tg->locklist[i].lock_id == 0) {
			return i;
		}
	}

	return tg->lockidx;

}

#endif

int inc(int *value, int add) {

	int old;

	__asm__ volatile(
		"lock;xaddl %2, %1;"
		: "=a"(old)
		: "m"(*value), "a" (add)
		: "cc", "memory"
	);
	
	return old;
}


void print_locklist(void) {

	int i = 0;

	printf("print_locklist: \n");
	printf("---------------------\n");
	for (i = 0;i < tg->lockidx;i ++) {
		printf("threadid : %ld, lockid: %ld\n", tg->locklist[i].id, tg->locklist[i].lock_id);
	}
	printf("---------------------\n\n\n");
}

void lock_before(uint64 thread_id, uint64 lockaddr) {


	int idx = 0;
	// list<threadid, toThreadid>

	for(idx = 0;idx < tg->lockidx;idx ++) {
		if ((tg->locklist[idx].lock_id == lockaddr)) {

			struct source_type from;
			from.id = thread_id;
			from.type = PROCESS;
			add_vertex(from);

			struct source_type to;
			to.id = tg->locklist[idx].id;
			tg->locklist[idx].degress++;
			to.type = PROCESS;
			add_vertex(to);
			
			if (!verify_edge(from, to)) {
				add_edge(from, to); // 
			}

		}
	}
}

void lock_after(uint64 thread_id, uint64 lockaddr) {

	int idx = 0;
	if (-1 == (idx = search_lock(lockaddr))) {  // lock list opera 

		int eidx = search_empty_lock(lockaddr);
		
		tg->locklist[eidx].id = thread_id;
		tg->locklist[eidx].lock_id = lockaddr;
		
		inc(&tg->lockidx, 1);
		
	} else {


		struct source_type from;
		from.id = thread_id;
		from.type = PROCESS;

		struct source_type to;
		to.id = tg->locklist[idx].id;
		tg->locklist[idx].degress --;
		to.type = PROCESS;

		if (verify_edge(from, to))
			remove_edge(from, to);

		
		tg->locklist[idx].id = thread_id;

	}
	
}

void unlock_after(uint64 thread_id, uint64 lockaddr) {


	int idx = search_lock(lockaddr);

	if (tg->locklist[idx].degress == 0) {
		tg->locklist[idx].id = 0;
		tg->locklist[idx].lock_id = 0;
		//inc(&tg->lockidx, -1);
	}
	
}



int pthread_mutex_lock(pthread_mutex_t *mutex) {

    pthread_t selfid = pthread_self(); //
    
	lock_before(selfid, (uint64)mutex);
    pthread_mutex_lock_f(mutex);
	lock_after(selfid, (uint64)mutex);

}

int pthread_mutex_unlock(pthread_mutex_t *mutex) {


	pthread_t selfid = pthread_self();

    pthread_mutex_unlock_f(mutex);
	unlock_after(selfid, (uint64)mutex);


}

int init_hook() {

    pthread_mutex_lock_f = dlsym(RTLD_NEXT, "pthread_mutex_lock");

    pthread_mutex_unlock_f = dlsym(RTLD_NEXT, "pthread_mutex_unlock");

}



#if 0  //debug

pthread_mutex_t mutex_1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_4 = PTHREAD_MUTEX_INITIALIZER;

void *thread_rountine_1(void *args)
{
	pthread_t selfid = pthread_self(); //

	printf("thread_routine 1 : %ld \n", selfid);
	
    pthread_mutex_lock(&mutex_1);
    sleep(1);
    pthread_mutex_lock(&mutex_2);

    pthread_mutex_unlock(&mutex_2);
    pthread_mutex_unlock(&mutex_1);

    return (void *)(0);
}

void *thread_rountine_2(void *args)
{
	pthread_t selfid = pthread_self(); //

	printf("thread_routine 2 : %ld \n", selfid);
	
    pthread_mutex_lock(&mutex_2);
    sleep(1);
    pthread_mutex_lock(&mutex_3);

    pthread_mutex_unlock(&mutex_3);
    pthread_mutex_unlock(&mutex_2);

    return (void *)(0);
}

void *thread_rountine_3(void *args)
{
	pthread_t selfid = pthread_self(); //

	printf("thread_routine 3 : %ld \n", selfid);

    pthread_mutex_lock(&mutex_3);
    sleep(1);
    pthread_mutex_lock(&mutex_4);

    pthread_mutex_unlock(&mutex_4);
    pthread_mutex_unlock(&mutex_3);

    return (void *)(0);
}

void *thread_rountine_4(void *args)
{
	pthread_t selfid = pthread_self(); //

	printf("thread_routine 4 : %ld \n", selfid);
	
    pthread_mutex_lock(&mutex_4);
    sleep(1);
    pthread_mutex_lock(&mutex_1);

    pthread_mutex_unlock(&mutex_1);
    pthread_mutex_unlock(&mutex_4);

    return (void *)(0);
}


int main()
{

    
    init_hook();
	start_check();

	printf("start_check\n");

    pthread_t tid1, tid2, tid3, tid4;
    pthread_create(&tid1, NULL, thread_rountine_1, NULL);
    pthread_create(&tid2, NULL, thread_rountine_2, NULL);
    pthread_create(&tid3, NULL, thread_rountine_3, NULL);
    pthread_create(&tid4, NULL, thread_rountine_4, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);

    return 0;
}

#endif



