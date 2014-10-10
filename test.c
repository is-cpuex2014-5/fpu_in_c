#include "float.h"
#include "fmul.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


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

int
getSignTestUnit (float test)
{
  uint32_t *a;
  a = (uint32_t *) & test;

  return test ? getSign (*a) == test < 0 : 1;
}

void
getSignTest (void)
{
  for (int i = 0; i < 1000; i++)
    {
      if (!(getSignTestUnit (frand ())))
	{
	  puts ("test of getSign not passed!!");
	  exit (1);
	}
    }
  puts ("test of getSign passed!!");
}


int
makeFloatTestUnit (float test)
{
  uint32_t *a;
  a = (uint32_t *) & test;

  return *a = makeFloat (getSign (*a), getExp (*a), getMant (*a));
}

void
makeFloatTest (void)
{
  for (int i = 0; i < 1000; i++)
    {
      if (!(makeFloatTestUnit (frand ())))
	{
	  puts ("test of makeFloat not passed!!");
	  exit (1);
	}
    }
  puts ("test of makeFloat passed!!");
}

int
constTest (void)
{
  union
  {
    float as_float;
    int32_t as_int;
  } i, n;
  i.as_int = m_Inf;
  n.as_int = m_Nan;
  if (!(isnan (n.as_float)))
    {
      puts ("test of m_Nan not passed!!");
      printf ("%f\n", n.as_float);

      exit (1);
    }

  if (!(isinf (i.as_float)))
    {
      puts ("test of m_Inf not passed!!");
      printf ("%f\n", i.as_float);

      exit (1);
    }
  puts ("test of const value passed!!");
}

float
fmulAdapter (float x, float y)
{
  union
  {
    float as_float;
    int32_t as_int;
  } a, b, c;
  a.as_float = x;
  b.as_float = y;
  c.as_int = fmul (a.as_int, b.as_int);
  return c.as_float;
}

void
fmulIntTest (void)
{
  for (int i = 0; i < 1000; i++)
    {
      float a = rand () / 32, b = rand () / 32;
      float c = fmulAdapter (a, b);
      if (fabs (1.0f - a * b / c) > 0.000001)
	{
	  puts ("test of fmulInt not passed!!");
	  printf ("%d %f * %f = %f(%f),%10f\%\n", i, a, b, a * b, c,
		  100.0f * a * b / c);
	  exit (1);
	}
    }
  puts ("test of fmulInt passed!!");
}

void
fmulTest (void)
{
  for (int i = 0; i < 1000; i++)
    {
      float a = frand (), b = frand ();
      // 非正規化数とかはやらない
      if (fpclassify(a) != FP_NORMAL || fpclassify(b) != FP_NORMAL)
	continue;
      float c = fmulAdapter (a, b);
      if (fpclassify(c) != FP_NORMAL || fpclassify(a * b) != FP_NORMAL)
      	continue;
#define max(A,B) ((A) > (B) ? (A) : (B))
      if (fabs (a) < pow (2, 127) && fabs (b) < pow (2, 127)
	  && fabs (a * b) < pow (2, 127)
	  && fabs (c - a * b) >= max (a * b * pow (2, -22), pow (2, -126)))
	{
	  puts ("test of fmul not passed!!");
	  printf ("%d %f * %f = %f(%f),%e,%a %a\n", i, a, b, a * b, c,
		  fabs (c - a * b), c, a * b);
	  exit (1);
	}
    }
  puts ("test of fmul passed!!");
}

int
main (void)
{
  srand (time (NULL));

  getSignTest ();
  makeFloatTest ();
  constTest ();
  /* fmulIntTest (); */
  fmulTest ();
  return 0;
}
