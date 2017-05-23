#include <stdlib.h>
#include "dict.c"


int main(int argc, char const *argv[]){
	
	dict_t dico = dict_new();

	dict_print(dico);

	return 0;
}