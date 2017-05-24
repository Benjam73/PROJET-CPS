#include <stdlib.h>
#include "dict.h"
#include "LZW.h"

int main(int argc, char const *argv[]){
	
	FILE* f_input ;
	FILE* f_output ;
	dict_t dico ;


	dico = dict_new();
	dict_print(dico);

	f_input = fopen(argv[1], "r");
	f_output = fopen(argv[2], "w");

	compression (f_input, f_output);

	decompression (f_input, f_output);


	return 0;
}