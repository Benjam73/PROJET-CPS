#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/dictionnaire/dict.h"


uint8_t* concatenation (uint8_t* w, int wlength, uint8_t* a){ //longueur en nombre d'octets
  uint8_t* wa;
  int i = 0;
  for(i = 0 ; i < wlength ; i++){
    wa[i] = w[i];
  }
  wa[i+1] = a[0];
  return wa;
}



FILE codage (FILE *f){
  uint8_t* a;
  uint8_t* w;

  dict_t dico = dict_new();
  dict_index_t *index;

  fread(w, 1, 1, f);
  int wlength = 1;
  while (!feof(f)) {
       fread(a, 1, 1, f);
       if (dict_rechercher_mot(dico, concatenation(w, wlength, a) , wlength+1 , index) ==  DICT_NOERROR){
         w = concatenation(w, wlength, a);
         wlength++;
       }else{
         //TODO écrire sur le fichier de sortie l'index associé à w dans D
         dict_insert(dico, wlength, w);
         w = a;
       }
  }
}
