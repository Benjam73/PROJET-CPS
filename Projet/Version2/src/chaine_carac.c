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

void fprintf_n_octets(FILE* f, uint8_t* word, int n){
	// for (int i = 0; i < n; i++){
	// 	fprintf(f, "%" PRIu8 ".", word[i]);
	// 	// #ifdef DEBUG
	// 	// fprintf(stdout, " -> On ecrit\n");
	// 	// #endif
	// }
	// fprintf(f, " \"");
	for (int i = 0; i < n; i++){
		fprintf(f, "%c", word[i]);  
	}
	// fprintf(f, "\" ");
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

int adapter_longueur(uint8_t* w1){
	int lg =0;
	for(int i = 0; i<16; i++){
		if(w1[i] != 0x0){
			lg++;
		}
	}
	return lg;
}


int uint8_cmp(uint8_t* tab, char* tab2, int taille){
	int monbool = 1;
	for(int i = 0; i < taille && monbool == 1; i++){
		if(tab[i] != tab2[i]){
			monbool = 0;
		}
	}
	return !monbool;
}

dict_index_t to_index(uint8_t* tab, int taille){
	int result = 0;
	char tmp;
	for(int i = 0; i < taille; i++){
		tmp = tab[i];
		result += atoi(&tmp);
	}
	return result;
}

uint8_t* init_vect(){
	uint8_t* tab = malloc(sizeof(uint8_t));
	while(adapter_longueur(tab) != 0){
		tab = malloc(sizeof(uint8_t));
	}
	return tab;
}

void fflush_vect(uint8_t* tab, int taille){
	for(int i = 0; i < taille; i++){
		tab[i] = 0x0;
	}
}