#ifndef _MOCKS_H_
#define _MOCKS_H_

#include <stdlib.h>

#define malloc(x) fake_malloc(x)

struct {
    size_t last_request;
    int should_fail;
    void *(*real_malloc) (size_t);
} fake_malloc_params;

void *fake_malloc(size_t size);

#endif
