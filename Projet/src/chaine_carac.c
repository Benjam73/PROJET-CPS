#include "chaine_carac.h"

void fprintf_n_octets(FILE* f, uint8_t* word, int n){
	for (int i = 0; i < n; i++){
		fprintf(f, "%c", word[i]);
		fprintf(stdout, "%s\n", "On ecrit");
	}
	fflush(f);
}

void fprintf_n_octets_comp(FILE* f, dict_index_t* index, int n){
	for (int i = 0; i < n; i++){
		fprintf(f, "%c", index[i]);
		fprintf(stdout, "%s\n", "On ecrit");		
	}
	fflush(f);
}

uint8_t* concatenation(uint8_t* w, int wlength, uint8_t* a){
	uint8_t* wa = malloc(sizeof(uint8_t));
	int i;
	for (i = 0; i < wlength; i++){
		wa[i] = w[i];
	}
	wa[i+1] = a[0];
	*a = wlength + 1 ;
	return wa;
}
