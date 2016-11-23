/* file: stack_queue_polish.c -- correction tp6 ex4-9

   Implements stacks of strings.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// to deal with errors
void die(char* msg) {
  printf ("Error: %s\n", msg);
  exit (EXIT_FAILURE);
}

// returns the length of a string
size_t str_len (char* str) {
  size_t i = 0; while(str[i++]);
  return i;
}

/* stack's stuff: begin */

// same as linked list with string values
typedef struct cell_s* mystack_t;
struct cell_s {
  char* val;
  mystack_t next;
} cell_t;

// prototypes
mystack_t stack_push (char* str, mystack_t s);
char *stack_pop (mystack_t* s);

mystack_t stack_push (char* str, mystack_t s){
  // allocate memory for a new cell
  mystack_t new = (mystack_t) malloc(sizeof(cell_t));
  // put str in the new cell, now pointing to s
  new->val = (char *) malloc(sizeof(char)*str_len(str));
  strcpy(new->val, str);
  new->next = s;
  // return the new head 'new'
  return new;
}

char *stack_pop (mystack_t* s) {
  mystack_t tmp = *s;
  if(!tmp) die("Can not pop empty stack.");
  char *head = tmp->val; // save head value
  *s = tmp->next; free(tmp); // pop head
  return head; // return head value
}
/* stack's stuff: end */

/* queue's stuff: begin */

// same as linked list with string values
typedef struct qcell_s qcell_t;
typedef struct queue_s queue_t;

struct qcell_s {
  char* val;
  qcell_t* next, *prev; // also store previous
};

struct queue_s {
  qcell_t* first; // point to one end
  qcell_t* last; // point to the other end
};

// prototypes
queue_t queue_push (char* str, queue_t q);
char *queue_pop (queue_t q);

queue_t queue_push (char* str, queue_t q){
  // allocate memory for a new cell
  qcell_t* new = (qcell_t*) malloc(sizeof(qcell_t));
  // put str in the new cell, now pointing to s
  new->val = str; new->next = q.first; q.first->prev = new; 
  // return the new head 'new'
  return (queue_t) { new, q.last};
}

char *queue_pop (queue_t *q) {
  char *tail = q->last->val; // save head value
  q->last = q->last->prev; // pop head
  return tail; // return the backup
}
/* queue's stuff: end */


/* polish notation calculus: begin */

mystack_t str_to_stack (char* str) {
  mystack_t s = NULL;
  while(*str) { // while it remains character in str
    int i = 0; while(str[i] != ' ' && str[i] != '\0') i++ ; // track next space

    // allocate memory for the thing to be pushed and copy the
    // relevant part of s into it
    char *topush = (char *) malloc(sizeof(char)*(i+1));
    int j = 0;
    for (; j < i ; j++) topush[j] = str[j]; topush[j+1] = '\0';

    s = stack_push(topush,s); // and push it

    str += (str[i] == '\0') ? i : i+1;
  }
  return s;
}

int compute (mystack_t s) {
  mystack_t comp = NULL;

  while (s) { // while s non empty
    char *top = stack_pop(&s); // pop the head
    
    // if top is an operation
    if (top[1] == '\0' && (top[0] == '+' || top[0] == '*'
	 || top[0] == '-' || top[0] == '/')) {
      // pop args off comp and check they are in fact integers
      int m,n;
      if(sscanf(stack_pop(&comp),"%d",&m) != 1) die("Bad operand.");
      if(sscanf(stack_pop(&comp),"%d",&n) != 1) die("Bad operand.");
      // do the actual computation
      int res;
      switch(top[0]) { // depending on the operation
      case '+': res = m+n; break;
      case '-': res = m-n; break;
      case '*': res = m*n; break;
      case '/': res = m/n; break;
      default: die("Bad operator.");
      }
      // push the result back on comp
      char sres[32]; sprintf(sres,"%d",res);
      comp = stack_push(sres,comp);
    }

    // otherwise, it's a number to push on comp
    else comp = stack_push(top,comp);
  } 

  // comp should now have a unique cell
  if(comp->next) die ("Incorrect syntax for polish notation.");
  int res; if( sscanf(stack_pop(&comp),"%d",&res) != 1 ) die ("Invalid result.");
  return res;
}

/* polish notation calculus: end */


int main(int argc, char** argv) {

  if (argc != 2) {
    printf ("Usage: %s [polish notation].\nExiting.\n",argv[0]);
    exit (EXIT_SUCCESS);
  }

  printf("Result of %s is: %d\n", argv[1], compute(str_to_stack(argv[1])));

  return EXIT_SUCCESS;
}
