#include <stdio.h>
#include <stdlib.h>

int gcd (int a, int b);
int str2int (char* s);

int main (int argc, char** argv) {
  // In case of wrong usage.
  if (argc!=3) {
    printf("Usage: %s [n] [m] where n and m are integers.\n", argv[0]);
    exit(EXIT_SUCCESS);
  }
  
  int a = str2int(argv[1]), b = str2int(argv[2]);
  printf("gcd(%d,%d) = %d\n", a, b, gcd(a,b));
  
  return EXIT_SUCCESS;
}

// Compute gcd
int gcd (int a, int b) {
  if (b > a) return gcd(b,a);
  else return b==0 ? a : gcd(b,a%b);
}

// Turn a string with just an integer in it into a int
int str2int (char* s){
  int n;
  if (sscanf(s,"%d",&n)==1) return n;
  else exit(EXIT_FAILURE);
}
