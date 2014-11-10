#include <stdint.h>
#include <stdbool.h>
#include "float.h"

bool
feq (uint32_t a,uint32_t b)
{
  if (getExp (a) == 0 && getExp (b) == 0)
    return true;  
  if (getExp (a) == 255 || getExp (b) == 255)
    return false;
  return a == b;  
}

