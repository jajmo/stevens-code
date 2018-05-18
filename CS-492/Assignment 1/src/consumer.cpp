#include "common.hh"

/**
 * The consumer function
 * Consumes products from the queue, based on the selected scheduling algorithm
 *
 * Precondition: None
 * Postcondition: The products are consumed from the created consumer threads
 *
 * @param void* args The thread ID
 * @return void* Nothing (NULL)
 */
void *consumer(void *args)
{
    int i;
    int thread_id;
    float now;

    thread_id = *((int *) args);

    while (gl_env.consumed_products < gl_env.product_limit)
    {
        pthread_mutex_lock(&gl_env.queue_lock);
        while (gl_env.consumed_products < gl_env.product_limit && products.size() == 0)
        {
            pthread_cond_wait(&gl_env.queue_not_empty, &gl_env.queue_lock);
        }

        clock_gettime(CLOCK_MONOTONIC, &gl_env.now);
        now = gl_env.now.tv_sec  + (gl_env.now.tv_nsec / 1000000000.0);

        if (gl_env.schedule == 0)
        {
            t_product *prod = products.back();
            if (prod != NULL)
            {
                gl_env.total_wait_time +=  now - prod->timestamp;
                if (now - prod->timestamp < gl_env.min_wait_time)
                {
                    gl_env.min_wait_time = now - prod->timestamp;
                }
                if (now - prod->timestamp > gl_env.max_wait_time)
                {
                    gl_env.max_wait_time = now - prod->timestamp;
                }
                for (i = 0; i < prod->life; i++)
                {
                    fib(10);
                }
                std::cout << "[Consumer " << thread_id << "]: Consumed product " << prod->id << std::endl;
                products.pop_back();
                ++gl_env.consumed_products;
                if (now - prod->timestamp < gl_env.min_consumption_time)
                {
                    gl_env.min_consumption_time = now - prod->timestamp;
                }
                if (now - prod->timestamp > gl_env.max_consumption_time)
                {
                    gl_env.max_consumption_time = now - prod->timestamp;
                }
            }
        }
        else
        {
            t_product *prod = products.front();
            if (prod != NULL)
            {
                if (now - prod->timestamp < gl_env.min_wait_time)
                {
                    gl_env.min_wait_time = now - prod->timestamp;
                }
                if (now - prod->timestamp > gl_env.max_wait_time)
                {
                    gl_env.max_wait_time = now - prod->timestamp;
                }
                products.pop_front();
                if (prod->life >= gl_env.quantum)
                {
                    prod->life -= gl_env.quantum;
                    for (i = 0; i < gl_env.quantum; i++)
                    {
                        fib(10);
                    }
                    products.push_back(prod);
                }
                else
                {
                    gl_env.total_wait_time += now - prod->timestamp;
                    for (i = 0; i < prod->life; i++)
                    {
                        fib(10);
                    }
                    std::cout << "[Consumer " << thread_id << "]: Consumed product " << prod->id << std::endl;
                    ++gl_env.consumed_products;
                    if (now - prod->timestamp < gl_env.min_consumption_time)
                    {
                        gl_env.min_consumption_time = now - prod->timestamp;
                    }
                    if (now - prod->timestamp > gl_env.max_consumption_time)
                    {
                        gl_env.max_consumption_time = now - prod->timestamp;
                    }
                }
            }
        }
        fflush(stdout);
        pthread_mutex_unlock(&gl_env.queue_lock);
        pthread_cond_broadcast(&gl_env.queue_not_full);
        usleep(100000);
    }
    //We put this here so that the stop time is last set by the last thread to exit
    clock_gettime(CLOCK_MONOTONIC, &gl_env.consumer_stop_time);
    return NULL;
}