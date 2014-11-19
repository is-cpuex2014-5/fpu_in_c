#include <stdint.h>
#include "float.h"
#include <stdio.h>

static int
ZLC (uint32_t a)
{
  if (!a) 
    {
      return 31;
    }
  
  if (bin(a,30) == 1) 
    {
      return 0;
    }
  else
    {      
      return 1 + ZLC (a << 1);
    }  
}

uint32_t
h_i2f (uint32_t in)
{
  const bool isZero = !in;
  const uint8_t sign = bin (in,31);
  /* printf ("in = %d %x\n",in,in); */
  in = sign ? (~(bina (in,30,0))) + 1: bina (in,30,0);  
  int s = ZLC (in);
  uint8_t expr = 127 + 30 - s;
  if (s < 7)
    {
      // rounding
      const uint8_t R = bin (in,6-s);
      const uint8_t G = bina (in,5-s,0) != 0;
      in >>= 7 - s;
      /* printf ("sign %d,s = %d,in = %d %x\n",sign,s,in,in); */
      const uint8_t ulp = bin(in,0);
      /* const uint8_t f = !bin (in,25); */
      in += R &&(G || ulp );

      /* printf ("R %d\n",R); */
      /* printf ("sign %d,s = %d,in = %d %x\n",sign,s,in,in); */
      /* if ((f && bin (in,25) == 1) || (!f && bin (in,25) == 0)) { */
      if (bina (in,23,0) == 0) {
	  /* puts ("HERE"); */
	  in >>= 1;
	  expr++;
      }
    }  
  else if (s > 7)
    {
      in <<= s - 7;
    }

  in = bina (in,22,0);
  if (isZero)
    return 0;
  return makeFloat (sign,expr,in);  
}

    
