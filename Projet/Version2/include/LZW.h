/**
 * \file LZW.h
 * \brief codage et decodage
 * \author BESNIER Benjamin, DE ARAUJO Bastien, MOLION Enzo, VALETTE Léo
 * 
 * Fichier contenant les fonctions permettant de compresser ou decompresser un fichier
 * 
 */

#ifndef _LZW
#define _LZW

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "dict.h"
#include "chaine_carac.h"
#include "IO.h"

/**
 * @brief      Place la compression du contenu de f_input dans f_output
 *
 * @param      f_input   Le fichier a compresser
 * @param      f_output  Le fichier contenant le fichier compresse
 */
void compression (FILE* f_input, FILE* f_output);

/**
 * @brief      Place la decompression du contenu de f_input dans f_output
 *
 * @param      f_input   Le fichier a decompresser
 * @param      f_output  Le fichier contenant le contenu decompresse
 */
void decompression (FILE* f_input, FILE* f_output);

#endif //_LZW