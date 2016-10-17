/*
  file: exercise7.c
  date: last updated on 27/09/2016
  ---

  Implement the function 'simulate' that does iterated random draws on
  a given interval. (It directly contains the upgrades proposed in
  question 8.)
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int str2int(char*);
float simulate(int,int,int,int);

int main(int argc, char** argv) {
  // in case of wrong usage
  if (argc != 4) {
    printf("Usage: %s number_of_draws inf_bound sup_bound\n", argv[0]);
    printf("It prints out the frequency of appearence of k\
 among number_of_draws draws in [inf_bound,sup_bound)\
 for every k inside that interval.\n");
    exit(EXIT_FAILURE); }

  //initialize the random function. DO NOT put it inside 'simulate',
  //one only initializes the seed ONCE!
  srandom(time(NULL));

  int n = str2int(argv[1]);
  int inf = str2int(argv[2]), sup = str2int(argv[3]);
  
  for(int i = inf; i < sup; i++){
    printf("%d appears %f%c of the time.\n",i,
	   simulate(n, i, inf, sup)*100, '%');
  }
  
  return EXIT_SUCCESS;
}

// convert a string into an int if possible
int str2int(char* s) {
  int n;
  if (sscanf(s,"%d",&n) == 1) return n;
  else exit(EXIT_FAILURE);
}

float simulate(int ndraw, int val, int inf, int sup) {
  int cmpt = 0;
  for(int i = 0; i < ndraw; i++) {
    if(random()%(sup-inf)+inf == val) cmpt +=1;
  }
  
  return ((float) cmpt)/ndraw;
}
