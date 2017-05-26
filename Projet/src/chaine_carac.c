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
	for (int i = 0; i < n; i++){
		fprintf(f, "%" PRIu8 "", word[i]);  
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

// char* dec_to_binarray(dict_index_t n, int taille_reelle_donnees){
//   int c, d, count;
//   char *pointer;

//   count = 0;
//   pointer = (char*) malloc(taille_reelle_donnees);

//   if ( pointer == NULL ){
//     exit(EXIT_FAILURE);
//   }

//   printf("%lu\n", sizeof(dict_index_t));

//   for ( c = taille_reelle_donnees-1 ; c >= 0 ; c--){
//     d = n >> c;

//     if ( d & 1 ){
//       *(pointer+count) = 1 + '0';
//     }
//     else{
//       *(pointer+count) = 0 + '0';
//     }

//     count++;
//   }
//   *(pointer+count) = '\0';

//   return  pointer;
// }