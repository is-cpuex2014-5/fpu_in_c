#include "float.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


float
frand(void) {
  union 
  {
    float as_float;
    int32_t as_int;    
  } unit;  
  unit.as_int = rand();
  
  return unit.as_float;
}

int
getSignTestUnit (float test)
{
  uint32_t * a;
  a = (uint32_t*)&test;  
  
  return test ? getSign(*a) == test < 0 : 1;  
}

void
getSignTest (void)
{
  for (int i = 0;i < 1000;i++) 
    {      
      if (!(getSignTestUnit (frand()))) 
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
  uint32_t * a;
  a = (uint32_t*)&test;  
  
  return *a = makeFloat(getSign(*a),getExp(*a),getMant(*a));  
}

void
makeFloatTest (void)
{
  for (int i = 0;i < 1000;i++) 
    {      
      if (!(makeFloatTestUnit (frand()))) 
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
  } i,n;
  i.as_int = m_Inf;
  n.as_int = m_Nan;
  if (!(isnan (n.as_float)))
    {
      puts ("test of m_Nan not passed!!");
      printf ("%f\n",n.as_float);
      
      exit (1);
    }
  
  if (!(isinf (i.as_float)))
    {
      puts ("test of m_Inf not passed!!");
      printf ("%f\n",i.as_float);

      exit (1);      
    }
  puts ("test of const value passed!!"); 
}

int
main (void)
{
  srand (time(NULL));  
  
  getSignTest ();
  makeFloatTest ();
  constTest ();
  
  return 0;
}

