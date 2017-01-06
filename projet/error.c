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
void error_handle (char *msg) {
  fprintf (stderr, "%s: %s\n", msg, strerror((int) errno));
  exit(EXIT_FAILURE);
}

/*
  prints out the usage and quit with failure status
*/
void error_usage (char *name) {
  fprintf(stderr,"\
%s: wrong usage\n\
usage: %s [-h] [file]\n\n\
- if -h is given, prints this help menu and quit.\n\
- file should be a path to a sudoku file; can be ommited only if -h given.\n", name, name);
  exit(EXIT_FAILURE);
}
