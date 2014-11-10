#include "float.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <fenv.h>
#include <limits.h>
#include <assert.h>

extern uint64_t table (uint16_t);

int main (void)
{
    fesetround (FE_TOWARDZERO);
    for (int t = 0;t < 1 << 12;t++) {
	print_binary_n(table (t),35);
    }
    
}

