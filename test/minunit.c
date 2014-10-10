#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "minunit.h"
#include "fmul_test.h"
#include "float_test.h"

int tests_run = 0;

float
frand (void)
{
  union
  {
    float as_float;
    int32_t as_int;
  } unit;
  unit.as_int = rand ();

  return unit.as_float;
}

static char *
all_tests ()
{
  mu_run_test (getSignTest);
  mu_run_test (makeFloatTest);
  mu_run_test (constTest);
  mu_run_test (fmulIntTest);
  mu_run_test (fmulTest);
  return 0;
}

int
main (int argc, char **argv)
{
  char *result = all_tests ();
  if (result != 0)
    {
      printf ("%s\n", result);
    }
  else
    {
      printf ("ALL TESTS PASSED\n");
    }
  printf ("Tests run: %d\n", tests_run);

  return result != 0;
}
