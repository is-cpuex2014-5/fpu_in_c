#pragma once
#include "fmul.h"
#include "finv.h"

#define fdiv(A,B) fmul((A),finv(B))
