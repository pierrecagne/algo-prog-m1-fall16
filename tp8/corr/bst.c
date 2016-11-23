#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "bst.h"

struct bst_node_s {
  int key;
  bst_t left;
  bst_t right;
} bst_node_t;

bst_t bst_init() {
  return NULL;
}

void bst_destruct(bst_t root) {
  if (!root) return;
  
  bst_destruct(root->left); bst_destruct(root->right);
  free(root);
}

bst_t bst_sing(int key) {
  bst_t root = (bst_t) malloc(sizeof(bst_node_t));
  root->left = NULL; root->right = NULL; 
  root->key = key;
  return root;
}

bst_t bst_add(bst_t root, int key) {
  if (!root) return bst_sing(key);

  if (key < root->key) root->left = bst_add(root->left, key);
  else if (key > root->key) root->right = bst_add(root->right, key);
  // in case root->key is equal to key, nothing to do
  return root;
}

bst_t bst_max_node (bst_t root) {
  if (!root->right) return root;
  return bst_max_node (root->right);
}

int bst_max (bst_t root) {
  return bst_max_node(root)->key;
}

bst_t bst_min_node (bst_t root) {
  if (!root->left) return root;
  return bst_min_node (root->left);
}

int bst_min (bst_t root) {
  return bst_min_node(root)->key;
}

bst_t bst_search (bst_t root, int key) {
  if (!root) return NULL;
  
  if (root->key == key) return root;
  if (root->key < key) return bst_search(root->left, key);
  else return bst_search(root->right, key);
}
 
char bst_mem (bst_t root, int key) {
  bst_t key_at = bst_search(root, key);
  if (!key_at) return 0;
  else return 1;
}

/* // iterative version */
/* bst_t bst_mindel (bst_t root) { */
/*   bst_t x, min = bst_min_node(root); */
/*   for(x = root; x && x->left != min; x = x->left); */
/*   free(x->left); x->left = min->right; */
/*   return root; */
/* } */

// recursive version
bst_t bst_mindel (bst_t root) {
  assert(root);
  if (!root->left) {
    bst_t r = root->right;
    free(root);
    return r;
  }

  root->left = bst_mindel (root->left);
  return root;
}
  
bst_t bst_rem (bst_t root, int key) {
  // removing something that is not there is doing nothing
  if (!root) return root;
  
  if (key == root->key) {
    if (!root->left || !root->right) // at most one child for root
      root = root->left ? root->left : root->right;
    else {
      root->key = bst_min(root->right);
      root->right = bst_mindel(root->right);
    }
  }
  else if (key < root->key)
    root->left = bst_rem (root->left, key);
  else if (key > root->key)
    root->right = bst_rem (root->right, key);
  // in any case, return root
  return root;
}

bst_t bst_copy (bst_t root) {
  if (!root) return NULL;

  bst_t new = bst_sing(root->key);
  new->left = bst_copy(root->left);
  new->right = bst_copy(root->right);
  return new;
}

// stupidely inefficient
void bst_print (bst_t root) {
  bst_t copy = bst_copy(root);
  while (copy) {
    printf("%d ",bst_min(copy));
    copy = bst_mindel(copy);
  }
}

void bst_print_tree_aux (bst_t root, int ntab) {
  if (!root) return;
  
  bst_print_tree_aux (root->left,ntab+1);
  for(int i=0; i<ntab; i++) printf("    ");
  printf("%d <\n", root->key);
  bst_print_tree_aux (root->right,ntab+1);
}

void bst_print_tree (bst_t root) {
  bst_print_tree_aux(root,0);
}
