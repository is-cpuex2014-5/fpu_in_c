#include <fenv.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

extern uint32_t
fsqrt (uint32_t a);

union uint32_f
{
  uint32_t i;
  float f;
};

void printSqrt (uint32_t in)
{
  union uint32_f a, c;
  char aa[33],cc[33];
  a.i = in;
  if (fpclassify (a.f) != FP_NORMAL)
    return;
  c.i = fsqrt (a.i);
  if (fpclassify (c.f) != FP_NORMAL)
    return;
  for (int t = 0; t < 32;++t)
    {
      aa[31 - t] = a.i & (1 << t) ? '1' : '0';
      cc[31 - t] = c.i & (1 << t) ? '1' : '0';
    }
  aa[32] = '\0';
  cc[32] = '\0';
  // 非正規化数とかはやらない
  if (isnormal (a.f))
    {
      if (!isnan (c.f))
	printf ("%s\t%s\n",aa,cc);
    }    
}

void
gen_test (void)
{
  printSqrt(0x3f800001);
  for (int i = 0; i < 2000000 ; i++)
    {
      printSqrt(rand () | rand () << 16);
    }
}

int
main (void)
{
  fesetround (FE_TOWARDZERO);
  srand((unsigned)time(NULL));

  gen_test ();

  return 0;
}
