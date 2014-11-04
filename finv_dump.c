#include <fenv.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

extern uint32_t finv (uint32_t a);

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

union uint32_f
{
  uint32_t i;
  float f;
};

int
main (void)
{
  fesetround (FE_TOWARDZERO);
  srand((unsigned)time(NULL));
  union uint32_f a, c;
  for (int i = 0; i < 2000000 ; i++)
    {
      a.i = rand();
      c.i = finv (a.i);
      if (isnan (c.f) || a.f == 0 || c.f == 0 || !isnormal (a.f) || fabs (a.f) > pow (2,126))
	continue;
      printf ("%e %e\n",1/a.f,c.f);
      if ( fabs((1/a.f - c.f )/ c.f) > 0.1) {
	fprintf (stderr,"%e %e %e\n",a.f,1/a.f,c.f);
      }
    }
  fprintf (stderr,"finished finv_dump\n");
  return 0;
}
