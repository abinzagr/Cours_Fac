#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *HelloGoodbye(void *p)
{
  int n =(int)p;
  printf("%p: bonjour,je suis le thread %d\n ", pthread_self(),n); 
  sleep(1);
  printf("%p: a bientot\n", pthread_self()); 

  return NULL;
}

int 
main(int argc, char *argv[])
{pthread_t pid;
 void *val;	
 int i=1;
 pthread_create(&pid,NULL,HelloGoodbye,(void*)i);
 pthread_join(pid,&val); 
 HelloGoodbye(NULL);

  return EXIT_SUCCESS;
}
