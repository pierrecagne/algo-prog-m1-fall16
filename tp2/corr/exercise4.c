/*
  file: exercise4.c
  date: last updated on 27/09/2016
  ---
  More or Less: let the computer guess the number you're thinking
  about.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
  srandom(time(NULL)); //init seed for rand

  int bound = 100, chances = 10; //same old, same old
  int myst, guess, ans; //ans will be for the user's succesive answers

  printf("Choose a mystery number x (0 ≤ x < 100): ");
  scanf("%d", &myst);
  do {
    guess = random()%bound; //the computer take a guess
    do { //get the user to give information about the guess
      printf("Is it %d? [0 for yes/-1 for less/1 for more] ", guess);
      scanf("%d", &ans);
    } while(!(ans > -2 && ans < 2));

    if((ans==-1 && guess <= myst)
       || (ans == 1 && guess >= myst) ) { //the info should be correct
      printf("Trying to mess with me? I quit!\n");
      exit(EXIT_SUCCESS);
    }
    
    chances--; //the computer wasted a chance
  } while(chances > 0 && ans != 0);

  /* at that point, the computer wins if and only if it still has some
     chances */
  if(chances > 0){ printf("I won! So happy right now!\n"); }
  else { printf("Oh, man...\n"); }
  
  return EXIT_SUCCESS;
}
