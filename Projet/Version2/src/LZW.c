#include "LZW.h"



uint8_t* init_vect(){
	uint8_t* tab = malloc(sizeof(uint8_t));
	while(adapter_longueur(tab) != 0){
		tab = malloc(sizeof(uint8_t));
	}
	return tab;
}




void compression (FILE* f_input, FILE* f_output){

	dict_t dico ;

	uint8_t* a = malloc(sizeof(uint8_t));
	uint8_t* w = malloc(sizeof(uint8_t));

	int taille ;

	dict_index_t index = 0;

	// Un tableau de representation binaire de l'octet a coder
	int taille_codage = 9;
	uint8_t *binarray ;

	// Un tableau de representation binaire
	uint8_t *buffer = malloc(8 * sizeof(uint8_t));
	int *lg_buf = malloc(sizeof(int)) ;
	*lg_buf = 0 ;


    // D <- ens. de toutes les chaînes de longueur 1
	dico = dict_new();        

    // w <- [1er octet de E]
	fread(w, 1, 1, f_input);
	int wlength = 1;
	#ifdef DEBUG
	printf("w <- [1er octet de E]\n");
	printf("Premier w : ");fprintf_n_octets(stdout, w, wlength);printf("\n\n");
	#endif 


    // tant que la fin de E n'est pas atteinte
	while (!feof(f_input)) {

        // a <- octet suivant de E
        #ifdef DEBUG
		printf("a <- octet suivant de E\n");
		#endif 

		fread(a, 1, 1, f_input);

    	#ifdef DEBUG
		printf("a : ");fprintf_n_octets(stdout, a, 1);printf("\n");
		#endif


        // si w.a est dans D alors
		if (dict_rechercher_mot(dico, concatenation(w, wlength, a), wlength + 1, &index, &taille) ==  DICT_NOERROR) {

			#ifdef DEBUG
			uint8_t* DEBUG_wa = malloc(2 * sizeof(uint8_t)) ; 
			DEBUG_wa = concatenation(w, wlength, a);
			fprintf_n_octets(stdout, DEBUG_wa, wlength + 1);printf(" est dans D\n");
			#endif

            // w <- w.a                        
			#ifdef DEBUG
			printf("w <- w.a\n");
			#endif
			w = concatenation(w, wlength, a);
			wlength++;

		}
        // sinon
		else{

			#ifdef DEBUG
			uint8_t* DEBUG_wa = malloc(2 * sizeof(uint8_t)) ; 
			DEBUG_wa = concatenation(w, wlength, a);
			fprintf_n_octets(stdout, DEBUG_wa, wlength + 1);printf(" n'est pas dans D\n");
			#endif


            // Ecrire sur S l'index associe a w dans D 
			if(dict_rechercher_mot(dico, w, wlength, &index, &taille) != DICT_NOERROR){
				printf("Erreur de dictionnaire\n");
				exit(EXIT_FAILURE);
			}

			#ifdef DEBUG
			printf("Ecrire sur S l'index associe a w dans D\n");
			printf("On ecrit donc ");fprintf_n_octets(stdout, w, wlength);printf(" d'index %hi = ", index);fprintf_binarray(stdout, dec_to_binarray(index,9), 9); fprintf(stdout, "\n");
			#endif
			
			/* On place index dans un tableau binaire */
			binarray = dec_to_binarray(index, taille_codage);
			/* On ecrit cette representation binaire dans f_output */
			fprintf_index(f_output, buffer, lg_buf, binarray, taille_codage);
			#ifdef DEBUG
			fprintf(stdout, "Contenu restant du buffer : "); fprintf_binarray(stdout, buffer, *lg_buf); printf("\n");
			#endif

            // D <- D U {w.a}
			dict_insert(dico,concatenation(w, wlength, a), wlength+1);
			
			w = malloc(sizeof(uint8_t));
			wlength = 1;
			*w = *a;
		}
		#ifdef DEBUG
		printf("\n");
		#endif
	}

    // Ecrire sur S l'index associé à w
	// #ifdef DEBUG
	// printf("Ecrire sur S l'index associé à w\n");
	// #endif
	// dict_rechercher_mot(dico, w, wlength, &index, &taille);
	// /* On place index dans un tableau binaire */
	// binarray = dec_to_binarray(index, taille_codage);
	//  On ecrit cette representation binaire dans f_output 
	// fprintf_index(f_output, buffer, lg_buf, binarray, taille_codage);
	// #ifdef DEBUG
	// fprintf(stdout, "Contenu restant du buffer : "); fprintf_binarray(stdout, buffer, *lg_buf); printf("\n");
	// #endif

	// AjoutEOF
	#ifdef DEBUG
	printf("Ajout de EOM\n");
	printf("On ecrit donc EOM d'index %hi\n", EOM);
	#endif
	
	binarray = dec_to_binarray(EOM, taille_codage);
	fprintf_index(f_output, buffer, lg_buf, binarray, taille_codage);

	#ifdef DEBUG
	fprintf(stdout, "Contenu restant du buffer : "); fprintf_binarray(stdout, buffer, *lg_buf); printf("\n");
	#endif


	fflush_index(f_output, buffer, *lg_buf);


}


void decompression (FILE* f_input, FILE* f_output){

	dict_t dico ;

	dict_index_t i1 = 0; 
	dict_index_t i2 = 0;

	uint8_t* w1 = malloc(N * sizeof(uint8_t));
	uint8_t* w2 = malloc(N * sizeof(uint8_t));

	int len_w1 = 0;
	int len_w2 = 0;

	uint8_t* a = malloc(sizeof(uint8_t));

	uint8_t* binarray = malloc(8 * sizeof(uint8_t)); // Pour lire des 


	uint8_t* current_buffer = malloc(8 * sizeof(uint8_t));
	int* buffer_length = malloc(sizeof(int)); *buffer_length = 0 ;

    // D <- ens. de toutes les chaînes de longueur 1
	dico = dict_new();

	// i <- 1er code de S
	fread(binarray, 1, 1, f_input);
	binarray_to_dec(binarray, 8);

	// a <- chaine d'index i dans D
	dict_rechercher_index(dico, i1, a);

    // w <- [a]
	w1[0] = *a ;
	len_w1 = 1 ;


    // ecrire w sur E
	fprintf_index (f_output, current_buffer, buffer_length, w1, len_w1);


	//FIXME : A TERMINER D'ADAPTER AU BINAIRE

    // tant que la fin de S n'est pas atteinte
	while(!feof(f_input)){

        // i' <- code suivant de S
		fread(tmp, 1, 1, f_input);
		while(uint8_cmp(tmp,".",1)) {
			i2 = i2*10 + to_index(tmp,1);

			fread(tmp, 1, 1, f_input) ;
		}

        // On place la chaine d'index i2 dans w2
        // Si on a une erreur, c'est que i2 n'est pas dans dico
		if(i2 == 256){
			fprintf(f_output, "EOF" );

			break;

		} else {
			if (dict_rechercher_index(dico, i2, w2) != DICT_NOERROR){
				dict_rechercher_index(dico, i1, w2) ;
				//w2[len_w2] = a[0] ; 
			}
			//len_w2 = 1;
            // ecrire w' sur E 
			//fprintf_n_octets(f_output, w2, len_w2);
			fprintf(f_output, "%s",w2 );
			//fprintf(f_output, ".");

            // a <- 1er octet de w' 
			a[0] = w2[0] ;

            // D <- D U {w.a}
			dict_insert(dico, concatenation(w1, len_w1, a), len_w1+1);
            // i <- i'
			i1 = i2 ;
			i2 = 0;
			w1 = init_vect();

			*w1 = *a;
            // w <- chaine d'index i dans D
			dict_rechercher_index(dico, i1, w1);
			len_w1 = adapter_longueur(w1);
			w2 = init_vect();

		}
	}
	//end(FIXME : A TERMINER D'ADAPTER AU BINAIRE)
}