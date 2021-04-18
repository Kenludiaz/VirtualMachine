#ifndef BITPACK_INCLUDED
#define BITPACK_INCLUDED
#include <stdbool.h>
#include <stdint.h>
#include "except.h"
bool Bitpack_fitsu(uint32_t n, unsigned width);
bool Bitpack_fitss( int32_t n, unsigned width);
uint32_t Bitpack_getu(uint32_t word, unsigned width, unsigned lsb);
 int32_t Bitpack_gets(uint32_t word, unsigned width, unsigned lsb);
uint32_t Bitpack_newu(uint32_t word, unsigned width, unsigned lsb, uint32_t value);
uint32_t Bitpack_news(uint32_t word, unsigned width, unsigned lsb,  int32_t value);
extern Except_T Bitpack_Overflow;
#endif

