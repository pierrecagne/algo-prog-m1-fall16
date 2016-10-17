/*
  file: exercise6.c
  date: last updated on 27/09/2016
  ---

  More or Less: let the computer guess the number you're thinking
  about. No more randomness, only dichotomy. And args given by the
  command line.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int str2int(char*);

int main(int argc, char** argv) {
  srandom(time(NULL)); //init seed for rand

  // in case of wrong usage
  if (argc != 3) {
    printf("Usage: '%s bound chances' (where bound and chances are integers).\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  //convert args into their meaningful values
  int bound = str2int(argv[1]), chances = str2int(argv[2]);
  int myst, guess, ans; //ans will be for the user's successive answers
  int min = 0, max = bound; //number is in [min,max[

  do {
    printf("Choose a mystery number x (0 ≤ x < %d): ", bound);
    scanf("%d", &myst);
  } while(myst>=bound);
  do {
    guess = min+(max-min)/2; //the computer take a guess
    do { //get the user to give information about the guess
      printf("Is it %d? [0 for yes/-1 for less/1 for more] ", guess);
      scanf("%d", &ans);
    } while(!(ans > -2 && ans < 2));

    if((ans==-1 && guess <= myst)
       || (ans == 1 && guess >= myst) ) { //the info should be correct
      printf("Trying to mess with me? I quit!\n");
      exit(EXIT_SUCCESS);
    }

    if(ans == -1) max = guess;
    if(ans == 1) min = guess+1;
    
    chances--; //the computer wasted a chance
  } while(chances > 0 && ans != 0);

  /* at that point, the computer wins if and only if it still has some
     chances */
  if(chances > 0){ printf("I won! So happy right now!\n"); }
  else { printf("Oh, man...\n"); }
  
  return EXIT_SUCCESS;
}

// convert a string into an int if possible
int str2int(char* s) {
  int n;
  if (sscanf(s,"%d",&n) == 1) return n;
  else exit(EXIT_FAILURE);
}
