/**
 * \file chaine_carac.h
 * \brief Gestion de l'ecriture dans les fichiers
 * \author BESNIER Benjamin, DE ARAUJO Bastien, MOLION Enzo, VALETTE Léo
 * 
 * Fichier contenant les fonctions de traitement de chaine de caractere
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
 * @brief      Fonction permettant d'ecrire n octets contenant de word dans le fichier f
 *
 * @param      f     Fichier où l'on écrit les n octets
 * @param      word  La chaine de caractere a ecrire
 * @param[in]  n     Le nombre d'octet a ecrire
 */
void fprintf_n_octets(FILE* f, uint8_t* word, int n) ;

/**
 * @brief      Fonction permettant d'ecrire n octets contenant de word dans le fichier f
 *
 * @param      f     Fichier où l'on écrit les n octets
 * @param      index  La chaine de caractere a ecrire
 * @param[in]  n     Le nombre d'octet a ecrire
 */
void fprintf_n_octets_comp(FILE* f, dict_index_t* index, int n);

/**
 * @brief      Fonction permettant de concatener une chaine de caractere et un caractere
 *
 * @param      w        La chaine de caratere
 * @param[in]  wlength  La longeur de la chaine w
 * @param      a        Le caractere a concatener
 *
 * @return     La chaine w concatener avec a
 */
uint8_t* concatenation(uint8_t* w, int wlength, uint8_t* a);

#endif //_STRING
