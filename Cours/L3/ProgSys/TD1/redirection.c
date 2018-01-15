#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


void verifier(int i, char *s)
{
  if (!i) {
    perror (s);
    exit (EXIT_FAILURE);
  }
}

void quelques_prints (void)
{
  printf ("Juste");
  printf (" histoire");
  printf (" de tester...\n");
  printf ("...que la redirection");
  printf (" marche !\n");
}

void rediriger_vers (void (*f)(void), char *file)
{ /* code complet*/
	/*char c='a';
  int tempout=open(file,O_WRONLY|O_CREAT,0666);
  int oldout=dup(1);
  close(1);
  int newout= dup(tempout);
  write(1,&c,sizeof(char));
  close(tempout);
  close(1);
  newout=dup(oldout);
  close(oldout);*/
  int fd=open(file,O_WRONLY|O_CREAT,0666);
  dup2(fd,1);
  f();
  dup2(1,fd);
  close(fd);
  close(1);
	}
  


int main(int argc, char *argv[])
{
  printf ("*** DEBUT ***\n");

  rediriger_vers (quelques_prints, "sortie.txt");

  printf ("*** FIN ***\n");

  return EXIT_SUCCESS;
}
  
