/**
 * \file chaine_carac.h
 * \brief Gestion de l'ecriture dans les fichiers
 * \author BESNIER Benjamin, DE ARAUJO Bastien, MOLION Enzo, VALETTE Léo
 * 
 * Fichier contenant les fonctions de traitement de chaine de caractere (tableau d'octets uint8_t)
 * 
 */

#ifndef _STRING
#define _STRING

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "dict.h"

void test_chaine_carac();

/**
 * @brief      Ecrit n octets de word dans f
 *
 * @param[in,out]	f     Fichier ou ecrire
 * @param[in]		word  La chaine de caractere a ecrire
 * @param[in]		n     Le nombre d'octet a ecrire
 */
void fprintf_n_octets(FILE* f, const uint8_t* word, const int n) ;


/**
 * @brief      Renvoit la concatenation du tableau d'octets w de taille wlength et de l'octet a
 *
 * @param[in]	w        La chaine de caratere
 * @param[in]	wlength  La longeur de la chaine w
 * @param[in]	a        L'octet a concatener
 *
 * @return     Le tableau d'octet forme par la concatenation du tableau d'octets w et de l'octet a donc de taille wlength + 1
 */
uint8_t* concatenation(const uint8_t* w, const int wlength, const uint8_t* a);


#endif //_STRING
