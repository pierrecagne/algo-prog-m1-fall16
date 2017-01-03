#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct node_s {
  coord_t key;
  int value;
  struct node_s *next;
} node_t;


list_t list_init(){
  return NULL;
}

list_t list_create (coord_t key, int value) {
  list_t new = (list_t) malloc(sizeof(node_t));
  new->key = key; new->value = value; new->next = NULL;
  return new;
}

list_t list_rem (coord_t key, list_t list){
  if (!list) return NULL;
  else if (coord_eq(list->key,key)) {
    list_t tmp = list->next;
    free(list); return tmp;
  }
  else return list_rem(key, list->next);
}

list_t list_ins (coord_t key, int value, list_t list){
  if (!list) return list_create(key,value);
  else if (coord_eq(list->key,key)) {
    list->value = value; return list;
  }
  else return list_ins(key,value,list->next);
}

char list_mem (coord_t key, list_t list) {
  if(!list) return 0;
  else if (coord_eq(key,list->key)) return 1;
  else return list_mem (key,list->next);
}

int list_get (coord_t key, list_t list) {
  if (coord_eq(key,list->key)) return list->value;
  else return list_mem (key,list->next);
}
  

