#include "LZW.h"


void compression (FILE* f_input, FILE* f_output){

	dict_t dico ;

	uint8_t* a = malloc(sizeof(uint8_t)) ;
	uint8_t* w = malloc(sizeof(uint8_t)) ;

	int taille ;

	dict_index_t index = 0;


        // D <- ens. de toutes les chaînes de longueur 1
	dico = dict_new();        

        // w <- [1er octet de E]
	fread(w, 1, 1, f_input);
	int wlength = 1;

        // tant que la fin de E n'est pas atteinte
	while (!feof(f_input)) {

                // a <- octet suivant de E
		fread(a, 1, 1, f_input);

                // si w .a est dans D alors
		if (dict_rechercher_mot(dico, concatenation(w, wlength, a), wlength+1, &index, &taille) ==  DICT_NOERROR) {
                       // w <- w .a                        
			w = concatenation(w, wlength, a);
			wlength++;
		}
                // sinon
		else{
                        // ecrire sur S l'index associe a w dans D 
			dict_rechercher_mot(dico, w, wlength, &index, &taille);
                        /* Ici, index est un short int (16bits) mais contient 9bits de donnees
                         * Ainsi, on utilise une procedure ecrivant les 8 premiers bits dans le fichier et sauvegardant le dernier bit afin de l'ecrire au rang suivant
                         */
			fprintf(f_output, "%d", index);
			fprintf(f_output, ".");

                        // D <- D U {w.a}
			dict_insert(dico,concatenation(w, wlength, a), wlength+1);
			
			w = malloc(sizeof(uint8_t)) ;
			wlength = 1;

			*w = *a;
		}
	}
        // ecrire sur S l'index associé à w
	dict_rechercher_mot(dico, w, wlength, &index, &taille);
	// Ajout EOF
	index = 256;
	taille = 1;
	fprintf_n_octets_comp(f_output, &index, taille);
	fprintf(f_output, ".");

}

// void decompression (FILE* f_input, FILE* f_output){

// 	dict_t dico ;

// 	dict_index_t i1 = 0; 
// 	dict_index_t i2 = 0;

// 	uint8_t* w1 = malloc(sizeof(uint8_t)) ;
// 	uint8_t* w2 = malloc(sizeof(uint8_t)) ;
// 	int len_w1 = 0, len_w2 = 0;

// 	uint8_t a[1] ;


//         // D <- ens. de toutes les chaînes de longueur 1
// 	dico = dict_new();

//         // i' <- 1er code de S
// 	fread(&i1, 1, 1, f_input) ;
//         #ifdef DEBUG
// 	printf("On a lu %d\n", i1);
//         #endif

//         // a <- chaine d'index i dans D
// 	dict_rechercher_index(dico, i1, a);

//         // w <- [a]
// 	w1[0] = a[0] ;
// 	len_w1 = 1 ;

//         // ecrire w sur E
// 	fprintf_n_octets(f_output, w1, len_w1);

//         // tant que la fin de S n'est pas atteinte
// 	while(!feof(f_input)){

//                 // i' <- code suivant de S
// 		fread(&i2, 1, 1, f_input);
//                 // #ifdef DEBUG
//                 // printf("On a lu %d\n", i2);
//                 // #endif

//                 // On place la chaine d'index i2 dans w2
//                 // Si on a une erreur, c'est que i2 n'est pas dans dico
// 		if (dict_rechercher_index(dico, i2, w2) != DICT_NOERROR){
// 			dict_rechercher_index(dico, i1, w2) ;
// 			w2[len_w2] = a[0] ; 
// 		}

//                 // ecrire w' sur E 
// 		fprintf_n_octets(f_output, w2, len_w2);

//                 // a <- 1er octet de w' 
// 		a[0] = w2[0] ;

//                 // D <- D U {w.a}
// 		dict_insert(dico, concatenation(w1, len_w1, a), len_w1+1);

//                 // i <- i'
// 		i1 = i2 ;

//                 // w <- chaine d'index i dans D
// 		dict_rechercher_index(dico, i1, w1);

// 	}

// }





void decompression (FILE* f_input, FILE* f_output){

	dict_t dico ;

	dict_index_t i1 = 0; 
	dict_index_t i2 = 0;

	uint8_t* tmp = malloc(sizeof(uint8_t)) ;


	uint8_t* w1 = malloc(sizeof(uint8_t)) ;
	uint8_t* w2 = malloc(sizeof(uint8_t)) ;
	int len_w1 = 0;

	uint8_t a[1] ;


        // D <- ens. de toutes les chaînes de longueur 1
	dico = dict_new();

	// Lecture du premier index
	// TODO : fonction de comparaison pour tableau de uint8_t afin evite warning et atoi egalement
	fread(tmp, 1, 1, f_input) ;
	while(uint8_cmp(tmp,".",1)) {
		i1 = i1*10 + to_index(tmp,1);

		fread(tmp, 1, 1, f_input) ;
	}

	    // a <- chaine d'index i dans D
	dict_rechercher_index(dico, i1, a);

        // w <- [a]
	w1[0] = a[0] ;
	len_w1 = 1 ;


        // ecrire w sur E
	//fprintf_n_octets(f_output, w1, len_w1);
	fprintf(f_output, "%s",w1 );	
	//fprintf(f_output, ".");


	i1 = 0;
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
			w1 = malloc(sizeof(uint8_t)) ;

			*w1 = *a;
                // w <- chaine d'index i dans D
			dict_rechercher_index(dico, i1, w1);
			len_w1 = adapter_longueur(w1);
			w2 = malloc(sizeof(uint8_t)) ;

		}
	}

}