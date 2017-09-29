#include "minunit.h"
#include "../src/darray_algos.h"

int testcmp(char **a, char **b)
{
	return strcmp(*a, *b);
}

DArray *create_words()
{
	DArray *result = DArray_create(0, 5);
	char *words[] = {"asdfsa", "werwar", "12312", "sdasda", "ojos" };
	int i = 0;

	for(i = 0; i < 5; i++) {
		DArray_push(result, words[i]);
	}

	return result;
}

int is_sorted(DArray *array)
{
	int i = 0;

	for(i = 0; i < DArray_count(array) - 1; i++) {
		if(strcmp(DArray_get(array, i), DArray_get(array, i+1)) > 0) {
			return 0;
		}
	}

	return 1;
}

char *run_sort_test(int (*func)(DArray *, DArray_compare), const char *name)
{
	DArray *words = create_words();
	mu_assert(!is_sorted(words), "should start not sorted.");

	debug("--- testing %s sorting algorithm", name);
	int rc = func(words, (DArray_compare)testcmp);
	mu_assert(rc == 0, "sort failed");
	mu_assert(is_sorted(words), "didn't sort it");

	DArray_destroy(words);

	return NULL;
}

char *test_qsort()
{
	return run_sort_test(DArray_qsort, "qsort");
}

char *test_heapsort()
{
	return run_sort_test(DArray_heapsort, "heapsort");
}

char *test_mergesort()
{
	return run_sort_test(DArray_mergesort, "mergesort");
}

char *all_tests()
{
	mu_suite_start();
	mu_run_test(test_qsort);
	mu_run_test(test_heapsort);
	mu_run_test(test_mergesort);

	return NULL;
}

RUN_TESTS(all_tests);