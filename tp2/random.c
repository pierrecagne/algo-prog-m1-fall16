#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv){

  srand((unsigned) time(NULL)); //initialize random generation
  int r = rand(); //r is now a random number
  printf("%d is random.\n", r);
  
  return EXIT_SUCCESS;
}
