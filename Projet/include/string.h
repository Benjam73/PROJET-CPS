#ifndef _STRING
#define _STRING

#include <stdio.h>
#include <stdlib.h>

void fprintf_n_octets(FILE* f, uint8_t* word, int n) ;

uint8_t* concatenation(uint8_t* w, int wlength, uint8_t* a);

#endif //_STRING