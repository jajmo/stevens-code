#include "common.hh"

//Declare globals
t_gl_env gl_env;
std::deque<t_product *> products;

/**
 * Assignment 1: Inter-Process Communication
 *
 * The purpose of this assignment is to simulate the consumer producer problem using mutexes and condition variables,
 * as well as round-robin and FIFO scheduling.
 *
 * The way the program works:
 * 1. Producer and consumer threads are created based on arguments to the program.
 * 2. The producer/consumer threads run in parallel, with only 1 thread having the mutex lock at a time.
 * 3a. If the producer has the mutex, it waits on the queue not being full. When the queue is not full (signaled by consumer condition variable),
 *     it pushes a new product to the queue and increments the products created count.
 * 3b. If the consumer has the mutex, it waits on the queue not being empty. When the queue is not empty (signaled by producer condition vairable),
 *     it pops either the front or back (depending on the type of scheduling), and either consumes the product or subtracts from the products life and
 *     pushes the product to the back of the queue.
 * 4. Once the production limit is reached, all of the producer threads die.
 * 5. Once the consumption limit is reached, all of the consumer threads die.
 * 6. The stats of the execution are printed, and the main thread dies.
 *
 * Usage: ./processes producerThreads consumerThreads productCount queueSize scheduleAlgorithm quantum seed
 *
 * Precondition: The program recieves 7 command line arguments
 * Postcondition: The program executes based on the parameters
 *
 * @param int argc The number of command line arguments
 * @param char** argv The vector of command line arguments
 * @return int The exit status
 */
int main(int argc, char **argv)
{
    int producer_threads;
    int consumer_threads;
    int product_count;
    int queue_size;
    int schedule_algorithm;
    int quantum;
    int seed;
    int err;
    int i;
    int *ret;
    struct timespec end_time;

    /*
     * Error check and prepare arguments
     *
     * This ensures that valid arguments were entered, and that everything is an int
     */
    if (argc < 8 || argc > 8)
    {
        std::cerr << "Invalid number of command line arguments!" << std::endl;
        return 1;
    }

    producer_threads   = atoi(argv[1]);
    consumer_threads   = atoi(argv[2]);
    product_count      = atoi(argv[3]);
    queue_size         = atoi(argv[4]);
    schedule_algorithm = atoi(argv[5]);
    quantum            = atoi(argv[6]);
    seed               = atoi(argv[7]);

    if (producer_threads == 0 || consumer_threads == 0 || schedule_algorithm > 1 || schedule_algorithm < 0)
    {
        std::cerr << "Please check your arguments!" << std::endl;
        return 1;
    }

    //Initialize the seed for rand()
    srandom(seed);

    //Setup thread variables
    ret = (int *) malloc(sizeof(int));

    pthread_t producerThreads[producer_threads];
    pthread_t consumerThreads[consumer_threads];

    //Production and consumption globals
    gl_env.product_count = 0;
    gl_env.product_limit = product_count;
    gl_env.quantum = quantum;
    gl_env.queue_size = queue_size;
    gl_env.consumed_products = 0;
    gl_env.schedule = schedule_algorithm;

    //Statistics globals
    gl_env.min_consumption_time = 100000.0;
    gl_env.max_consumption_time = 0;
    gl_env.total_wait_time = 0;
    gl_env.min_wait_time = 100000.0;
    gl_env.max_wait_time = 0;

    pthread_mutex_init(&gl_env.queue_lock, NULL);
    pthread_cond_init(&gl_env.queue_not_full, NULL);
    pthread_cond_init(&gl_env.queue_not_empty, NULL);

    //Setup the start run time
    clock_gettime(CLOCK_MONOTONIC, &gl_env.start_time);

    //Generate the producer threads
    for (i = 0; i < producer_threads; i++)
    {
        err = pthread_create(&producerThreads[i], NULL, (void *(*)(void *))producer, &i);
        if (err)
        {
            std::cout << "Producer thread creation error: " << err << std::endl;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &gl_env.consumer_start_time);
    //Generate the consumer threads
    for (i = 0; i < consumer_threads; i++)
    {
        err = pthread_create(&consumerThreads[i], NULL, (void *(*)(void *))consumer, &i);
        if (err)
        {
            std::cout << "Consumer thread creation error: " << err << std::endl;
        }
    }

    //Join the producer threads
    for (i = 0; i < producer_threads; i++)
    {
        pthread_join(producerThreads[i], (void **) &ret);
    }

    //Join the consumer threads
    for (i = 0; i < consumer_threads; i++)
    {
        pthread_join(consumerThreads[i], (void **) &ret);
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);

    //Destroy condition variable and mutexes
    pthread_cond_destroy(&gl_env.queue_not_full);
    pthread_cond_destroy(&gl_env.queue_not_empty);
    pthread_mutex_destroy(&gl_env.queue_lock);

    //Print out benchmarking information
    float now = (end_time.tv_sec - gl_env.start_time.tv_sec) + ((end_time.tv_nsec - gl_env.start_time.tv_nsec) / 1000000000.0);

    std::cout << std::endl;
    std::cout << "-------------------------" << std::endl;
    std::cout << "           STATS         " << std::endl;
    std::cout << "-------------------------" << std::endl;
    std::cout << "Total consumption time: " << (gl_env.consumer_stop_time.tv_sec - gl_env.consumer_start_time.tv_sec) + ((gl_env.consumer_stop_time.tv_nsec - gl_env.consumer_start_time.tv_nsec) / 1000000000.0) << "s" << std::endl;
    std::cout << "-------------------------" << std::endl;
    std::cout << "Min turn-around time: " << gl_env.min_consumption_time << "s" << std::endl;
    std::cout << "Max turn-around time: " << gl_env.max_consumption_time << "s" << std::endl;
    std::cout << "Average turn-around time: " << ((gl_env.consumer_stop_time.tv_sec - gl_env.consumer_start_time.tv_sec) + ((gl_env.consumer_stop_time.tv_nsec - gl_env.consumer_start_time.tv_nsec) / 1000000000.0)) / gl_env.product_limit << "s" << std::endl;
    std::cout << "-------------------------" << std::endl;
    std::cout << "Min wait time: " << gl_env.min_wait_time << "s" << std::endl;
    std::cout << "Max wait time: " << gl_env.max_wait_time << "s" << std::endl;
    std::cout << "Average wait time: " << gl_env.total_wait_time / gl_env.product_limit << "s" << std::endl;
    std::cout << "-------------------------" << std::endl;
    std::cout << "Producer throughput: " << (int) (gl_env.product_limit / ((gl_env.producer_stop_time.tv_sec - gl_env.start_time.tv_sec) + ((gl_env.producer_stop_time.tv_nsec - gl_env.start_time.tv_nsec) / 1000000000.0))) * 60 << " products per minute" << std::endl;
    std::cout << "Consumer throughput: " << (int) (gl_env.product_limit / ((gl_env.consumer_stop_time.tv_sec - gl_env.start_time.tv_sec) + ((gl_env.consumer_stop_time.tv_nsec - gl_env.start_time.tv_nsec) / 1000000000.0))) * 60 << " products per minute" << std::endl;
    std::cout << "-------------------------" << std::endl;
    std::cout << "Total run time: " <<  now << "s" << std::endl;
    std::cout << "-------------------------" << std::endl;

    return 0;
}