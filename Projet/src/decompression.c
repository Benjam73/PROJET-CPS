#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "dict.h"
#include "string.h"

int decompression (int argc, char const *argv[]){
	
	FILE* f_input ;	 
	FILE* f_output ;
	
	dict_t dico ;
	
	dict_index_t i1, i2 ; 
	
	uint8_t* w1 = NULL;
	uint8_t* w2 = NULL ;
	int len_w1 = 0, len_w2 = 0;
	
	uint8_t a[1] ;

	dico = dict_new();
	f_input = fopen(argv[1], "r");
	f_output = fopen(argv[2], "w");

	// i' <- 1er code de S
	fread(&i1, 1, 1, f_input) ;
	
	// a <- chaine d'index i dans D
	dict_rechercher_index(dico, i1, a);

	// w <- [a]
	w1[0] = a[0] ;
	len_w1 = 1 ;

	// ecrire w sur E
	fprintf_n_octets(f_output, w1, len_w1);

	// tant que la fin de S n'est pas atteinte
	while(!feof(f_input)){

		// i' <- code suivant de S
		fread(&i2, 1, 1, f_input);
		
		// On place la chaine d'index i2 dans w2
		// Si on a une erreur, c'est que i2 n'est pas dans dico
		if (dict_rechercher_index(dico, i2, w2) != DICT_NOERROR){
			dict_rechercher_index(dico, i1, w2) ;
			w2[len_w2] = a[0] ; 
		}

		// ecrire w' sur E 
		fprintf_n_octets(f_output, w2, len_w2);
		
		// a <- 1er octet de w' 
		a[0] = w2[0] ;
		
		// D <- D U {w.a}
		dict_insert(dico, concatenation(w1, len_w1, a), len_w1+1);
		
		// i <- i'
		i1 = i2 ;

		// w <- chaine d'index i dans D
		dict_rechercher_index(dico, i1, w1);

	}

	return 0;
}