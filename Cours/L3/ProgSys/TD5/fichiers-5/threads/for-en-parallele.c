#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
static pthread_mutex_t  mutex = PTHREAD_MUTEX_INITIALIZER;


unsigned long volatile k = 0;
const unsigned long MAX = 100 * 1000;

void *for_en_parallele(void *p)
{ 
  double j=0;
  for(unsigned long i=0; i < MAX; i++)
    j++;	
  pthread_mutex_lock(& mutex);
  k+=j;
  pthread_mutex_unlock(& mutex);
  return NULL;
}

int 
main(int argc, char *argv[])
{

  int n = atoi(argv[1]);
  pthread_t tids[n];
 
  for(int i = 0; i <n ; i++)
    pthread_create(tids + i, NULL, for_en_parallele, NULL);

  for(int i = 0; i <n ; i++)
    pthread_join(tids[i],NULL);

  printf("%lu\n",k);

  return EXIT_SUCCESS;
}
