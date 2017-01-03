#ifndef LIST_H
#define LIST_H

#include "coord.h"

typedef struct node_s* list_t;

list_t list_init();
list_t list_create (coord_t key, int value);
list_t list_rem (coord_t key, list_t list);
list_t list_ins (coord_t key, int value, list_t list);
char list_mem (coord_t key, list_t list);
int list_get (coord_t key, list_t list);

# endif
