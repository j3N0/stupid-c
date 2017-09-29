#undef NDEBUG
#ifndef _minuint_h
#define _minuint_h

#include <stdio.h>
#include <stdlib.h>
#include "../src/lcthw/dbg.h"

#define mu_suite_start() char *message = NULL

#define mu_assert(tests, message) if(!(tests)){log_err(message); return message; }
#define mu_run_test(test) debug("\n------%s", " " #test);\
	message = test(); tests_run++; if (message) return message;

#define RUN_TESTS(name) int main(int argc, char *argv[]) {\
	argc = 1;\
	debug("------ RUNNING: %s", argv[0]);\
		printf("-----\nRUNNING: %s\n", argv[0]);\
		char *result = name();\
		if (result != 0) {\
			printf("FAILED: %s\n", result);\
		}\
		else {\
			printf("ALL TESTS PASSED\n");\
		}\
		printf("Test run: %d\n", tests_run);\
			exit(result != 0);\
}

int tests_run;

#endif
