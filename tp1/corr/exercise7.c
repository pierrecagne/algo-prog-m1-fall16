#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv){

  int choice;
  
  printf("1. Level 1 -- number between 0 and 10 -- 5 chances\n\
2. Level 2 -- number between 0 and 100 -- 10 chances\n\
3. Level 3 -- number between 0 and 100 -- 5 chances\n\
4. Level 4 -- number between 0 and 1000 -- 10 chances\n\
Level (enter corresponding number): ");
  scanf("%d",&choice);

  srand(time(NULL));
  int bound, chances, myst;
  switch(choice){
  case 1: bound = 10, chances = 5; break;
  case 2: bound = 100, chances = 10; break;
  case 3: bound = 100, chances = 5; break;
  case 4: bound = 1000, chances = 10; break;
  default: printf("Not a valid choice.\n"), exit(EXIT_SUCCESS);
  }
  
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
