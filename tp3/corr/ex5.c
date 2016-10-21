/*
  file: ex5.c -- quick modular exponential

  Uses the quick exponential method but keep the results mod n.
 */

#include <stdio.h>
#include <stdlib.h>

int quick_exp_mod (int a, int e, int n);
int str2int (char* s);

int main (int argc, char** argv) {
  // In case of wrong usage.
  if (argc!=4) {
    printf("Usage: %s [a] [e] [n] where a,e and n are integers.\n", argv[0]);
    exit(EXIT_SUCCESS);
  }
  
  int a = str2int(argv[1]), e = str2int(argv[2]), n = str2int(argv[3]);
  printf("%d^%d (mod %d) = %d\n", a, e, n, quick_exp_mod(a,e,n));
  
  return EXIT_SUCCESS;
}

// same as quick_exp, just mod n at each step
int quick_exp_mod (int a, int e, int n) {
  if (e == 0) return 1;
  int t = quick_exp_mod(a,e/2,n);
  return e%2 == 0 ? (t*t) % n : (a*t*t) % n;
}

// Turn a string with just an integer in it into a int
int str2int (char* s){
  int n;
  if (sscanf(s,"%d",&n)==1) return n;
  else exit(EXIT_FAILURE);
}
