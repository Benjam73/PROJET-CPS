#include "chaine_carac.h"

void test_chaine_carac(){

	uint8_t *word = malloc(sizeof(uint8_t));
	uint8_t *a = malloc(sizeof(uint8_t));

	word[0] = 100 ;
	word[1] = 2 ;
	a[0] = 3 ;

	fprintf_n_octets(stdout, word, 2) ;
	fprintf_n_octets(stdout, a, 1) ;
	fprintf_n_octets(stdout, concatenation(word, 2, a), 3) ;
	
}

void fprintf_n_octets(FILE* f, const uint8_t* word, const int n){
	
	// TODO : Adapter au binaire

	// for (int i = 0; i < n; i++){
	// 	fprintf(f, "%" PRIu8 ".", word[i]);
	// }
	

	if (f == stdout){
		fprintf(f, "'");  
	}	
	for (int i = 0; i < n; i++){
		fprintf(f, "%c", word[i]);  
	}
	if (f == stdout){
		fprintf(f, "'");  
	}	
	fflush(f);
}


uint8_t* concatenation(const uint8_t* w, const int wlength, const uint8_t* a){
	uint8_t* wa = malloc(sizeof(uint8_t));
	int i;
	for (i = 0; i < wlength; i++){
		wa[i] = w[i];
	}
	wa[i] = *a;
	return wa;
}

