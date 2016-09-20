#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){

  int year;
  
  printf("Give me a year: ");
  scanf("%d",&year);

  if( ((year%4 == 0) && (year%100 != 0)) || (year%400 == 0) ){
    printf("%d is a leap year.\n", year);
  }
  else{
    printf("%d is not a leap year.\n", year);
  }
  
  return EXIT_SUCCESS;
}
