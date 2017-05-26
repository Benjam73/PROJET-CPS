#ifndef _IO
#define _IO

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "dict.h"

void test_IO();

/**
 * @brief      Traduit n en sa representation binaire
 *
 * @param[in]	n             le code (dict_index_t) a traduire 
 * @param[in]	array_length  la longueur de la representation binaire (en nombre de bits)
 *
 * @return     le tableau de 1/0 (uint8_t) correspondant a la traduction de n en binaire
 */
uint8_t* dec_to_binarray(dict_index_t n, int array_length);


/**
 * @brief      Affiche dans f la representation binaire donnee
 *
 * @param      f             le fichier ou ecrire
 * @param      binarray      la representation binaire
 * @param[in]  array_length  la longueur de la representation binaire
 */
void fprintf_binarray (FILE* f, uint8_t *binarray, const int array_length);

/**
 * @brief      Traduit l'ecriture binaire en codage 
 *
 * @param      array         l'ecriture binaire
 * @param[in]  array_length  la longueur de l'ecriture binaire
 *
 * @return     le codage (dict_index_t) traduit depuis la forme binaire donnee en parametre
 */
dict_index_t binarray_to_dec(uint8_t* array, int array_length);

/**
 * @brief      Ecrit dans f la representation binaire de index apres avoir ecrit le reste du buffer  
 *
 * @param      f               le fichier ou ecrire
 * @param      current_buffer  le buffer des bits restants d'ecritures precedentes, sera ecrit en premier
 * @param      buffer_length   la longueur du buffer
 * @param      index           l'index a ecrire
 * @param      index_length    la longueur de celui-ci (9 par defaut, jusqu'a atteinder signal d'augmentation du dictionnaire)
 */
void fprintf_index (FILE* f, uint8_t* current_buffer, int* buffer_length, uint8_t* index, int* index_length);
// Cette fonction ne doit pas etre appelee avec index valant "AgrandirDictionnaire" ni "ReinitialiserDictionnaire"


#endif //_IO