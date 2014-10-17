#include <fenv.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++;     \
    if (message) return message; } while (0)
int tests_run = 0;
char str[1000];
extern uint32_t fadd (uint32_t a, uint32_t b);

union uint32_f
{
  uint32_t i;
  float f;
};

char *
all_tests (void)
{

  fesetround (FE_TOWARDZERO);
  srand((unsigned)time(NULL));
  union uint32_f a, b, c;
  for (int i = 0; i < 2000000 ; i++)
    {
      scanf ("%f %f",&a.f,&b.f);
      tests_run++;
      c.i = fadd (a.i, b.i);
      printf ("%f\n",c.f);
      // 非正規化数とかはやらない
      if (isnormal (a.f) && isnormal (b.f))
	{
	  mu_assert ((sprintf
		      (str, "error:%d %d %d %f %f %f %f\n", a.i, b.i, c.i,
		       a.f, b.f, c.f, a.f + b.f), str), c.f == a.f + b.f
		     || isnan (c.f));
	}
    }
  return NULL;
}

int
main (void)
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
