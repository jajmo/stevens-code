#include "common.hh"

/**
 * Create a new product
 *
 * Precondition: None
 * Postcondition: The product is created and pushed to the front of the queue
 */
void createProduct()
{
    struct timespec tmp;
    clock_gettime(CLOCK_MONOTONIC, &tmp);
    t_product *prod = (t_product *) malloc(sizeof(t_product));
    prod->timestamp = tmp.tv_sec + (tmp.tv_nsec / 1000000000.0);
    prod->id = random() % 1024;
    prod->life = random() % 1024;
    products.push_front(prod);
    gl_env.product_count++;
}