#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "utils_test.h"

#define TEST 1

static void null_test_success(void **state)
{
    (void) state; /* unused */
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(null_test_success),
    };
    int result = 0;
    result = cmocka_run_group_tests(tests, NULL, NULL);
    result |= Utils_tests();
    return result;
}
