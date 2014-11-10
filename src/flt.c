#include <stdint.h>
#include <stdbool.h>
#include "float.h"

bool
flt (uint32_t a,uint32_t b)
{
  if (getExp (a) == 0 && getExp (b) == 0)
    return false;
  return a < b;  
}

