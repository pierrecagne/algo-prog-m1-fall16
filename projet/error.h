/*
  file: error.h
  updated: 03/01/2017
  author: pierre cagne

  header file for error.c; handles every kind of error and quit
  accordingly.
*/

#ifndef ERROR_H
#define ERROR_H

#define ERROR_MAX 1000 // maximum size of an error message

/*
  prints out msg in stderr and add the string associated to errno,
  then quit with failure status.
*/
void error_handle (char *msg);
void error_usage (char *name);

#endif
