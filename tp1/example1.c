#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){

  printf("Hello, World!\n");

  int n = 10;
  while(n>0){
    printf("%d...", n);
    n--;
  }
  printf("Go!\n");
  
  return EXIT_SUCCESS;
}
