/*
  file: error.c
  updated: 03/01/2017
  author: pierre cagne

  handles every kind of error and quit accordingly.
*/


#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "error.h"

/*
  prints out msg in stderr and add the string associated to errno,
  then quit with failure status.
*/
void error_handle (char *msg){
  fprintf (stderr, "%s: %s\n", msg, strerror((int) errno));
  exit(EXIT_FAILURE);
}
