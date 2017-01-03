#ifndef HASH_H
#define HASH_H

#include "coord.h"

typedef struct hash_s* hash_t;

hash_t hash_init (int size);
hash_t hash_ins (coord_t key, int val, hash_t htab);
hash_t hash_rem (coord_t key, hash_t htab);
char hash_mem (coord_t key, hash_t htab);
int hash_getval (coord_t key, hash_t htab);

#endif
