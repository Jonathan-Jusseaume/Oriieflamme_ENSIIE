/**
 * @file carte.h
 * @brief Fichier contenant la structure liée aux cartes
 */
#ifndef ORIIEFLAMME_GR_11_CARTE_H
#define ORIIEFLAMME_GR_11_CARTE_H

#include "constante.h"
#include "position.h"

/**
 * Structure représentant une carte.
 */
typedef struct s_carte *carte;


/**
 * Fonction qui permet d'initialiser une carte
 * @param nom : nom de la carte
 * @param effet : effet de la carte
 * @param effet_carte : pointeur sur fonction vers l'effet de la carte
 * @param identifiant_faction : identifiant la faction
 * @param numero_plateau : entier représentant la numéro de la carte sur le plateau.
 * @param est_face_cachee : état de la carte : VRAI = face cachée, FAUX = face visible.
 * @return carte : pointeur vers la carte
 */
carte initialiser_carte(char *nom, char *effet, void *effet_carte, int identifiant_faction, int numero_plateau,
                        booleen est_face_cachee);


#endif //ORIIEFLAMME_GR_11_CARTE_H