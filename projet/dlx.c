/* 
file: dlx.c
author: Pierre Cagne
date: last updated on 23/09/2016

---

This file implements Knuth's algorithm X with dancing links.

Under GPLv3 license.

 */

#include <stdio.h>
#include <stdlib.h>

// #include "dlx.h"

struct chead;
struct data;

typedef struct chead chead_t;
typedef struct data data_t;
typedef char id_t; 

// type for data objects of a sparse matrix
struct data {
  data_t *left, *right, *up, *down;
  chead_t *head;
  id_t id; // might become handy
};

// type for column header of a sparse matrix
// A unique header has name=NULL and is called the root.
struct chead {
  chead_t *left, *right;
  data_t node; //left and right field should be NULL
  int size;
  id_t id;
};

// disconnect a columen head
static void chead_delete(chead_t* c){
  c->left->right = c->right, c->right->left = c->left;
}

// reconnect a column head
static void chead_reinsert(chead_t* c){
  c->left->right = c, c->right->left = c;
}

// disconnect a data inside its column
static void data_delete(data_t* d){
  d->up->down = d->down, d->down->up = d->up;
}

// reconnect a data inside its column
static void data_reinsert(data_t* d){
  d->up->down = d, d->down->up = d;
}

// "cover" a column ; i.e. for each node of the column, disconnect
// every node of the same raw of their column
static chead_t* cover(chead_t* col){
  chead_delete(col);
  for(data_t* d=col->node.down; d!=&(col->node); d=d->down){
    for(data_t* e=d->right; e!=d; e=e->right){
      data_delete(e);
      e->head->size -= 1 ;
    }
  }
  return col;
}

// "uncover" a column
static void uncover(chead_t* col){
  for(data_t* d=col->node.up; d!=&(col->node); d=d->up){
    for(data_t* e=d->left; e!=d; e=e->left){
      data_reinsert(e);
      e->head->size += 1 ;
    }
  }
  chead_reinsert(col);
}



/* // trials */
/* int main(int argc, char** argv) { */
/*   printf("Foo\n"); */

/*   dlx_root h = NULL; */
/*   printf("declaring h: ok\n"); */
/*   h->id=0; h->size=0; */
/*   printf("affecting h id and size: ok\n"); */
/*   h->left = h; h->right = h; */
/*   printf("affecting h left and right: ok\n"); */
/*   h->node.left = h->node.right = h->node.up = h->node.down = NULL; */

/*   printf("Bar\n"); */
/*   return EXIT_SUCCESS; */
/* } */
