#include <stdlib.h>

#include "utils.h"

struct Vector {
    int x;
    int y;
};

static void init(Vector *v, int x, int y);

Vector* Vector_new(int x, int y)
{
    Vector *v;

    v = (Vector *) malloc(sizeof(Vector));

    if(v == NULL)
        return NULL;

    init(v, x, y);

    return v;
}

void Vector_clear(Vector *v)
{
    if(v != NULL)
        free(v);
}

static void init(Vector *v, int x, int y)
{
    v->x = x;
    v->y = y;
}

void Vector_update(Vector *v, int x, int y)
{
    v->x = x;
    v->y = y;
}

int Vector_get_x(Vector *v)
{
    return v->x;
}

int Vector_get_y(Vector *v)
{
    return v->y;
}
