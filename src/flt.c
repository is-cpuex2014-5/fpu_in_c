#include <stdint.h>
#include <stdbool.h>
#include "float.h"

bool
flt (uint32_t a,uint32_t b)
{
  if (getExp (a) == 0 && getExp (b) == 0)
    return false;
  if (getSign (a) == 1 && getSign (b) == 1)
    {
      return a > b;  
    }  
  else if (getSign (a) == 1 && getSign (b) == 0)
    {
      return true;      
    }  
  else if (getSign (a) == 0 && getSign (b) == 1) 
    {
      return false;
    }  
  else 
    {
      return a < b;  
    }  		     
}

