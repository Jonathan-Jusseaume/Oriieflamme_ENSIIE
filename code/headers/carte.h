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
typedef struct s_carte *carte;

/**
 * Fonction permettant de recupérer le nom de la carte.
 * @param c : pointeur sur la carte dont on veut récuperer le nom.
 * @return chaîne de caractères représentant le nom de la carte.
 */
char *get_nom_carte(carte c);

/**
 * Fonction permettant de recupérer l'effet de la carte.
 * @param c : pointeur sur la carte dont on veut récuperer l'effet.
 * @return chaîne de caractères représentant l'effet de la carte.
 */
char *get_effet(carte c);

/**
 * Fonction permettant de recupérer l'identifiant_faction de la carte.
 * @param c : pointeur sur la carte dont on veut récuperer l'identifiant_faction.
 * @return entier représentant l'identifiant_faction de la carte.
 */
int get_identifiant_faction_carte(carte c);

/**
 * Fonction permettant de recupérer le numero_plateau de la carte.
 * @param c : pointeur sur la carte dont on veut récuperer le numero_plateau.
 * @return entier représentant le numero_plateau de la carte.
 */
int get_numero_plateau(carte c);

/**
 * Fonction permettant de recupérer le est_face_cachee de la carte.
 * @param carte : pointeur sur la carte dont on veut récuperer le est_face_cachee.
 * @return booleen représentant le est_face_cachee de la carte.
 */
booleen get_est_face_cachee(carte carte);

/**
 * Fonction permettant de changer le nom de la carte.
 * @param c : pointeur sur la carte dont on veut changer son nom.
 * @param nom : chaîne de caractères que l'on va associer au nom de la carte.
 */
void set_nom_carte(carte c, char *nom);
/**
 * Fonction permettant de changer l'effet de la carte.
 * @param c : pointeur sur la carte dont on veut changer son effet.
 * @param effet : chaîne de caractères que l'on va associer à l'effet de la carte.
 */
void set_effet(carte c,char *effet);

/**
 * Fonction permettant de changer l'identifiant_faction de la carte.
 * @param c : pointeur sur la carte dont on veut changer son identifiant_faction.
 * @param identifiant_faction : entier que l'on va associer à l'identifiant_faction de la carte.
 */
void set_identifiant_faction_carte(carte c, int identifiant_faction);

/**
 * Fonction permettant de changer le numero_plateau de la carte.
 * @param c : pointeur sur la carte dont on veut changer son numero_plateau.
 * @param numero_plateau : entier que l'on va associer à le numero_plateau de la carte.
 */
void set_numero_plateau(carte c, int numero_plateau);

/**
 * Fonction permettant de changer le est_face_cachee de la carte.
 * @param c : pointeur sur la carte dont on veut changer son est_face_cachee.
 * @param est_face_cachee : booleen que l'on va associer à le est_face_cachee de la carte.
 */
void set_est_face_cachee(carte c, booleen est_face_cachee);

#endif //ORIIEFLAMME_GR_11_CARTE_H