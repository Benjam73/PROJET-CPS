/**
 * \file dict.h
 * \brief Gestion du dictionnaire
 * \author BESNIER Benjamin, DE ARAUJO Bastien, MOLION Enzo, VALETTE Léo
 * 
 * Fichier contenant les fonctions de gestion du dictionnaire
 * 
 */

#ifndef DICT_H
#define DICT_H
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 

typedef short int dict_index_t;  	// le type index
typedef long dict_char_t;          // le type valeur/caractere

typedef struct _dict *dict_t;
typedef struct _node *noeud_t;

/**
*\enum dict_error_t
*\brief Type enumere gerrant les codes d'erreurs 
*/
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

/**
 * \struct _dict
 * \brief Structure caracterisant un dictionnaire, contient le nombre d'element de celui-ci, un pointeur vers _node et un tableau de pointeur de _node
 */
struct _dict{
  dict_index_t nb_elt ;
  noeud_t racine ;
  noeud_t map[TAILLE_MAX] ;
};

/**
 * \struct _node
 * \brief Structure caracterisant un noeud, chaque noeud possede un symbole, un code et pointeur vers sont noeud pere, un vers sont frere et un vers sont fils
 */
struct _node {
  uint8_t sym ;          // Le char suffixe
  dict_index_t code ; // Le code associe au symbole
  struct _node* frere ;   // Le noeud suivant dans la liste de meme niveau
  struct _node* fils ;    // Le noeud de profondeur superieure
  struct _node* pere ;    // Le noeud de profondeur inferieure
};

#define EOM 256
#define AD 257
#define RD 258

/**
 * @brief      Fonction affichant le dictionnaire
 *
 * @param[in]  dico  Le dictionnaire a afficher
 */
void dict_print (dict_t dico);

/**			
 * @brief   Alloue et renvoie un dictionnaire compose des prefixes de taille 1  
 */
dict_t dict_new();

/**
 * @brief      Supprime dans le dictionnaire les entrees autres que des prefixes de taille 1
 *
 * @param[in]  dico  Le dictionnaire a reinitialiser
 */

 
dict_error_t dict_reinit(dict_t dico);

/**
 * @brief      Ajoute la chaine de caractere mot au dictionnaire dico
 *
 * @param[in]  dico        Le dictionnaire auquel on ajoute un mot
 * @param      mot         Le mot a ajouter
 * @param[in]  taille_mot  le taille du mot
 *
 * @return     Le code d'erreur correspondant suivant l'execution de la fonction
 */

dict_error_t dict_insert(dict_t dico, uint8_t* mot, int taille_mot) ;

/**
 * @brief      Renvoit dans resultat le codage correspondant a mot
 *
 * @param[in]  dico        Le dictionnaire ou on recherche le codage
 * @param      mot         Le mot a rechercher correspondant au codage
 * @param[in]  taille_mot  La taille du mot
 * @param      resultat    Le resultat ou l'on stock le codage de mot
 * @param      taille      La taille du codate en nombre de bit
 *
 * @return     Le code d'erreur correspondant suivant l'execution de la fonction
 */
dict_error_t dict_rechercher_mot(dict_t dico, uint8_t* mot, int taille_mot, dict_index_t* resultat, int* taille);


/**
 * @brief      Renvoit dans resultat le mot correspondant au codage index
 *
 * @param[in]  dico      Le dictionnaire ou on recherche le mot
 * @param[in]  index     Le codage du mot a rechercher
 * @param      resultat  Permet de stocker le mot correspondant a l'index
 *
 * @return     Le code d'erreur correspondant suivant l'execution de la fonction
 */
dict_error_t dict_rechercher_index(dict_t dico, dict_index_t index, uint8_t* resultat);



#endif // DICT_H
