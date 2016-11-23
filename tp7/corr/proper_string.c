#include <stdlib.h>
#include "proper_string.h"


struct string_s {
  int length;
  char *val;
};

string_t ps_init(char* str) {
  string_t ret = (string_t) malloc(sizeof(struct string_s)); // init
  
  int i = 0; while(str[i]) i++; // i = len(str)
  char *val = (char *) malloc(sizeof(char)*i);
  for(int j = 0; j < i; j++) val[j] = str[j]; // copy without '\0'
  ret->length = i; ret->val = val;
  return ret;
}

int ps_len(string_t ps) {
  return ps->length;
}
