/**
 * \file RLE.h
 * \brief Gestion des fonction de RLE
 * \author BESNIER Benjamin, DE ARAUJO Bastien, MOLION Enzo, VALETTE Léo
 * 
 * Fichier contenant les fonctions permettant l'ecriture sous forme RLE 
 */

#ifndef _RLE
#define _RLE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "dict.h"
#include "chaine_carac.h"

#define true 1
#define false 0


/**
 * @brief      Procedure permettant d'écrire f_input sur forme RLE dans le fichier f_ouput
 *
 * @param      f_input   Le fichier a traduire
 * @param      f_output  Le fichier resultant ecrit en RLE
 */
void rle (FILE* f_input, FILE* f_output);

/**
 * @brief      PRocedure permettant de passer d'un fichier sous forme RLE a un fichier "classique"
 *
 * @param      f_input   Le fichier a traduire ecrit en RLE
 * @param      f_output  Le fichier resultant sous forme classique
 */
void elr (FILE* f_input, FILE* f_output);

#endif //_RLE