#include <stdio.h>
#include <stdlib.h>
#include "cdll.h"

struct node_s {
  int key;
  cdll left, right;
} node_t;

cdll cdll_empty () {
  return NULL;
}

cdll cdll_create (int key) {
  cdll new = (cdll) malloc(sizeof(node_t));
  new->key = key;
  new->right = new; new->left = new;
  return new;
}

cdll cdll_disconnect (cdll list) {
  list->left->right = list->right;
  list->right->left = list->left;

  return list->right;
}

cdll cdll_reconnect (cdll node) {
  node->left->right = node;
  node->right->left = node;

  return node;
}

cdll cdll_add (int key, cdll list) {
  if (!list) return cdll_create(key);
  
  cdll tmp = cdll_create(key);
  tmp->left = list; tmp->right = list->right;

  return cdll_reconnect(tmp);
}

int cdll_get (cdll list) {
  return list->key;
}

void cdll_print (cdll list) {
  cdll tmp = list;
  do {
    printf ("%d ",tmp->key);
    tmp = tmp->right;
  } while (tmp != list);
  printf ("\n");

  return;
}

cdll cdll_plug (cdll main, cdll aux) {
  cdll t = main, tt = aux;
  aux->left = main; tt->left->right = main->right;
  main->right = aux; t->right->left = tt->left;
  
  return main;
}

cdll cdll_chop (cdll list) {
  cdll tmp = cdll_disconnect(list);
  if (list == tmp) {
    free(list);
    return NULL;
  }
  else {
    free(list);
    return tmp;
  }
}

cdll cdll_rem (int key, cdll list) {
  if (!list) return NULL;
  
  cdll tmp = list;
  do {
    if (key == tmp->key)
      return cdll_chop (tmp);
    tmp = tmp->right;
  } while(tmp != list);

  return list;
}
