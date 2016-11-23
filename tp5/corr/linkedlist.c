/* file: linkedlist.c -- corection tp5 ex 1,2,3,4

   Implements basic functions about linked lists.
*/

#include <stdio.h>
#include <stdlib.h>

// making 'list_t' an alias for 'struct node_s*'
typedef struct node_s* list_t;

// a list should be a pointer to some value together with a pointer to
// the rest of the list
struct node_s {
  int val;
  list_t next; // see the use of the alias 'list_t'
} node_t; // 'node_t' is now an alias for 'struct node_s'


// pp_list(l) print the list 'l', separating elements with spaces and
// a newline at the end.
void pp_list (list_t l) {
  list_t t = l;
  while (t != NULL) {
    printf ("%d ",t->val); t = t->next;
  }
  printf ("\n");
}

// new_list() creates a new list
list_t new_list () {
  return NULL;
}

// push(l,v) pushes 'v' on top of 'l' and returns the updated list
list_t push (list_t l, int val) {
  list_t head = (list_t) malloc(sizeof(node_t));
  head->val = val; head->next = l;
  return head;
}

// length(l) returns the lenght of 'l'
int length (list_t l) {
  list_t t = l; int cmpt = 0;
  while (t != NULL) {
    cmpt ++; t = t->next;
  }
  return cmpt;
}

// recurvsive version of length ; recursion is especially suitable to
// inductively defiend data types as list_t
int length_rec (list_t l) {
  return l == NULL ? 0 : length_rec(l->next)+1 ;
}

// auxiliary function ; reverse_aux(prev,curr) reverse the list
// starting at 'prev' ; 'curr' is required to be prev->next
list_t reverse_aux (list_t prev, list_t curr) {
  if (curr == NULL) return prev;
  list_t tmp = curr->next; curr->next = prev;
  return reverse_aux(curr,tmp);
}

// actually reverse a list 'l' without the user having to deal with
// any subtilities
list_t reverse (list_t l) {
  return reverse_aux(NULL,l);
}


int main (int argc, char** argv) {

  list_t l = new_list(); // new list
  for (int i = 0; i < 10; i++) l = push(l,i); // n n-1 .. 2 1 0

  printf ("Testing functions:\n");

  printf ("list of length %d\n", length(l)); // length
  printf ("list of length_rec %d\n", length_rec(l)); // length rec
  
  printf ("list: "); pp_list(l); // l itself

  printf ("reversed: "); pp_list(reverse(l)); // reverse and print
  
  return EXIT_SUCCESS;
}
