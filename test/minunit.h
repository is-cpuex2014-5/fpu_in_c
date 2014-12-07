#pragma once

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do {printf ("\e[32m[ RUN      ]\e[0m %s\n",#test); char *message = test(); tests_run++; \
	if (message) { printf ("\e[31m[  FAILED  ]\e[0m %s\n",#test); return message; }printf ("\e[32m[  PASSED  ]\e[0m %s\n",#test);} while (0)
extern int tests_run;
float
frand (void);
