#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv){

  int n = 100;
  srand(time(NULL));

  printf("random number between 0 and %d: %d\n", n, rand() % n);
  
  return EXIT_SUCCESS;
}
