#include <stdlib.h>
#include <stdio.h>

#include "dict.h"


dict_error_t dict_rechercher_mot(dict_t dico, uint8_t* mot, int taille_mot, dict_index_t* resultat, int* taille){

        noeud_t noeud_courant = dico->racine;
        int i = 0;
        *taille  = 0;
        dict_error_t error = DICT_NOERROR;
        while (i < taille_mot && error != DICT_NOTFOUND) {
                while (noeud_courant != NULL && noeud_courant->sym != mot[i] ) {
                        noeud_courant = noeud_courant->frere;
                }
                if (noeud_courant != NULL && noeud_courant->sym == mot[i]) {
                        if (i == taille_mot) {
                                *resultat = noeud_courant->code;
                        }else if (noeud_courant->fils == NULL) {
                                error = DICT_NOTFOUND;
                        }else {
                                noeud_courant = noeud_courant->fils;
                                taille++;
                        }
                }else{
                        error = DICT_NOTFOUND;
                }
				i++;
        }
        return error;
}


dict_error_t dict_rechercher_index(dict_t dico, dict_index_t index, uint8_t* resultat){
        int i = 0;
        int j = 1;

        for ( i = 0; i < dico->nb_elt && dico->map[i]->code != index; i++) {
        }
        // printf("Valeur du resultat : %s \n",resultat);
	//printf(" valeur de i : %d \n",i);
        if ( dico->map[i]->code == index) {
                // printf("Valeur du resultat : %c \n",resultat[1]);
                noeud_t noeud_courant = dico->map[i];
                resultat[0] = noeud_courant->sym;
                while (noeud_courant->pere != NULL) {
                        noeud_courant = noeud_courant->pere;
                        resultat[j] = noeud_courant->sym;
                        j++;
                }
        }else{
                return DICT_NOTFOUND;
        }
        uint8_t temp;
        for (int k = 0; k <= j/2; k++) {
                temp = resultat[k];
                resultat[k] = resultat[j-k];
                resultat[j-k] = temp;
        }

        // printf("Valeur du resultat : %s \n",resultat);
        return DICT_NOERROR;
}


// Retourne le pointeur du noeud ayant c pour symbole et son frere precedent
// Les deux pointeurs vallent NULL si c n'est pas present
noeud_t rechercher_dans_ligne(noeud_t liste, uint8_t c, noeud_t frere){

	noeud_t noeud_courant = liste;
	frere = noeud_courant;

	while(noeud_courant != NULL){

		if(noeud_courant->sym == c){
			return noeud_courant;
		}
		frere = noeud_courant;
		noeud_courant = noeud_courant->frere;
	}

	return NULL;
}


// Ajoute courant dans dico a la suite de frere avec sym comme symbole
dict_error_t ajouter_dans_ligne(dict_t dico, noeud_t pere, noeud_t frere, uint8_t sym){

	noeud_t courant = malloc(sizeof(struct _node)) ;

	dico->nb_elt = dico->nb_elt + 1;
	if(frere != NULL){
		frere->frere = courant ;
	}
	courant->sym = sym ;
	courant->code = dico->nb_elt-1 ;
	courant->fils = NULL ;
	courant->frere = NULL ;
	courant->pere = pere ;

	dico->map[dico->nb_elt-1] = courant;

 	//printf("valeur de map[%d] = %d \n",dico->nb_elt-1,dico->map[dico->nb_elt-1]->code);
	//printf(" valeur de map de 0 : %d \n ",dico->map[0]->code);


	return DICT_NOERROR ;
}


dict_error_t dict_insert(dict_t dico, uint8_t* mot, int taille_mot){

	dict_index_t index ;

	noeud_t ligne_courante = dico->racine;
	int index_caractere_courant = 0;
	noeud_t noeud_courant = malloc(sizeof(struct _node));
	noeud_t noeud_pere = NULL;
	noeud_t noeud_frere = malloc(sizeof(struct _node));
	int taille;


	if (dict_rechercher_mot(dico, mot, taille_mot, &index, &taille) == DICT_NOTFOUND){
		while (index_caractere_courant < taille_mot){
			noeud_courant = rechercher_dans_ligne(ligne_courante, mot[index_caractere_courant], noeud_frere);

			if (noeud_courant != NULL){
				noeud_pere = malloc(sizeof(noeud_t));
				noeud_pere = noeud_courant;
				index_caractere_courant++;
			}
			else{
				ajouter_dans_ligne(dico, noeud_pere, noeud_frere, mot[index_caractere_courant]);
				return DICT_ADDED;
			}

			ligne_courante = noeud_courant->fils;
		}
	}
	return DICT_FOUND ;
}


void dict_print (dict_t dico){

	uint8_t* mot_courant = malloc(sizeof(uint8_t)) ;
        // printf("Mot courant : %s\n", i, mot_courant);

	for (int i = 0; i < dico->nb_elt; i++){
		dict_rechercher_index(dico, i, mot_courant);
                printf("Code : %d \t Mot courant : %s\n", i, mot_courant);
		// printf("Code : %d \t Mot courant : %c\n", i, mot_courant[1]);
	}

}


dict_t dict_new(){

	dict_t dico = malloc(sizeof(struct _dict)) ;

	dico-> nb_elt = 0 ;

	// uint8_t  mot_courant[2];
        uint8_t*  mot_courant = malloc(sizeof(uint8_t));

	mot_courant[1] = '\0' ;

	for(int i = 0 ; i < 256 ; i++){
		// mot_courant[0] = (uint8_t) i ;
                *mot_courant = (uint8_t) i ;
                // printf("code : %d - mot_courant :  %s\n", (int) i,  mot_courant);
		dict_insert(dico, mot_courant, 1);
	}

        // dict_print(dico);
	//printf(" valeur de map de 0 : %d \n ",dico->map[0]->code);

	// TODO : ajout cas speciaux
	// EndOfMessage, ResetDictionnaire, AgrandirDictionnaire


	return dico ;
}



dict_error_t dict_reinit(dict_t dico){

	for(int i=256; i<TAILLE_MAX; i++){
		free(dico->map[i]);
		dico->map[i] = NULL;
	}

	return DICT_NOERROR;

}
