#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv[])
{
int i = 0;
int tube[2];
int in = 0;//STDIN_FILENO;
int out = 0;//STDOUT_FILENO;
int nb = atoi(argv[1]);
do {
pipe(tube);
if(fork() == 0) {
close(tube[1]); in = tube[0];
} else {
close(tube[0]); out = tube[1];
break;
}
i++;
} while(i < nb-1);
printf("Processus %d\n", i);
return 0;
}
