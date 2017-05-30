/**
 * \file dict.h
 * \brief Gestion du dictionnaire
 * \author BESNIER Benjamin, DE ARAUJO Bastien, MOLION Enzo, VALETTE Léo
 * 
 * Fichier contenant definitions et les fonctions utiles a la gestion du dictionnaire
 * 
 */

#ifndef DICT_H
#define DICT_H
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
typedef int bool ;
#define true 1
#define false 0

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
 * \struct hashmap
 * \brief Donne un pointeur de noeud et la longueur du mot associe
 */
typedef struct {
  noeud_t noeud;
  int taille ;
}hashmap;

/**
 * \struct _dict
 * \brief Dictionnaire défini par son nombre d'elements, le noeud racine et une map index -> noeud
 */
struct _dict{
  dict_index_t nb_elt ;
  noeud_t racine ;
  hashmap map[TAILLE_MAX] ;
};

/**
 * \struct _node
 * \brief Noeud defini par un symbole, un index, un pointeur vers son noeud pere, un pointeur vers son noeud frere et un pointeur vers son noeud fils
 */
struct _node {
  uint8_t sym ; // Le char suffixe
  dict_index_t code ; // Le code associe au symbole
  struct _node* frere ; // Le noeud suivant dans la liste de meme niveau
  struct _node* fils ; // Le noeud de profondeur superieure
  struct _node* pere ; // Le noeud de profondeur inferieure
};

#define EOM 256
#define AD 257
#define RD 258

/**
 * @brief      Affiche le dictionnaire (pour toute : entree index et symbole)
 *
 * @param[in]  dico  Le dictionnaire a afficher
 */
void dict_print (const dict_t dico);


/**			
 * @brief   Alloue et renvoie un dictionnaire compose des prefixes de taille 1  
 */
dict_t dict_new();


/**
 * @brief      Supprime dans le dictionnaire les entrees autres que des prefixes de taille 1
 *
 * @param[in,out]  dico  Le dictionnaire a reinitialiser
 */ 
dict_error_t dict_reinit(dict_t dico);

/**
 * @brief      Ajoute la chaine de caractere mot au dictionnaire dico
 *
 * @param[in,out]  dico        Le dictionnaire auquel on ajoute un mot
 * @param[in]      mot         Le mot a ajouter
 * @param[in]  taille_mot  le taille du mot
 *
 * @return     Le code d'erreur correspondant suivant l'execution de la fonction
 */

dict_error_t dict_insert(dict_t dico, const uint8_t* mot, const int taille_mot) ;

/**
 * @brief      Renvoie dans resultat le codage correspondant a mot
 *
 * @param[in]   dico        Le dictionnaire ou on recherche le codage
 * @param[in]   mot         Le mot a rechercher correspondant au codage
 * @param[in]   taille_mot  La taille du mot
 * @param[out]  resultat    Le resultat ou l'on stock le codage de mot
 * @param[out]  taille      La taille du codate en nombre de bits
 *
 */
dict_error_t dict_rechercher_mot(const dict_t dico, const uint8_t* mot, const int taille_mot, dict_index_t* resultat, int* taille);


/**
 * @brief      Renvoie dans resultat le mot correspondant au codage index
 *
 * @param[in]  dico      Le dictionnaire ou on recherche le mot
 * @param[in]  index     Le codage du mot a rechercher
 * @param[out]      resultat  L'index trouve
 * @param[out]  taille_resultat La taille du de l'index trouve (en nombre de bits)
 */
dict_error_t dict_rechercher_index(const dict_t dico, const dict_index_t index, uint8_t* resultat, int* taille_resultat);

/**
 * @brief      Permet de liberer la mémoire allouer pour le dictionnaire
 *
 * @param[in,out]  dico  Le dictionnaire a liberer
 */
void free_dico(dict_t dico);


#endif // DICT_H
