#include "coord.h"
#include <stdlib.h>

coord_t coord_create(int x,int y){
  return (coord_t) {x, y};
}

int coord_getx(coord_t p){
  return p.x;
}

int coord_gety(coord_t p){
  return p.y;
}

char coord_eq(coord_t p, coord_t q){
  return (char) (p.x == q.x) && (p.y == q.y);
}  
