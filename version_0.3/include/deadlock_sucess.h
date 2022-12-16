#ifndef DEAD_H_
#define DEAD_H_

#define _GNU_SOURCE
#include <dlfcn.h>

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdint.h>

#include <unistd.h>

#define THREAD_NUM      10
typedef unsigned long int uint64;

typedef int (*pthread_mutex_lock_t)(pthread_mutex_t *mutex);

pthread_mutex_lock_t pthread_mutex_lock_f;

typedef int (*pthread_mutex_unlock_t)(pthread_mutex_t *mutex);

pthread_mutex_unlock_t pthread_mutex_unlock_f;

#define MAX		100

enum Type {PROCESS, RESOURCE};

struct source_type {

	uint64 id;
	enum Type type;

	uint64 lock_id;
	int degress;
};

struct vertex {

	struct source_type s;
	struct vertex *next;

};

struct task_graph {

	struct vertex list[MAX];
	int num;

	struct source_type locklist[MAX];
	int lockidx;

	pthread_mutex_t mutex;
};

struct task_graph *tg = NULL;
int path[MAX+1];
int visited[MAX];
int k = 0;
int deadlock = 0;


struct vertex *create_vertex(struct source_type type);
int search_vertex(struct source_type type);
void add_vertex(struct source_type type);
int add_edge(struct source_type from, struct source_type to);
int verify_edge(struct source_type i, struct source_type j);
int remove_edge(struct source_type from, struct source_type to);
void print_deadlock(void);
int DFS(int idx);
int search_for_cycle(int idx);
void check_dead_lock(void);
static void *thread_routine(void *args);
void start_check(void);
int search_lock(uint64 lock);
int search_empty_lock(uint64 lock);
int inc(int *value, int add);
void print_locklist(void);
void lock_before(uint64 thread_id, uint64 lockaddr);
void lock_after(uint64 thread_id, uint64 lockaddr);
void unlock_after(uint64 thread_id, uint64 lockaddr);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
int init_hook();

#endif