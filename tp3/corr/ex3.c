#include <stdio.h>
#include <stdlib.h>

int exp_int (int a, int e);
int str2int (char* s);

int main (int argc, char** argv) {
  // In case of wrong usage.
  if (argc!=3) {
    printf("Usage: %s [n] [m] where n and m are integers.\n", argv[0]);
    exit(EXIT_SUCCESS);
  }
  
  int a = str2int(argv[1]), e = str2int(argv[2]);
  printf("%d^%d = %d\n", a, e, exp_int(a,e));
  
  return EXIT_SUCCESS;
}

int exp_int(int a, int e) {
  int r = 1;
  for(int i = 0; i < e; i++) r*=a;
  return r;
}

// Turn a string with just an integer in it into a int
int str2int (char* s){
  int n;
  if (sscanf(s,"%d",&n)==1) return n;
  else exit(EXIT_FAILURE);
}
