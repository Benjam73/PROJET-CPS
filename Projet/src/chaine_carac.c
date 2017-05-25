#include "chaine_carac.h"

// Cette fonction a été testee, elle fonctionne
void fprintf_n_octets(FILE* f, uint8_t* word, int n){
	for (int i = 0; i < n; i++){
		fprintf(f, "%c", word[i]);
		#ifdef DEBUG
		fprintf(stdout, " -> On ecrit\n");
		#endif
	}
	fflush(f);
}

void fprintf_n_octets_comp(FILE* f, dict_index_t* index, int n){
	for (int i = 0; i < n; i++){
		fprintf(f, "%d", index[i]);
		#ifdef DEBUG
		fprintf(stdout, " -> On ecrit\n");
		fflush(stdout);
		#endif
	}
	fflush(f);
}

uint8_t* concatenation(uint8_t* w, int wlength, uint8_t* a){
	uint8_t* wa = malloc(sizeof(uint8_t));
	int i;
	for (i = 0; i < wlength; i++){
		wa[i] = w[i];
	}
	wa[i] = a[0];
	return wa;
}
