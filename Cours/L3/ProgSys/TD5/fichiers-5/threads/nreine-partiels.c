#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX 16

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
	int pid;
  if (argc < 2)
    usage (argv[0]);

  int n = strtoul (argv[1], &endptr, 10);

  if (*endptr != 0)
    usage (argv[1]);

  memset (e, 0, sizeof (e));
    for(int i=0;i<n;i++){
		// création des processus fils...
		if( (pid = fork()) == 0) {      
		  // le processus fils continue ici
		  e[0][i]=true;
		  cpt=0;
		  nreines (n, 1, e, &cpt);
		  //printf("%d\n",cpt);
		  printf("fork du processus fils %d (pid = %d)\t cpt:%d\n",i, getpid(),cpt);
		  int fd=open("fichier.txt",O_WRONLY|O_CREAT,0666);
		  lseek(fd,i*sizeof(int),SEEK_SET);
		  write(fd,&cpt,sizeof(int));
		  close(fd);
		  return EXIT_SUCCESS; // fin processus fils
		}
    
	}
  
  // le père attend tout ces fils
  for(int i = 0 ; i < n ; i++) {
    wait(NULL); // j'attend la fin de une de mes fils...
  }
  
  int fdp=open("fichier.txt",O_RDONLY,0666);
  int somme=0;
  
  for(int i = 0 ; i < n ; i++) {  
    read(fdp,&cpt,sizeof(int));
    somme += cpt;
  }
  printf("somme:%d\n",somme);


  return EXIT_SUCCESS;
}

