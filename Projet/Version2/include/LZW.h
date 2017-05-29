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
 * @brief      Fonction compressant le fichier f_input et ecrivant le resultat de f_output
 *
 * @param      f_input   Le fichier a compresser
 * @param      f_output  Le fichier contenant le fichier compresser
 */
void compression (FILE* f_input, FILE* f_output);

/**
 * @brief      Fonction decompressant le fichier f_input et ecrivant le resultat de f_output
 *
 * @param      f_input   Le fichier a decompresser
 * @param      f_output  Le fichier contenant le fichier decompresser
 */
void decompression (FILE* f_input, FILE* f_output);

#endif //_LZW