/**
 * @file faction.h
 * @brief Fichier contenant la structure et les fonctions liées aux factions
 */
#ifndef ORIIEFLAMME_GR_11_FACTION_H
#define ORIIEFLAMME_GR_11_FACTION_H

#include "constante.h"
#include "carte.h"

/**
 * Structure représentant une faction.
 */
typedef struct s_faction
{
    /**
     * Chaîne de caractère représentant le nom de la faction.
     */
    char *nom;
    /**
     * Entier représentant l'identifiant de la faction.
     */
    int identifiant_faction;
    /**
     * Entier représentant les points DDRS de la faction.
     */
    int points_DDRS;
    /**
     * Entier représentant les manches gagnées par la faction.
     */
    int manches_gagnees;
    /**
     * Pointeur vers des cartes représentant les cartes dans la pioche de la faction.
     */
    carte *pioche;
    /**
     * Pointeur vers des cartes représentant les cartes dans la main de la faction.
     */
    carte *main;
} *faction;

/**
 * Fonction permettant de savoir si une faction a utilisé l'option de remélanger sa main et la boîte à idée et de repiocher des cartes.
 * @param faction : pointeur sur la faction qui veux faire l'action.
 * @return un booleen indiquant si la faction à remélanger sa main (VRAI) ou non (FALSE).
 */
booleen a_remelanger(faction f);

/**
 * Fonction permettant à une faction d'utiliser l'option de remélanger sa main et la boîte à idée et de repiocher des cartes. 
 * @param f : pointeur sur la faction qui veux faire l'action.
 */
void remelanger(faction f);

/**
 * Fonction permettant à une faction de vider sa main dans sa pioche. 
 * @param f : pointeur sur la faction qui veux faire l'action.
 */
void vider_main_dans_pioche(faction f);

/**
 * Fonction permettant à une faction de mélanger sa pioche. 
 * @param f : pointeur sur la faction qui veux faire l'action.
 */
void melanger_pioche(faction f);

/**
 * Fonction permettant à une faction de repiocher ses cartes. 
 * @param faction : pointeur sur la faction qui veux faire l'action.
 */
void repioche(faction f);


#endif //ORIIEFLAMME_GR_11_FACTION_H