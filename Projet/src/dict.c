#include <stdlib.h>
#include <stdio.h>

#include "dict.h"


// Retourne le pointeur du noeud ayant c pour symbole et son frere precedent 
// Les deux pointeurs vallent NULL si c n'est pas present
noeud_t rechercher_dans_ligne(noeud_t liste, char c, noeud_t frere){
	
	noeud_t noeud_courant = liste;
	frere = NULL;

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
dict_error_t ajouter_dans_ligne(dict_t dico, noeud_t pere, noeud_t frere, char sym){

	noeud_t courant = malloc(sizeof(noeud_t)) ;

	dico->nb_elt = dico->nb_elt + 1;
	frere->frere = courant ;

	courant->sym = sym ;
	courant->code = dico->nb_elt ;
	courant->fils = NULL ;
	courant->frere = NULL ;
	courant->pere = pere ;

	return DICT_NOERROR ;
}


dict_error_t dict_insert(dict_t dico, char* mot, int taille_mot){

	dict_index_t index ;

	noeud_t ligne_courante = dico->racine;
	int index_caractere_courant = 0;
	noeud_t noeud_courant ;
	noeud_t noeud_pere ;
	noeud_t noeud_frere ;

	if (dict_rechercher_mot(dico, mot, taille_mot, &index) == DICT_NOTFOUND){
		while (index_caractere_courant < taille_mot){
			noeud_courant = rechercher_dans_ligne(ligne_courante, mot[index_caractere_courant], noeud_frere);

			if (noeud_courant != NULL){
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

	char* mot_courant ;

	for (int i = 0; i < dico->nb_elt; i++){
		dict_rechercher_index(dico, i, mot_courant);
		printf("Code : %d \t Mot courant : %s\n", i, mot_courant);
	}

}


dict_t dict_new(){
	
	dict_t dico = malloc(sizeof(dict_t)) ;

	dico->nb_elt = 0 ;

	char * mot_courant ;

	mot_courant[1] = '\0' ;

	for(int i = 0 ; i < 256 ; i++){
		mot_courant[0] = (char) i ;
		dict_insert(dico, mot_courant, 1);
	}

	// TODO : ajout cas speciaux 
	// EndOfMessage, ResetDictionnaire, AgrandirDictionnaire
	

	return dico ;
}