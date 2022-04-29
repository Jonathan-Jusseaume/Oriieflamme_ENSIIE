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
 * @return carte : pointeur vers la carte
 */
carte initialiser_carte(char *nom, char *effet, void *effet_carte, int identifiant_faction, int numero_plateau,
                        booleen est_face_cachee);


#endif //ORIIEFLAMME_GR_11_CARTE_H