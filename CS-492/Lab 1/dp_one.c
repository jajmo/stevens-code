#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#define NUMP 5
#define EATING_COUNT 3

pthread_mutex_t fork_mutex[NUMP];
pthread_cond_t eating_cond;
pthread_mutex_t eating_mutex;
int eating_count;

int main()
{
  int i;
  pthread_t diner_thread[NUMP];
  int dn[NUMP];
  void *diner();
  eating_count = 0;

  for (i=0; i < NUMP; i++)
  {
    pthread_mutex_init(&fork_mutex[i], NULL);
  }
  pthread_cond_init(&eating_cond, NULL);
  pthread_mutex_init(&eating_mutex, NULL);
  for (i=0; i < NUMP; i++)
  {
    dn[i] = i;
    pthread_create(&diner_thread[i], NULL, diner, &dn[i]);
  }
  for (i=0; i < NUMP; i++)
  {
    pthread_join(diner_thread[i], NULL);
  }
  pthread_exit(0);
}

void *diner(void *i)
{
  int v;
  int eating = 0;
  printf("I'm diner %d\n", *((int*) i));
  v = *((int*) i);
  while(eating < 5)
  {
    printf("%d is thinking\n", v);
    sleep(v / 2);
    printf("%d is hungry\n", v);
    pthread_mutex_lock(&eating_mutex);
    while(eating_count >= EATING_COUNT)
    {
      pthread_cond_wait(&eating_cond, &eating_mutex);
    }
    ++eating_count;
    pthread_mutex_lock(&fork_mutex[v]);
    pthread_mutex_lock(&fork_mutex[(v + 1) % NUMP]);
    printf("%d is eating\n", v);
    eating++;
    sleep(1);
    printf("%d is done eating\n", v);
    pthread_mutex_unlock(&fork_mutex[v]);
    pthread_mutex_unlock(&fork_mutex[(v + 1) % NUMP]);
    --eating_count;
    pthread_cond_broadcast(&eating_cond);
    pthread_mutex_unlock(&eating_mutex);
  }
  pthread_exit(NULL);
}
