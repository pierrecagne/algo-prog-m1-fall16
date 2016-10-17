#include <stdio.h>
#include <stdlib.h>
#define MAX_NAME 50

char perfect_square(int);
void hello_name(char*);

int main (int argc, char** argv) {
  char str[MAX_NAME];
  printf("Enter your name: "); scanf("%s",str);
  hello_name(str);

  int n;
  printf("Enter a square: "); scanf("%d",&n);
  if (perfect_square(n)) { printf("Good job!\n") ; }
  else { printf("Not square...\n") ; }
  
  return EXIT_SUCCESS;
}

char perfect_square(int n) {
  int i;
  for(i = 0; i*i<n; i++);
  return i*i == n ? 1 : 0;
}

void hello_name (char* name) {
  printf("Hello, %s!\n", name);
}
