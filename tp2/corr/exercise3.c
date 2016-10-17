/*
  file: exercise3.c
  date: last updated on 27/09/2016
  ---
  More or Less: guess the number the computer is thinking about.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
  srand(time(NULL)); //init rand with a seed

  int bound = 100, chances = 10;
  int myst = rand()%bound, guess; //use exercise1 idea for myst

  /* remark the \ that allows to write a string on multiple lines */
  printf("I'm thinking of a number between 0 (included)\
 and %d (excluded)...\n", bound);
  
  while(chances > 0) {
    do { //trap until correct format for guess
      printf("Take a guess (%d chances remaining): ", chances);
      scanf("%d",&guess);
    } while(!(0 <= guess && guess < bound));  

    if(guess == myst) { 
      printf("We've got a winner!\n");
      break; //winning case, exit the while loop
    }
    else if(guess < myst) {
      printf("It's more.\n");
    }
    else {
      printf("It's less.\n");
    }

    chances--; //the user waisted a chance
  }

  /* if chances is 0 there, it means the user used all its chances
     without finding the mystery number */
  if(chances==0){ printf("You're a loser.\n"); }
  
  return EXIT_SUCCESS;
}
