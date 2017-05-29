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

/**
 * @brief      Permet de nous donner la taille du tableau w1
 *
 * @param      w1    Le tableau dont il faut determiner la taille
 *
 * @return     La taille du tableau
 */
int adapter_longueur(uint8_t* w1);


/**
 * @brief      Fonction strcmp mais pour tableau de uint8_t
 *
 * @param      tab     Le premier tableau a comparer
 * @param      tab2    Le deuxieme tableau a comparer
 * @param[in]  taille  La taille du premier tableau
 *
 * @return     renvoie 1 si les tableaux sont identiques, 0 sinon
 */
int uint8_cmp(uint8_t* tab, char* tab2, int taille);


/**
 * @brief      Fonction atoi
 *
 * @param      tab     Le tableau a convertir en dict_index_t
 * @param[in]  taille  La taille du tableau
 *
 * @return     Le tableau tab convertie en dict_index_t
 */
dict_index_t to_index(uint8_t* tab, int taille);

/**
 * @brief      Fonction permettant d'allouer un vecteur vide en memoire
 *
 * @return     Le vecteur allouer en mémoire
 */
uint8_t* init_vect();


/**
 * @brief      Fonction permettant de vider un vecteur
 *
 * @param      tab     Le vecteur a vider
 * @param[in]  taille  La taille du vecteur
 */
void fflush_vect(uint8_t* tab, int taille);

#endif //_STRING
