#include <stdlib.h>

typedef struct Vector Vector;
struct Vector {
    int angle;
    int magnitude;
};

Vector* Vector_new(int angle, int magnitude)
{
    Vector *v;

    v = (Vector *) malloc(sizeof(Vector));

    if(v == NULL)
        return NULL;

    return v;
}
