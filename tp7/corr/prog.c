#include <stdio.h>
#include <stdlib.h>
#include "proper_string.h"

int main (int argc, char **argv) {

  string_t proper = ps_init("Paraconsistant");
  printf ("lenght: %d\n", ps_len(proper));

  
  return EXIT_SUCCESS;
}
