#include <stdlib.h>

#ifdef TEST
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#endif

#include "utils.h"

struct Vector {
    int x;
    int y;
};

static void init(Vector *v, int x, int y);

Vector* Vector_new(int x, int y)
{
    Vector *v;

#ifdef TEST
    v = (Vector *) test_malloc(sizeof(Vector));
#else
    v = (Vector *) malloc(sizeof(Vector));
#endif

    if(v == NULL)
        return NULL;

    init(v, x, y);

    return v;
}

void Vector_clear(Vector *v)
{
    if(v != NULL)
    {
#ifdef TEST
        test_free(v);
#else
        free(v);
#endif
        v = NULL;
    }
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
