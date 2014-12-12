#include <stdint.h>
#include "float.h"

uint32_t
fneg (uint32_t a)
{
    switch (getSign (a)) {
    case 0:
	return changeSign(1, a);
    default:
	return changeSign(0, a);
    }
    
}

