/*
  file: exercice2.c
  date: last updated on 27/09/2016
  ---
  experimental verification of the distribution of exo1's random
  generator
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv){

  srand(time(NULL)); //initialize random generation
  int ntry = 1000000, wit = 42, sup = 100;
  
  int nwit = 0;
  for(int i=0; i<ntry; i++) {
    if(rand()%sup == wit){ nwit++; }
  }

  /* multiplying nwit (int) with 100. (double) gives a double as nwit
     is implicitly converted to a double */
  printf("%d occured %f%c of the time.\n", wit, (nwit*100.)/ntry,'%');
  
  return EXIT_SUCCESS;
}
