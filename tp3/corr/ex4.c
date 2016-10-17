#include <stdio.h>
#include <stdlib.h>

int quick_exp (int a, int e);
int str2int (char* s);

int main (int argc, char** argv) {
  // In case of wrong usage.
  if (argc!=3) {
    printf("Usage: %s [n] [m] where n and m are integers.\n", argv[0]);
    exit(EXIT_SUCCESS);
  }
  
  int a = str2int(argv[1]), e = str2int(argv[2]);
  printf("%d^%d = %d\n", a, e, quick_exp(a,e));
  
  return EXIT_SUCCESS;
}

int quick_exp(int a, int e) {
  if (e == 0) return 1;
  long t = quick_exp(a,e/2);
  return e%2 == 0 ? t*t : a*t*t;
}

// Turn a string with just an integer in it into a int
int str2int (char* s){
  int n;
  if (sscanf(s,"%d",&n)==1) return n;
  else exit(EXIT_FAILURE);
}
