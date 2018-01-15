#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

void perror_and_exit_whenever(int assertion){
  if (assertion)
    {
      perror("");
      exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv){
  int power;
  size_t buffer_size;
  char buf[30];
  int input_file=open(argv[1],O_RDONLY,0666);
  int output_file=open(argv[2],O_WRONLY|O_CREAT,0666);
  int c=1;
  int readok=1;
  int buffer;
  if (argc != 4)
    {
      fprintf(stderr,"%s : <input file name>"
	      " <output filename> <log2 of buffer length> \n", argv[0]);
      return EXIT_FAILURE;
    }
  
  power = strtoul(argv[3], NULL, 10);
  buffer_size = 1 << power;
  
  while(readok !=0){
		readok=read(input_file,buf,buffer_size);
		write(output_file,buf,readok);
	}

  close(output_file);
  close(input_file);	
  return EXIT_SUCCESS;
}
