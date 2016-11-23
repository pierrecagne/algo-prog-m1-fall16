/* file: ex8.c -- correction tp4 ex8

   Back to extended euclid through pointers.  Most elegant way is
   probably with structures, not seen at the moment.
*/

#include <stdio.h>
#include <stdlib.h>


void ext_euclid (int a, int b, int* gcd, int* u, int* v) {
  if (b == 0) { *gcd = a; *u = 1; *v = 0; return; } //base case
  /* if u'b+v'r = gcd(b,r) with a = qb +r euclidean division,
     then v'a + (u'-v'q)b = gcd(b,r) = gcd(a,b) 
  */
  int dd, uu, vv;
  ext_euclid (b, a%b, &dd, &uu, &vv);
  *gcd = dd; *u = vv; *v = uu - vv*(a/b);
}

int main (int argc, char** argv) {

  int a = 5282, b = 6976;
  int gcd,u,v;
  ext_euclid(a, b, &gcd, &u, &v);
  printf("%d*%d + %d*%d = %d (checking: %d)\n", u,a,v,b,gcd, u*a+b*v);
  
  return EXIT_SUCCESS;
}
