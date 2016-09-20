#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){

  int choice;

  printf("1. short\n\
2. unsigned short\n\
3. int\n\
4. unsigned int\n\
5. long\n\
6. unsigned long\n\
Type to use (enter corresponding number): ");
  scanf("%d", &choice);

  switch(choice){
  case 1:{
    short u = 1, v = 1;

    while(v>=u){
      v = v+u;
      u = v-u;
      printf ("%hd\n", u);
    }

    break;
  }
  case 2:{
    short unsigned u = 1, v = 1;

    while(v>=u){
      v = v+u;
      u = v-u;
      printf ("%hu\n", u);
    }

    break;
  }
  case 3:{
    int u = 1, v = 1;

    while(v>=u){
      v = v+u;
      u = v-u;
      printf ("%d\n", u);
    }

    break;
  }
  case 4:{
    int unsigned u = 1, v = 1;

    while(v>=u){
      v = v+u;
      u = v-u;
      printf ("%u\n", u);
    }

    break;
  }
  case 5:{
    long u = 1, v = 1;

    while(v>=u){
      v = v+u;
      u = v-u;
      printf ("%ld\n", u);
    }

    break;
  }
  case 6:{
    long unsigned u = 1, v = 1;
    
    while(v>=u){
      v = v+u;
      u = v-u;
      printf ("%lu\n", u);
    }
    
    break;
  }
  default:
    printf("Not a valid choice.\n");
  }
      
    
  return EXIT_SUCCESS;
}
