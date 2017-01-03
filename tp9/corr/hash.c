#include <stdlib.h>
#include "hash.h"
#include "list.h"

struct hash_s {
  int size;
  list_t *table;
};

int hash_fun (coord_t key, int size) {
  int r = 1, x = coord_getx(key), y = coord_gety(key);
  for(; x > 0; x--) r = (r*2) % size ;
  for(; y > 0; y--) r = (r*3) % size ;
  return r;
}

hash_t hash_init (int size){
  hash_t new = (hash_t) malloc(sizeof(struct hash_s));
  new->size = size;
  new->table = (list_t*) malloc(sizeof(list_t)*size);
  for(int i = 0; i < size ; i++)
    new->table[i] = list_init();
  return new;
}

hash_t hash_ins (coord_t key, int val, hash_t htab) {
  int index = hash_fun(key,htab->size);
  htab->table[index] = list_ins(key, val, htab->table[index]);
  return htab;
}

hash_t hash_rem (coord_t key, hash_t htab) {
  int index = hash_fun(key,htab->size);
  htab->table[index] = list_rem(key, htab->table[index]);
  return htab;
}

char hash_mem (coord_t key, hash_t htab) {
  int index = hash_fun(key,htab->size);
  return list_mem(key, htab->table[index]);
}

int hash_getval (coord_t key, hash_t htab) {
  int index = hash_fun(key,htab->size);
  return list_get(key, htab->table[index]);
}
