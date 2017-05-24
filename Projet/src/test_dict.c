#include <stdlib.h>
#include "dict.h"
#include "LZW.h"
#include <string.h>

#define true 1
#define false 0


int main(int argc, char const *argv[]){

	int argument_aide = false, comp = false, decomp =false ;
	

	FILE *f_input_c, *f_output_c, *f_input_x, *f_output_x ;
	dict_t dico ;

	
	for (int i = 1 ; i < argc && !argument_aide ; i++){
		if (strcmp(argv[i], "-h") == 0){
			argument_aide = true ;
		}
	}

	if(argc < 3 || argc > 5 || argument_aide){
		fprintf(stdout, "%s [-c fichier_entree ficher_sortie] [-x fichier_entree ficher_sortie]\n", argv[0]);
		fprintf(stdout, "Arguments : \n\t -c : compression\n\t -x : decompression\n");
		return -1 ;
	}


	for (int i = 1 ; i < argc && !(comp && decomp) ; i++){
		if (strcmp(argv[i], "-c") == 0){
			f_input_c = fopen(argv[i + 1], "r");
			f_output_c = fopen(argv[i + 2], "w");
			comp = true ;
		}
		if (strcmp(argv[i], "-x") == 0){
			f_input_x = fopen(argv[i + 1], "r");
			f_output_x = fopen(argv[i + 2], "w");
			decomp = true ;
		}
	}


	if (f_input_x == NULL){
		fprintf(stdout, "%s\n", "Erreur ouverture ficher entree decompression");
	}
	if (f_input_c == NULL){
		fprintf(stdout, "%s\n", "Erreur ouverture ficher entree compression");
	}
	if (f_output_x == NULL){
		fprintf(stdout, "%s\n", "Erreur ouverture ficher sortie decompression");
	}
	if (f_output_c == NULL){
		fprintf(stdout, "%s\n", "Erreur ouverture ficher sortie compression");
	}

	dico = dict_new();
	dict_print(dico);


	if (comp){
		compression (f_input_c, f_output_c);
	}

	if (decomp){
		decompression (f_input_x, f_output_x);
	}


	return 0;
}