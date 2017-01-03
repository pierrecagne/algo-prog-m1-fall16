#ifndef COORD_H
#define COORD_H

typedef struct {int x,y;} coord_t;

coord_t coord_create(int x,int y);
int coord_getx(coord_t p);
int coord_gety(coord_t p);
char coord_eq(coord_t p, coord_t q);

#endif
