/*
  file: list.h 
  updated: 03/01/2017
  author: pierre cagne

  header file for list.c; implements list of integers and list of list
  of integers; this will be used to store solutions and set of
  solutions of dlx problems.
*/

#ifndef LIST_H
#define LIST_H

// type for identifiers of the rows of dlx data
typedef unsigned short idrow_t;

// type for list of idrow_t
typedef struct list_cell_s* list_t;

// type for list of list of idrow_t
typedef struct lol_cell_s* lol_t;


// basic functions to manipulate list of idrow_t

/*
  returns a new empty list, i.e. NULL
*/
list_t list_new ();

/*
  returns the list with key added in front
*/
list_t list_cons (idrow_t head, list_t list);

/*
  returns the head of the list
*/
idrow_t list_head (list_t list);

/*
  returns the tail of the list
*/
list_t list_tail (list_t list);

/*
  destructs completely a list allocated of the heap
*/
void list_destruct (list_t list);


// basic functions to manipulate list of list of idrow_t

/*
  returns a new empty list of list, i.e. NULL
*/
lol_t lol_new ();

/*
  returns the list of list with head added in front
*/
lol_t lol_cons (list_t head, lol_t lol);

/*
  returns the head of a list of list
*/
list_t lol_head (lol_t lol);

/*
  returns the tail of a list of list
*/
lol_t lol_tail (lol_t lol);

/*
  destructs completely a list of list allocated of the heap
*/
void lol_destruct (lol_t lol);

#endif
