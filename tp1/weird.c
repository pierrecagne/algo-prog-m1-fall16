#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
  int n=0;
  printf("The value of n is %d.\n", n);

  if(n=1){
    printf("This case is obviously useless. Or is it?\n");
  }
  else {
    printf("This is what is gonna be printed!\n");
  }

  return EXIT_SUCCESS;
}
