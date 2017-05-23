#ifndef DICT_H
#define DICT_H

typedef short int dict_index_t;  	// le type index
typedef long dict_char_t;          // le type valeur/caractere

typedef struct _dict *dict_t;
typedef struct _node *noeud_t;

// Return codes
typedef enum {
  DICT_NOERROR=0,    // uniquement pour info et node_content
  DICT_NODICT=1,    // dictionnaire invalide
  DICT_INVALID=2,   // index ou prefixe invalide
  DICT_NOTFOUND=3,  // noeud cherche absent
  DICT_FOUND=4, 	// noeud (deja) present
	DICT_ADDED=5, 	// noeud ajoute
  DICT_FULL=6,      // erreur en insertion : plus de place
  DICT_FUNCERROR=7, // uniquement pour apply
  DICT_MALLOCERROR=8  // pour getstring
}dict_error_t;

// constantes dict_index_t 
#define DICT_ROOT_INDEX	-1		// index de la racine
#define DICT_NONODE -2			// Index de noeud illegal

// constantes dict_char_t
#define DICT_CHAR_EOS	-1		// End of string (valeur de racine)
#define DICT_CHAR_NOCHAR -2		// Valeur indefinie

// TAILLE_MAX = 2^15
#define TAILLE_MAX 32768

struct _dict{
  dict_index_t nb_elt ;
  noeud_t racine ;
  noeud_t map[TAILLE_MAX] ;
};

struct _node {
  char sym ;          // Le char suffixe
  dict_index_t code ; // Le code associe au symbole
  struct _node* frere ;   // Le noeud suivant dans la liste de meme niveau
  struct _node* fils ;    // Le noeud de profondeur superieure
  struct _node* pere ;    // Le noeud de profondeur inferieure
};


// Alloue et renvoie un dictionnaire compose des prefixes de taille 1
dict_t dict_new();

// Supprime dans le dictionnaire les entrees autres que des prefixes de taille 1
dict_error_t dict_reinit(dict_t dico);

// Ajoute la chaine de caractere mot au dictionnaire dico
dict_error_t dict_insert(dict_t dico, char* mot, int taille_mot) ;

// Renvoit dans resultat le codage correspondant a mot
dict_error_t dict_rechercher_mot(dict_t dico, char* mot, int taille_mot, dict_index_t* resultat);

// Renvoit dans resultat le mot correspondant au codage index
dict_error_t dict_rechercher_index(dict_t dico, dict_index_t index, char* resultat);



#endif // DICT_H
