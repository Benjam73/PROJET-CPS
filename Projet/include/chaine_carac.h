#ifndef _STRING
#define _STRING

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "dict.h"

void fprintf_n_octets(FILE* f, uint8_t* word, int n) ;

void fprintf_n_octets_comp(FILE* f, dict_index_t* index, int n);

uint8_t* concatenation(uint8_t* w, int wlength, uint8_t* a);

#endif //_STRING
