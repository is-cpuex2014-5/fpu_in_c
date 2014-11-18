#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "minunit.h"
#include "fpu_tests.h"

int tests_run = 0;

float
frand (void)
{
  union
  {
    float as_float;
    uint32_t as_int;
  } unit;
  unit.as_int = rand () | rand () << 16;

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
  mu_run_test (fmulCornerTest);
  mu_run_test (faddIntTest);
  mu_run_test (faddTest);
  mu_run_test (fsubIntTest);
  mu_run_test (fsubTest);
  mu_run_test (i2fTest);
  mu_run_test (i2fWholeTest);
  mu_run_test (floorTest);
  mu_run_test (floorWholeTest);
  mu_run_test (fdivTest);
  mu_run_test (fsqrtTest);
  mu_run_test (feqTest);
  mu_run_test (fltTest); 
  return 0;
}

int
main (void)
{
  srand (time (NULL));
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
