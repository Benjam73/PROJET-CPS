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

	bool EOM_received = false ;

	dict_t dico ;

	dict_index_t i1 = 0; 
	dict_index_t i2 = 0;

	uint8_t* w1 = malloc(8 * sizeof(uint8_t)); // 8 car au debut vaut le mot de premier index lu -> un seul caractere
	uint8_t* w2 = malloc(16 * sizeof(uint8_t)); // 16 car vaut la premiere fois au plus une chaine de deux carac si les deux premiers carac du fichier a compresser sont identiques 
	uint8_t* chaine_temp = malloc(8 * sizeof(uint8_t)); // On le malloc a nouveau dans dict_rechercher_index 


	int* len_w1 = malloc(sizeof(int)); *len_w1 = 0;
	int* len_w2 = malloc(sizeof(int)); *len_w2 = 0;
	int* len_a = malloc(sizeof(int)); *len_a = 0;
	int* len_chaine_temp = malloc(sizeof(int)); *len_chaine_temp = 0;

	uint8_t* a = malloc(sizeof(uint8_t));

	uint8_t* binarray = malloc(8 * sizeof(uint8_t)); // Pour lire des representations binaires d'index
	int binarray_length = 9 ;

	uint8_t* current_buffer = malloc(8 * sizeof(uint8_t));
	int* buffer_length = malloc(sizeof(int)); *buffer_length = 0 ;

    // D <- ens. de toutes les chaînes de longueur 1
	dico = dict_new();

	// i1 <- 1er code de S
	fread_index(f_input, current_buffer, buffer_length, binarray, binarray_length);
	i1 = binarray_to_dec(binarray, binarray_length);

	// a <- chaine d'index i dans D
	dict_rechercher_index(dico, i1, a, len_a);

    // w1 <- [a]
	w1[0] = *a ;
	*len_w1 = 1 ;


    // ecrire w sur E
	fprintf_index (f_output, current_buffer, buffer_length, w1, *len_w1);


	//FIXME : A TERMINER D'ADAPTER AU BINAIRE

    // tant que la fin de S n'est pas atteinte
	while (!feof(f_input) && !EOM_received){

        // i2 <- code suivant de S
		fread_index(f_input, current_buffer, buffer_length, binarray, binarray_length);
		i2 = binarray_to_dec(binarray, binarray_length);

		switch (i2){
			case EOM : 
				EOM_received = true ;
				break;
			case AD :
				// TODO : implementer AgrandirDictionnaire
				/* Code */
			break;
			case RD:
				// TODO : implementer ReinitialiserDictionnaire
				/* Code */
			break;
			default:
			
				// Si i1 appartient a D alors
				if (dict_rechercher_index(dico, i1, chaine_temp, len_chaine_temp) == DICT_NOERROR){
					// w2 <- chaine d'index i2 dans D
					dict_rechercher_index(dico, i2, w2, len_w2);
				}
				// Si i1 n'appartient pas a D alors 
				else{
					// w2 <- chaîne d'index i1 dans D
					dict_rechercher_index(dico, i1, w2, len_w2);
					// w2 <- w2.a
					w2 = concatenation(w2, *len_w2, a);
					len_w2++;
				}


	            // ecrire w2 sur E 
				fprintf_n_octets(f_output, w2, *len_w2);


	            // a <- 1er octet de w' 
				a[0] = w2[0] ;

	            // D <- D U {w.a}
				dict_insert(dico, concatenation(w1, *len_w1, a), (*len_w1) + 1);
	            
	            // i1 <- i2
				i1 = i2 ;

	            // w <- chaine d'index i dans D
	            dict_rechercher_index(dico, i1, w1, len_w1);
				
			
		}
	}
	//end(FIXME : A TERMINER D'ADAPTER AU BINAIRE)
}