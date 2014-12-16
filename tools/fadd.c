#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "fpu.h"

int
main (int argc,char *argv[])
{
  union 
  {
    float as_float;
    uint32_t as_int;
  } a,b,c;
  
  if (argc < 3)
    {
      puts ("usage: fadd [f/i/x] [float/int/hex] [float/int/hex]");
      return 1;      
    }

  switch (argv[1][0])
    {
    case 'f':
      a.as_float = atof (argv[2]);      
      b.as_float = atof (argv[3]);
      break;
    case 'i':
      a.as_int = atoi (argv[2]);
      b.as_int = atoi (argv[3]);
      break;
    case 'x':
      a.as_int = strtol(argv[2], NULL, 16);
      b.as_int = strtol(argv[3], NULL, 16);
      break;      
    default:
      puts ("invalid type argument.please type f,i or x");
      return 2;
    }

  c.as_int = fadd (a.as_int,b.as_int);
  printf ("as int : %d\n",c.as_int);
  printf ("as hex : %x\n",c.as_int);
  printf ("as float : %g\n",c.as_float);
  
#define max(A,B) ((A) > (B) ? (A) : (B))
  if (fabs (a.as_float) >= pow (2, 127) ||
      fabs (b.as_float) >= pow (2, 127) ||
      fabs (a.as_float + b.as_float) >= pow (2, 127) ||
      fabs (c.as_float - (a.as_float + b.as_float)) < max(
	  max (fabs (a.as_float) * pow (2, -23), fabs (b.as_float) * pow (2, -23)),
	  max (fabs (a.as_float + b.as_float) * pow (2, -23), pow (2, -126))))
    {
      puts ("This is Valid");
    }
  else
    {
      puts ("This is INVALID");      
    }  
  
  return 0;  
}
