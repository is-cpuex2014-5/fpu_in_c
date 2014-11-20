#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "fpu.h"

int
main (int argc,char *argv[])
{
  union 
  {
    float as_float;
    uint32_t as_int;
  } a,b;
  
  if (argc < 2) 
    {
      puts ("usage: finv [f/i] [float/int]");
      return 1;      
    }

  switch (argv[1][0])
    {
    case 'f':
      a.as_float = atof (argv[2]);      
      break;
    case 'i':
      a.as_int = atoi (argv[2]);
      break;
    default:
      puts ("invalid type argument.please type f or i");
      return 2;
    }
  
  printf ("case: %g\n",a.as_float);
  if ( a.as_float > INT32_MAX  || a.as_float < INT32_MIN ) {
      printf ("this case is not in range of 32bit integer (%d,%d)\n",INT32_MIN,INT32_MAX);
  }
  b.as_int = h_floor (a.as_int);
  printf ("expected : %d\n",(int) a.as_float);
  printf ("as int : %d\n",b.as_int);
  printf ("as float : %g\n",b.as_float);

  return 0;  
}










