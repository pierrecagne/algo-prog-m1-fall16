#ifndef BST_H
#define BST_H

typedef struct bst_node_s* bst_t;

bst_t bst_init();
void bst_destruct(bst_t root);
bst_t bst_sing(int key);
bst_t bst_add(bst_t root, int key);
int bst_max (bst_t root);
int bst_min (bst_t root);
char bst_mem (bst_t root, int key);
bst_t bst_rem (bst_t root, int key);
bst_t bst_copy (bst_t root);
void bst_print (bst_t root);
void bst_print_tree (bst_t root);

#endif
