#include "LZW.h"


void compression (FILE* f_input, FILE* f_output){
        
        uint8_t* a = NULL;
        uint8_t* w = NULL;

        int taille ;

        dict_t dico = dict_new();
        dict_index_t *index = NULL;

        fread(w, 1, 1, f_input);
        int wlength = 1;
        while (!feof(f_input)) {
                
                fread(a, 1, 1, f_input);
                
                if (dict_rechercher_mot(dico, concatenation(w, wlength, a), wlength+1, index, &taille) ==  DICT_NOERROR) {
                        w = concatenation(w, wlength, a);
                        wlength++;
                }
                else{
                        dict_rechercher_mot(dico, w, wlength+1, index, &taille);
                        fprintf_n_octets_comp(f_output, index, taille);
                        dict_insert(dico,w, wlength);
                        w = a;
                }
        }
        dict_rechercher_mot(dico, w, wlength+1, index, &taille);
        fprintf_n_octets_comp(f_output, index, taille);
}

void decompression (FILE* f_input, FILE* f_output){
                
        dict_t dico ;
        
        dict_index_t i1 = 0; 
        dict_index_t i2 = 0;

        uint8_t* w1 = malloc(sizeof(uint8_t)) ;
        uint8_t* w2 = malloc(sizeof(uint8_t)) ;
        int len_w1 = 0, len_w2 = 0;
        
        uint8_t a[1] ;

        dico = dict_new();

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

}