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


dict_index_t binarray_to_dec(uint8_t* array, int array_length);


#endif //_IO