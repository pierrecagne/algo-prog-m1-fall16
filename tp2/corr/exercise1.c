/* 
   file: exercice1.c
   date: last updated on 27/09/2016
   ---
   random generator in a integer interval
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
  /* initialize the seed for the function rand
     use it only ONCE in the all program (unless very specific purpose) */
  srand(time(NULL));
  
  int n = 100;
  int r = rand()%100;
  printf("%d is a random integer in [0,%d[\n", r, n);

  // One can extend this idea to any integer interval
  int inf = 19, sup = 83;
  printf("%d is a random integer in [%d,%d[\n", (rand()%(sup-inf))+inf, inf, sup);
  printf("%d is a random integer in ]%d,%d]\n", (rand()%(sup-inf))+inf+1, inf, sup);
  printf("%d is a random integer in [%d,%d]\n", (rand()%(sup+1-inf))+inf, inf, sup);
  printf("%d is a random integer in ]%d,%d[\n", (rand()%(sup-inf-1))+inf+1, inf, sup);
  
  return EXIT_SUCCESS;
}
