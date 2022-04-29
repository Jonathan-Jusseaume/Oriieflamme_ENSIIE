/**
 * @file faction.h
 * @brief Fichier contenant la structure et les fonctions liées aux factions
 */
#ifndef ORIIEFLAMME_GR_11_FACTION_H
#define ORIIEFLAMME_GR_11_FACTION_H

#include "constante.h"
#include "carte.h"
#include "structure.h"
#include<stdlib.h>


/**
 * Structure représentant une faction.
 */
typedef struct s_faction *faction;

/**
 * Fonction permettant d'initialiser les deux factions
 * @return faction* : pointeur sur les factions
 */
faction *initialiser_factions();

/**
 * Fonction permettant de savoir si une faction a utilisé l'option de remélanger sa main et la boîte à idée et de repiocher des cartes.
 * @param faction : pointeur sur la faction qui veux faire l'action.
 * @return un booleen indiquant si la faction à remélanger sa main (VRAI) ou non (FALSE).
 */
booleen a_remelanger(faction f);

/**
 * Fonction qui permet d'indiquer que la faction passée en paramètre à décider de remelanger sa main
 * @param f : pointeur sur la faction qui a remelangé sa main
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