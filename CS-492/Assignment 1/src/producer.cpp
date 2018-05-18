#include "common.hh"

/**
 * The producer logic. Used for creating products and adding them to the queue
 *
 * Precondition: The globals are initialized
 * Postcondition: The products are created
 *
 * @param void* args The thread ID
 * @return void* Nothing (NULL)
 */
void *producer(void *args)
{
    int thread_id;

    thread_id = *((int *) args);
    while (gl_env.product_count < gl_env.product_limit)
    {
        pthread_mutex_lock(&gl_env.queue_lock);

        //The check for queue_size > 0 is necessary in the case the queue size is unlimited
        //If that is the case, this loop will be skipped. It allows us to skip adding an additional if()
        while (gl_env.queue_size > 0 && products.size() == gl_env.queue_size && gl_env.product_count < gl_env.product_limit)
        {
            pthread_cond_wait(&gl_env.queue_not_full, &gl_env.queue_lock);
        }
        if (gl_env.product_count < gl_env.product_limit)
        {
            createProduct();
            std::cout << "[Producer " << thread_id << "]: Produced product " << products.front()->id << std::endl;
        }
        fflush(stdout);
        pthread_mutex_unlock(&gl_env.queue_lock);
        pthread_cond_broadcast(&gl_env.queue_not_empty);
        usleep(100000);
    }
    //We put this here so that the stop time is last set by the last thread to exit
    clock_gettime(CLOCK_MONOTONIC, &gl_env.producer_stop_time);
    return NULL;
}