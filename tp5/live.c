#include <stdio.h>
#include <stdlib.h>


typedef struct node_s* list_t;

struct node_s {
  int val;
  list_t next; 
} node_t ;

list_t new_list() {
  return NULL;
}

void pp_list(list_t l) {
  list_t tmp = l;
  while (tmp != NULL) {
    printf ("%d ", tmp->val);
    tmp = tmp->next;
  }
  printf ("\n");
}

void pp_list_rec (list_t l) {
  if (l == NULL) { printf("\n"); return; }
  printf("%d ", l->val);
  pp_list_rec(l->next);
}


list_t push(int v, list_t l) {
  list_t head = (list_t) malloc(sizeof(node_t));
  head->val = v; head->next = l;
  return head;
}

int length (list_t l) {
  if (l == NULL) return 0;
  return 1 + length(l->next);
}

int main (int argc, char** argv) {
  list_t l = new_list();

  for(int i = 0; i< 30; i++)
    l = push(2*i,l);
  
  pp_list_rec(l);
  printf ("length: %d\n", length(l));
  
  return EXIT_SUCCESS;
}
