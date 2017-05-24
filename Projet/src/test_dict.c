#include <stdlib.h>
#include "dict.h"


int main(int argc, char const *argv[]){
	
	dict_t dico = dict_new();

	dict_print(dico);

	return 0;
}