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
      puts ("usage: fsqrt [f/i] [float/int]");
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

  b.as_int = fsqrt (a.as_int);
  printf ("as int : %d\n",b.as_int);
  printf ("as float : %f\n",b.as_float);

  return 0;  
}
