#include <stdio.h>
#include <stdlib.h>

int gcd (int, int);
int str2int (char*);
int mod_inverse(int,int);

int main (int argc, char** argv) {
  // In case of wrong usage.
  if (argc!=3) {
    printf("Usage: %s [n] [m] where n and m are integers.\n", argv[0]);
    exit(EXIT_SUCCESS);
  }
  
  int a = str2int(argv[1]), n = str2int(argv[2]);
  int inva = mod_inverse(a,n);
  printf("%d*%d = %d mod %d\n", a, inva, (a*inva)%n,n);
  
  return EXIT_SUCCESS;
}

// Compute gcd
int gcd (int a, int b) {
  if (b > a) return gcd(b,a);
  else return b==0 ? a : gcd(b,a%b);
}

// Compute the inverse of a mod n
int mod_inverse (int a, int n) {
  int r = a, rr = n, t;
  int x = 1, xx = 0;
  while (rr!=0) { //invariant: x*a+xx*n = r
    t = x, x = xx, xx = (t - r/rr*xx)%n ;
    t = r, r = rr, rr = t%rr ;
  }
  return r==1 ? (x+n)%n : 0;
}

  
// Turn a string with just an integer in it into a int
int str2int (char* s){
  int n;
  if (sscanf(s,"%d",&n)==1) return n;
  else exit(EXIT_FAILURE);
}
