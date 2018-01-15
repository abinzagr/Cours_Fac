#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <pthread.h>

#define MAX 16
static pthread_mutex_t  mutex = PTHREAD_MUTEX_INITIALIZER;
int n,somme=0;
typedef bool echiquier[MAX][MAX];


static bool ok (int n, int ligne, int colonne, echiquier e);





void 
nreines (int n, int ligne, echiquier e, int *cpt)
{
  for (int col = 0; col < n; col++)
    if (ok (n, ligne, col, e))
    {
      if (ligne == n - 1)
	(*cpt)++;
      else
      {
	e[ligne][col] = true;
	nreines (n, ligne + 1, e, cpt);
	e[ligne][col] = false;
      }
    }
}


static bool
ok (int n, int ligne, int colonne, echiquier e)
{
  int l, c;
  for (l = 0; l < ligne; l++)
    if (e[l][colonne])
      return false;

  for (l = ligne - 1, c = colonne - 1; l >= 0 && c >= 0; l--, c--)
    if (e[l][c])
      return false;

  for (l = ligne - 1, c = colonne + 1; l >= 0 && c <= n; l--, c++)
    if (e[l][c])
      return false;
  return true;
}


void *Delegnreine(void *p)
{	echiquier e;
	int cpt=0;

	memset (e, 0, sizeof (e));
	int i =(int)p;
	e[0][i]=true;
	nreines (n, 1, e, &cpt);
	printf("threads :%d\t cpt:%d\n",i,cpt);
	pthread_mutex_lock(& mutex);
	somme += cpt;
	pthread_mutex_unlock(& mutex);
	return NULL;
}



void 
usage (char *s)
{
  fprintf (stderr, "%s entier", s);
  exit (EXIT_FAILURE);
}

int
main (int argc, char *argv[])
{
  echiquier e;
  int cpt = 0;
  char *endptr;

  if (argc < 2)
    usage (argv[0]);

  n = strtoul (argv[1], &endptr, 10);

  if (*endptr != 0)
    usage (argv[1]);

  memset (e, 0, sizeof (e));
  pthread_t pid[n];
  for(int i=0;i<n;i++){
	pthread_create(&pid[i],NULL,Delegnreine,(void*)i);
  }
  for(int i=0;i<n;i++){
	pthread_join(pid[i],NULL);
}

  printf("somme: %d\n",somme);
  

  return EXIT_SUCCESS;
}

