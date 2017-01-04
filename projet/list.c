/*
  file: list.c 
  updated: 03/01/2017
  author: pierre cagne

  implements list of integers and list of list of integers; this will
  be used to store solutions and set of solutions of dlx problems.
*/

#include <stdlib.h>
#include "list.h"

// type for cells of list of idrow_t
struct list_cell_s {
  idrow_t head;
  struct list_cell_s *tail;
} list_cell_t;

// type for cells of list of list of idrow_t
struct lol_cell_s {
  list_t head;
  struct lol_cell_s *tail;
} lol_cell_t;


// basic functions to manipulate list of idrow_t

/*
  returns a new empty list, i.e. NULL
*/
list_t list_new () { return NULL; }

/*
  returns the list with key added in front
*/
list_t list_cons (idrow_t head, list_t list) {
  list_t new = malloc(sizeof(list_cell_t));
  new->head = head; new->tail = list;

  return new;
}

/*
  returns the tail of the list
*/
idrow_t list_head (list_t list) { return list->head; }

/*
  returns the tail of the list
*/
list_t list_tail (list_t list) { return list->tail; }

/*
  destructs completely a list allocated of the heap
*/
void list_destruct (list_t list) {
  if (!list) return;

  list_t tmp = list->tail;
  free(list); list_destruct(tmp);
}


// basic functions to manipulate list of list of idrow_t

/*
  returns a new empty list of list, i.e. NULL
*/
lol_t lol_new () { return NULL; }

/*
  returns the list of list with head added in front
*/
lol_t lol_cons (list_t head, lol_t lol) {
  lol_t new = malloc(sizeof(lol_cell_t));
  new->head = head; new->tail = lol;

  return new;
}

/*
  returns the head of a list of list
*/
list_t lol_head (lol_t lol) { return lol->head; }

/*
  returns the tail of a list of list
*/
lol_t lol_tail (lol_t lol) { return lol->tail; }

/*
  destructs completely a list of list allocated of the heap
*/
void lol_destruct (lol_t lol) {
  if (!lol) return;

  lol_t tmp = lol->tail;
  free(lol); lol_destruct(tmp);
}
