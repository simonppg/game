#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>

#include "mocks.h"
#include "draughts.h"

int init_suite1(void)
{
    fake_malloc_params.real_malloc = malloc;
    fake_malloc_params.should_fail = 0;
    return 0;
}

int clean_suite1(void)
{
    fake_malloc_params.should_fail = 0;
    return 0;
}

static void test_game(void)
{
    struct Draughts *game;
    game = init_game();
    CU_ASSERT_PTR_NOT_NULL_FATAL(game);
    free(game);
    fake_malloc_params.should_fail = 1;
    struct Draughts *game_fail;
    game_fail = init_game();
    CU_ASSERT_PTR_NULL_FATAL(game_fail);
}

int main()
{
    CU_pSuite pSuite = NULL;

    /*
     * initialize the CUnit test registry
     */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /*
     * add a suite to the registry
     */
    pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /*
     * add the tests to the suite
     */
    if ((NULL == CU_add_test(pSuite, "test_game", test_game))
        ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /*
     * Run all tests using the CUnit Basic interface
     */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
