#ifndef CDLL_H
#define CDLL_H

typedef struct node_s* cdll;

cdll cdll_empty ();
cdll cdll_create (int key);
cdll cdll_plug (cdll main, cdll aux);
cdll cdll_add (int key, cdll list);
/* cdll cdll_disconnect (cdll list); */
/* cdll cdll_reconnect (cdll node); */
cdll cdll_chop (cdll list);
cdll cdll_rem (int key, cdll list);
int cdll_get (cdll list);
void cdll_print (cdll list);

#endif
