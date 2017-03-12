#ifndef _UTILS_H
#define _UTILS_H

typedef struct Vector Vector;

Vector* Vector_new(int x, int y);
void Vector_update(Vector *v, int x, int y);
int Vector_get_x(Vector *v);
int Vector_get_y(Vector *v);

#endif
