#include "check_operations.h"

int main(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = sum_suite();
    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    
    printf("\n");

    s = multiply_suite();
    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);
    srunner_free(runner);
    
    printf("\n");

    s = get_inverse_matrix_suite();
    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
