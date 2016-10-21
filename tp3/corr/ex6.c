/*
  file: ex5.c -- quick modular exponential

  Uses the quick exponential method but keep the results mod n.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int quick_exp_mod (int a, int e, int n);
int str2int (char* s);
char fermat_test(int n, int k);
int gcd(int a, int b);

int main (int argc, char** argv) {
  // In case of wrong usage.
  if (argc!=3) {
    printf("Usage: %s [n] [k] where n and k are integers.\n", argv[0]);
    exit(EXIT_SUCCESS);
  }

  srand((unsigned int) time(NULL)); // init seed
  
  int n = str2int(argv[1]), k = str2int(argv[2]);
  if (fermat_test(n, k)) printf("%d is composite for sure.\n", n);
  else printf("%d might be prime.\n", n);
  
  return EXIT_SUCCESS;
}

char fermat_test(int n, int k) {
  for(int i = 0; i < k; i++) {
    int a;
    a = (rand() % (n-1)) + 1, printf("a = %d / ",a);// random between 1 and n-1
    if ((quick_exp_mod(a,n-1,n)+n)%n != 1)
      return printf("try %d: %d^%d = %d mod %d\n",i,a,n-1,quick_exp_mod(a,n-1,n),n),
1; // fermat witness found
  }
  return 0; // no fermat witness found
}

int gcd(int a, int b) {
  if (b==0) return a;
  else return gcd(b,a%b);
}

// assure that norm_mod(a) is actually between 0 and n-1 (as in C, %n
// can return between -(n-1) and n-1).
int norm_mod (int a, int n) {
  return ((a%n)+n) % n;
}

// method of quick_exp_mod can be used to quick multiply modulo
int mult_mod (int a, int b, int n) {
  if (b == 0) return 0;
  int t = mult_mod (a, b/2, n);
  return b%2 == 0 ? norm_mod(t+t, n) : norm_mod(t+t+a, n);
}

// same as quick_exp, just mod n at each step
int quick_exp_mod (int a, int e, int n) {
  if (e == 0) return 1;
  int t = quick_exp_mod(a,e/2,n);
  t = mult_mod(t,t,n);
  return e%2 == 0 ? t : mult_mod(t,a,n);
}

// Turn a string with just an integer in it into a int
int str2int (char* s){
  int n;
  if (sscanf(s,"%d",&n)==1) return n;
  else exit(EXIT_FAILURE);
}
