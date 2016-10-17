/*
  file: exercise9.c
  date: last updated on 27/09/2016
  ---

  Evaluates the frequency of being prime in a given interval.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int str2int(char*);
char prime(unsigned int);

int main(int argc, char** argv) {
  
  // in case of wrong usage
  if (argc != 3) {
    printf("Usage: '%s ndraws max'\
(where ndraws and max are integers).\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  srandom(time(NULL)); //init seed for rand

  //retrieve the args
  int ndraws = str2int(argv[1]), max = str2int(argv[2]);
  int cmpt = 0;
  for(int i = 0; i < ndraws; i++){
    if(prime(random()%max)) cmpt +=1 ;
  }
  printf("Prime %f%c of the time in [0,%d)\n",
	 ((float) cmpt)/ndraws*100, '%', max);
  
  return EXIT_SUCCESS;
}

char prime(unsigned int n) {
  if(n < 2) return 0;
  for(int i = 2; i*i <= n; i++){
    if (n%i == 0) return 0;
  }
  return 1;
}

// convert a string into an int if possible
int str2int(char* s) {
  int n;
  if (sscanf(s,"%d",&n) == 1) return n;
  else exit(EXIT_FAILURE);
}
