#ifndef _LZW
#define _LZW

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "dict.h"
#include "string.h"

void compression (FILE* f_input, FILE* f_output);

void decompression (FILE* f_input, FILE* f_output);

#endif //_LZW