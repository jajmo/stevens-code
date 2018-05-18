#ifndef _COMMON_HH_
#define _COMMON_HH_

#include <iostream>
#include <cfloat>
#include <pthread.h>
#include <stdlib.h>
#include <queue>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

//A structure that represents a single product
typedef struct s_product
{
    int life;
    float timestamp;
    int id;
} t_product;

//Global environment structure
typedef struct s_gl_env
{
    //Producer globals
    int product_count;
    int product_limit;
    unsigned int queue_size;
    pthread_cond_t queue_not_full;
    struct timespec producer_stop_time;

    //Consumer globals
    int quantum;
    pthread_cond_t queue_not_empty;
    int consumed_products;
    struct timespec consumer_start_time;
    struct timespec consumer_stop_time;

    //The scheduling algorithm to use
    unsigned int schedule;

    //The queue mutex
    pthread_mutex_t queue_lock;

    //Benchmarking variables
    float min_consumption_time;
    float max_consumption_time;
    float total_wait_time;
    float min_wait_time;
    float max_wait_time;
    struct timespec start_time;
    struct timespec now;
} t_gl_env;

extern t_gl_env gl_env;
extern std::deque<t_product *> products;

void  createProduct();
void *producer(void *);
void *consumer(void *);
unsigned int fib(unsigned int num);

#endif