#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "utils.h"

#include "utils_test.h"

static void Vector_new_test(void **state)
{
    Vector *v;

    v = Vector_new(0,0);
    assert_non_null(v);
    Vector_clear(v);
}

static void Vector_update_test()
{
    Vector *v;

    v = Vector_new(0,0);
    assert_int_equal(Vector_get_x(v), 0);
    assert_int_equal(Vector_get_y(v), 0);
    Vector_update(v, 100, 50);
    assert_int_equal(Vector_get_x(v), 100);
    assert_int_equal(Vector_get_y(v), 50);
    Vector_clear(v);
}

int Utils_tests(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(Vector_new_test),
        cmocka_unit_test(Vector_update_test),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
