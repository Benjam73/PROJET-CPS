/**
 * \file IO.h
 * \brief Gestion d'entrees et sorties 
 * \author BESNIER Benjamin, DE ARAUJO Bastien, MOLION Enzo, VALETTE Léo
 * 
 * Fichier contenant les fonctions permettant d'ecrire vers ou de lire depuis un fichier et ce au format binaire depuis ou vers un codage (dict_index_t)
 * 
 */
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
 * @param[in]	n             Le code a traduire 
 * @param[in]	array_length  La longueur (nombre de bits) de la representation binaire a produire
 *
 * @return     Le tableau de 1s/0s (uint8_t) correspondant a la traduction de n en binaire
 */
uint8_t* dec_to_binarray(const dict_index_t n, const int array_length);


/**
 * @brief      Affiche dans f la representation binaire donnee
 *
 * @param[in,out]	f             Le fichier ou ecrire
 * @param[in]		binarray      La representation binaire
 * @param[in]		array_length  La longueur de la representation binaire
 */
void fprintf_binarray (FILE* f, const uint8_t *binarray, const int array_length);


/**
 * @brief      Traduit l'ecriture binaire en codage 
 *
 * @param[in]	array         L'ecriture binaire
 * @param[in]	array_length  La longueur de l'ecriture binaire
 *
 * @return     Le codage (dict_index_t) traduit depuis la forme binaire donnee en parametre
 */
dict_index_t binarray_to_dec(const uint8_t* array, const int array_length);


/**
 * @brief      Ecrit dans f la representation binaire de index apres avoir ecrit le reste du buffer  
 *
 * @param[in,out]	f               Le fichier ou ecrire
 * @param[in,out]	current_buffer  Le buffer des bits restants d'ecritures precedentes, sera ecrit en premier
 * @param[in,out]	buffer_length   La longueur du buffer
 * @param[in]		index           L'index a ecrire
 * @param[in]		index_length    La longueur de celui-ci (9 par defaut, jusqu'a atteindre un signal d'augmentation du dictionnaire)
 */
void fprintf_index (FILE* f, uint8_t* current_buffer, int* buffer_length, const uint8_t* index, const int index_length);
// Cette fonction ne doit pas etre appelee avec index valant "AgrandirDictionnaire" ni "ReinitialiserDictionnaire"


/**
 * @brief      Ecrit dans f la representation binaire current_buffer sur buffer_length bits eventuellement en ajoutant des 0s de padding
 *
 * @param[in,out]	f               Le fichier ou ecrire
 * @param[in,out]	current_buffer  La representation binaire a ecrire dans le fichier 
 * @param[in]		buffer_length   La longeur de la representation binaire a ecrire dans le fichier, comprise entre 0 et 8. Si elle est inferieure a 8, des bits de padding a 0 seront ajoutes
 */
void fflush_index (FILE* f, uint8_t* current_buffer, const int buffer_length);

/**
 * @brief      Lit (depuis current_buffer puis f) index_length bits qu'elle place dans index. Si des bits de l'octets lus n'entrent pas, ils sont ajoutes a current_buffer
 *
 * @param[in,out]	f               Le fichier ou lire
 * @param[in,out]	current_buffer  Un buffer contenant le reste des lectures precedentes. La lecture se fera prioritairement ici
 * @param[in,out]	buffer_length   La taille de current_buffer
 * @param[out]		index           La representation binaire lue
 * @param[in]		index_length    La taille de la representation binaire a lire
 */
void fread_index(FILE* f, uint8_t* current_buffer, int* buffer_length, uint8_t* index, const int index_length);

#endif //_IO