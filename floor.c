#include <stdint.h>
#include <stdio.h>
#include "float.h"

uint32_t
h_floor (uint32_t in)
{
  const uint8_t sign = bin (in,31);
  const uint8_t expr = bina (in,30,23);
  uint32_t mantissa = bina (in,22,0) + (1 << 23);
  if (expr > 158 || expr < 127)
    return 0;
  if (expr > 127 + 23) 
    {
      mantissa <<= (expr - 127 - 23);
    }
  else if (expr < 127 + 23) 
    {
      mantissa >>= (127 + 23 - expr);
    }

  if (!sign)
    {
      return mantissa;
    }
  else
    {
      return ~mantissa;
    }
}

    
