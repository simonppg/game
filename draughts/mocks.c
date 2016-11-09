#include <stdlib.h>

#include "mocks.h"

void *fake_malloc(size_t size)
{
    fake_malloc_params.last_request = size;
    if (fake_malloc_params.should_fail) {
        return NULL;
    }
    return (fake_malloc_params.real_malloc) (size);;
}
