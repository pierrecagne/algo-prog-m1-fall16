#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv){

  srand(time(NULL));
  int bound = 100;
  int chances = 10;
  int myst;
  
  printf("I'm thinking of a number between 0 and %d...\n", bound);
  myst = rand() % bound;

  while(chances>0){
    int guess;
    printf("Take a guess: "); scanf("%d", &guess);
    if(guess==myst){
      printf("We've got a winner.\n");
      break;
    }
    else if(guess<myst){
      printf("It's more...\n");
    }
    else {
      printf("It's less...\n");
    }
    chances --;
  }
  
  if(chances==0){
    printf("You loose!\n");
  }
  
  return EXIT_SUCCESS;
}
