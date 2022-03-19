/**
 * @file carte.h
 * @brief Fichier contenant la structure liée aux cartes
 */
#ifndef ORIIEFLAMME_GR_11_CARTE_H
#define ORIIEFLAMME_GR_11_CARTE_H

#include "constante.h"

/**
 * Structure représentant une carte.
 */
typedef struct s_carte
{
    /**
     * Chaîne de caractère représentant le nom de la carte.
     */
    char *nom;
    /**
     * Chaîne de caractère représentant l'effet de la carte.
     */
    char *effet;
    /**
     * Entier représentant l'identifiant de la faction qui possède la carte.
     */
    int identifiant_faction;
    /**
     * Entier représentant la numéro de la carte sur le plateau.
     * Il sera initialisé à -1 pour signifier que la carte n'est pas présente sur le plateau.
     * (par exemple la première carte aura son champ numero_plateau = 0).
     */
    int numero_plateau;
    /**
     * Booléen représentant l'état de la carte : VRAI = face cachée, FAUX = face visible.
     */
    booleen est_face_cachee;

}*carte;

#endif //ORIIEFLAMME_GR_11_CARTE_H