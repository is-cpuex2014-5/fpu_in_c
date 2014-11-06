/*!
  @file float.h
  @brief 浮動小数点の扱いで使う諸々のutility
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

#define isNaN(A) (((getExp(A)) == 0xff) && ((getMant(A)) != 0))
#define isInf(A) (((getExp(A)) == 0xff) && ((getMant(A)) == 0))
//! @note Denormal number is also regarded zero.
#define isZero(A) (getExp((A)) == 0)
#define getSign(A) ((A) >> 31)
#define getExp(A) (((A) >> 23) & ((1 << 8) - 1))
#define getMant(A) ((A) & ((1 << 23) - 1))
#define makeFloat(S,E,M) ((S) << 31) | ((E) << 23) | (M)
#define xor(A,B) (((A)+(B)) & 1)
#define changeSign(S,N) ((S) << 31) | ((N) & 0x7fffffff)
#define m_Nan 0xfff00000
#define m_Inf 0xff800000
//! binary access.AのNbit目を返す
#define bin(A,N) (((A) >> (N)) & 1)
//! binary arrayを返す.AのMからNbit目を返す
#define bina(A,N,M) ((A & (((uint64_t)((uint64_t)1 << (N+1)) - 1))) >> (M))

#ifdef DEBUG
#define dprintf printf
#else
#define dprintf
#endif

int32_t
f2i (float);

float
i2f (uint32_t);

void
print_binary (const uint32_t);

void
print_binary_n (const uint64_t,int);



