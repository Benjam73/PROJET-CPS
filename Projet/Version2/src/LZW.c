#include "LZW.h"

void compression (FILE* f_input, FILE* f_output){

	bool EOM_sent = false ;

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

    // tant que la fin de E n'est pas atteinte
	while (!feof(f_input) && !EOM_sent) {

        // a <- octet suivant de E
		fread(a, 1, 1, f_input);

        // si w.a est dans D alors
		if (dict_rechercher_mot(dico, concatenation(w, wlength, a), wlength + 1, &index, &taille) ==  DICT_NOERROR) {

			#ifdef DEBUG
			uint8_t* DEBUG_wa = malloc(2 * sizeof(uint8_t)) ; 
			DEBUG_wa = concatenation(w, wlength, a);
			fprintf_n_octets(stdout, DEBUG_wa, wlength + 1);printf(" trouve dans le dictionnaire\n");
			#endif

            // w <- w.a
			w = concatenation(w, wlength, a);
			wlength++;

		}
        // sinon
		else{

			#ifdef DEBUG
			uint8_t* DEBUG_wa = malloc(2 * sizeof(uint8_t)) ; 
			DEBUG_wa = concatenation(w, wlength, a);
			fprintf_n_octets(stdout, DEBUG_wa, wlength + 1);printf(" non trouve dans le dictionnaire\n");
			#endif


            // Ecrire sur S l'index associe a w dans D 
			if(dict_rechercher_mot(dico, w, wlength, &index, &taille) != DICT_NOERROR){
				printf("Erreur de dictionnaire\n");
				exit(EXIT_FAILURE);
			}

			#ifdef DEBUG
			printf("On ecrit donc ");fprintf_n_octets(stdout, w, wlength);printf(" d'index %hi = ", index);fprintf_binarray(stdout, dec_to_binarray(index,9), 9); fprintf(stdout, "\n");
			#endif
			
			/* On place index dans un tableau binaire */
			binarray = dec_to_binarray(index, taille_codage);
			/* On ecrit cette representation binaire dans f_output */
			fprintf_index(f_output, buffer, lg_buf, binarray, taille_codage);


			// Si le nombre d'element du dictionnaire depasse le nombre d'elements representable avec la taille de codage actuelle, on agrandit celle-ci 
			if(dico->nb_elt >= (1 << taille_codage)){
				binarray = dec_to_binarray(AD, taille_codage);
				fprintf_index(f_output, buffer, lg_buf, binarray, taille_codage);
				taille_codage++;
			} 
            // Si le nombre d'element du dictionnaire depasse le nombre d'elements qu'il peut stocker, on le reinitialise 
			else if (dico->nb_elt >= TAILLE_MAX){
				binarray = dec_to_binarray(RD, taille_codage);
				fprintf_index(f_output, buffer, lg_buf, binarray, taille_codage);
				dict_reinit(dico);
				taille_codage = 9;

			}

            // D <- D U {w.a}
			dict_insert(dico,concatenation(w, wlength, a), wlength+1);

			free(w);
			w = malloc(sizeof(uint8_t));
			wlength = 1;
			*w = *a;
		}
	}



	// AjoutEOF
	#ifdef DEBUG
	printf("Ajout de EOM\n");
	#endif
	
	binarray = dec_to_binarray(EOM, taille_codage);
	fprintf_index(f_output, buffer, lg_buf, binarray, taille_codage);

	fflush_index(f_output, buffer, *lg_buf);
	free(buffer);
	free(w);
	free(a);
	free(lg_buf);
	free_dico(dico);

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
	#ifdef DEBUG
	fprintf(stdout, "On a recupere l'index : "); fprintf_binarray(stdout, binarray, binarray_length); printf("\n");
	#endif

	// a <- chaine d'index i dans D
	dict_rechercher_index(dico, i1, a, len_a);

    // w1 <- [a]
	w1[0] = *a ;
	*len_w1 = 1 ;


    // ecrire w sur E
	#ifdef DEBUG
	printf("On ecrit ");fprintf_n_octets(stdout, w1, *len_w1);printf("\n");
	#endif
	fprintf_n_octets(f_output, w1, *len_w1);
	

    // tant que la fin de S n'est pas atteinte
	while (!feof(f_input) && !EOM_received){

        // i2 <- code suivant de S
		fread_index(f_input, current_buffer, buffer_length, binarray, binarray_length);
		i2 = binarray_to_dec(binarray, binarray_length);
		#ifdef DEBUG
		fprintf(stdout, "On a recupere l'index : "); fprintf_binarray(stdout, binarray, binarray_length); printf("\n");
		#endif


		switch (i2){
			case EOM : 
			EOM_received = true ;
			break;
			case AD :
			binarray_length++;
			break;
			case RD:
			binarray_length = 9;
			dict_reinit(dico);
			break;
			default:
				// Si i1 appartient a D alors
			if (dict_rechercher_index(dico, i2, chaine_temp, len_chaine_temp) == DICT_NOERROR){
					// w2 <- chaine d'index i2 dans D
					#ifdef DEBUG
				printf("%hi trouve dans le dictionnaire\n", i2);
					#endif
				dict_rechercher_index(dico, i2, w2, len_w2);
			}
				// Si i1 n'appartient pas a D alors 
			else{
					#ifdef DEBUG
				printf("%hi NON trouve dans le dictionnaire\n", i1);
					#endif
					// w2 <- chaîne d'index i1 dans D
				dict_rechercher_index(dico, i1, w2, len_w2);
					// w2 <- w2.a
				w2 = concatenation(w2, *len_w2, a);
				len_w2++;
			}


	            // ecrire w2 sur E 
	            #ifdef DEBUG
			printf("On ecrit ");fprintf_n_octets(stdout, w2, *len_w2);printf("\n");
	            #endif
			fprintf_n_octets(f_output, w2, *len_w2);


	            // a <- 1er octet de w' 
			a[0] = w2[0] ;

	            // D <- D U {w.a}
		        #ifdef DEBUG
			printf("On ajoute ");fprintf_n_octets(stdout, concatenation(w1, *len_w1, a), (*len_w1) + 1);printf(" au dictionnaire\n");
	            #endif


			dict_insert(dico, concatenation(w1, *len_w1, a), (*len_w1) + 1);

	            // i1 <- i2
			i1 = i2 ;

	            // w <- chaine d'index i dans D
			dict_rechercher_index(dico, i1, w1, len_w1);

			
		}

		#ifdef DEBUG
		if (EOM_received){
			printf("On a lu EOM, fin de decompression\n");
		}
		#endif 
	}

	free(w1);
	free(w2);
	free(a);
	free(binarray);
	free(buffer_length);
	free(current_buffer);
	free_dico(dico);
}