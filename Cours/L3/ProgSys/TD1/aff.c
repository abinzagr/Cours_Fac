#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc,char *argv[])
{ printf("s3\n");
  printf("S1\n");
  fprintf(stderr,"E1");
  printf("S2");
  fprintf(stderr,"E2");
  //printf("s3");
  //*((*int) NULL)=42; /* seg fault */
}
