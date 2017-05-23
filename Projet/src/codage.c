#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/dictionnaire/dict.h"
#include "../include/string.h"




FILE* codage (FILE *f){
        uint8_t* a = NULL;
        uint8_t* w = NULL;

        FILE* f_out = NULL;

        int taille ;

        dict_t dico = dict_new();
        dict_index_t *index = NULL;

        fread(w, 1, 1, f);
        int wlength = 1;
        while (!feof(f)) {
                fread(a, 1, 1, f);
                if (dict_rechercher_mot(dico, concatenation(w, wlength, a), wlength+1, index, &taille) ==  DICT_NOERROR) {
                        w = concatenation(w, wlength, a);
                        wlength++;
                }else{
                        //TODO écrire sur fout l'index associé à w dans D
                        dict_rechercher_mot(dico, w, wlength+1, index, &taille);
                        fprintf_n_octets_comp(f_out, index, taille);
                        dict_insert(dico,w, wlength);
                        w = a;
                }
        }
        //TODO écrire sur fout l'index associé à w dans D
        dict_rechercher_mot(dico, w, wlength+1, index, &taille);
        fprintf_n_octets_comp(f_out, index, taille);
        return f_out;
}
