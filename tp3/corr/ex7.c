/*
  file: ex7.c -- correction tp3 ex7

  Implements Miller-Rabin's test.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int quick_exp_mod (int a, int e, int n);
int str2int (char* s);
int mult_mod (int a, int b, int n);
char miller_rabin_test(int n, int k);
int gcd(int a, int b);

int main (int argc, char** argv) {
  // In case of wrong usage.
  if (argc!=3) {
    printf("Usage: %s [n] [k] where n and k are integers.\n", argv[0]);
    exit(EXIT_SUCCESS);
  }

  srand((unsigned int) time(NULL)); // init seed
  
  int n = str2int(argv[1]), k = str2int(argv[2]);
  int w; // w will stock a fermat witness
  if (miller_rabin_test(n, k)) 
    printf ("%d is composite for sure\n", n);
  else printf("%d might be prime.\n", n);
  
  return EXIT_SUCCESS;
}

// returns 1 if 'a' is a miller-rabin witness, and '0' otherwise
char miller_rabin_witness (int a, int n, int s, int d) {
  if (quick_exp_mod(a,d,n) == 1) return 0; // disproved
  else {
    for (int r = 0, rr = 1; r < s; r++, rr *= 2) {
      if(quick_exp_mod(a,mult_mod(rr,d,n),n) == n-1) return 0; // disproved
    }
  }
  // if this is reached, 'a' is a miller-rabin witness
  return 1; 
}

// Miller-Rabin test: if all k test are independents, as more than 3/4
// of the range of the random variable 'a' are supposed to be
// Miller-Rabin witnesses, there is at most probability (1/4)^k that
// miller_rabin_test will give 0 (no witness found) on a odd composite
// number.
//
// Fun fact: for k ~ 100, there is actually more chances that a cosmic
// ray hits you processor and changes a byte (making the computation
// wrong) than there is that Miller-Rabin gives you a false prime !
char miller_rabin_test(int n, int k) {
  // retrieve first d and s such that n-1 = 2^s*d
  int s = 0, d = n-1; while (d%2 == 0) { s++; d /= 2;}
  printf("s = %d, d = %d for n = %d\n",s,d,n);

  // test for Miller-Rabin witnesses k times
  for(int i = 0; i < k; i++) {
    int a = (rand() % (n-1)) + 1; // random between 1 and n-1
    if (miller_rabin_witness(a,n,s,d)) return 1; // witness found
  }
  return 0; // no witness found
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

// method of quick_exp_mod can be used to quick multiply modulo too
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
