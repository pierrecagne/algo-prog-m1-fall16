#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "coord.h"

int main (int argc, char** argv) {

  int x=10, y=2, val=36;
  coord_t key = coord_create(x,y);
  hash_t h = hash_init(7);
  h = hash_ins(key, val, h);

  
  if (hash_mem(key,h))
    printf("val: %d\n", hash_getval(key,h));
  else printf("fail\n");

  h = hash_rem(key, h);

  if (hash_mem(key,h))
    printf("val: %d\n", hash_getval(key,h));
  else printf("fail\n");
  
  return EXIT_SUCCESS;
}
