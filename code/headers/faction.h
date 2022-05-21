/**
 * @file faction.h
 * @brief Fichier contenant la structure et les fonctions liées aux factions
 */
#ifndef ORIIEFLAMME_GR_11_FACTION_H
#define ORIIEFLAMME_GR_11_FACTION_H

#include "constante.h"
#include "carte.h"
#include "structure.h"
#include <stdlib.h>


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

/**
 * Fonction permettant de recupérer le nom de la faction.
 * @param f : pointeur sur la faction dont on veut récuperer le nom.
 * @return chaîne de caractères représentant le nom de la faction.
 */
char *get_nom_faction(faction f);

/**
 * Fonction permettant de recupérer l'identifiant_faction de la faction.
 * @param f : pointeur sur la faction dont on veut récuperer l'identifiant_faction.
 * @return entier représentant l'identifiant_faction de la faction.
 */
int get_identifiant_faction(faction f);

/**
 * Fonction permettant de recupérer les points_DDRS de la faction.
 * @param f : pointeur sur la faction dont on veut récuperer les points_DDRS.
 * @return entier représentant les points_DDRS de la faction.
 */
int get_points_DDRS(faction f);

/**
 * Fonction permettant de recupérer les manches_gagnees de la faction.
 * @param f : pointeur sur la faction dont on veut récuperer les manches_gagnees.
 * @return entier représentant les manches_gagnees de la faction.
 */
int get_manches_gagnees(faction f);

/**
 * Fonction permettant de recupérer le a_remelanger de la faction.
 * @param f : pointeur sur la faction dont on veut récuperer le a_remelanger.
 * @return booleen représentant le a_remelanger de la faction.
 */
booleen get_a_remelanger(faction f);

/**
 * Fonction permettant de recupérer la pioche de la faction.
 * @param f : pointeur sur la faction dont on veut récuperer la pioche.
 * @return Set de carte représentant la pioche de la faction.
 */
ensemble_entier get_pioche(faction f);

/**
 * Fonction permettant de recupérer la main de la faction.
 * @param f : pointeur sur la faction dont on veut récuperer la main.
 * @return liste chainee de carte représentant la main de la faction.
 */
liste_chainee_carte get_main(faction f);

/**
 * Fonction permettant de changer le nom de la faction.
 * @param f : pointeur sur la faction dont on veut changer son nom.
 * @param nom : chaîne de caractères que l'on va associer au nom de la faction.
 */
void set_nom_faction(faction f, char *nom);

/**
 * Fonction permettant de changer l'identifiant_faction de la faction.
 * @param f : pointeur sur la faction dont on veut changer son identifiant_faction.
 * @param identifiant_faction : entier que l'on va associer à l'identifiant_faction de la faction.
 */
void set_identifiant_faction(faction f, int identifiant_faction);

/**
 * Fonction permettant de changer les points_DDRS de la faction.
 * @param f : pointeur sur la faction dont on veut changer ses points_DDRS.
 * @param points_DDRS : entier que l'on va associer à les points_DDRS de la faction.
 */
void set_points_DDRS(faction f, int points_DDRS);

/**
 * Fonction permettant de changer les manches_gagnees de la faction.
 * @param f : pointeur sur la faction dont on veut changer ses manches_gagnees.
 * @param manches_gagnees : entier que l'on va associer à les manches_gagnees de la faction.
 */
void set_manches_gagnees(faction f, int manches_gagnees);

/**
 * Fonction permettant de changer le a_remelanger de la faction.
 * @param f : pointeur sur la faction dont on veut changer son a_remelanger.
 * @param a_remelanger : entier que l'on va associer à le a_remelanger de la faction.
 */
void set_a_remelanger(faction f, booleen a_remelanger);
/**
 * Fonction permettant de changer la pioche de la faction.
 * @param f : pointeur sur la faction dont on veut changer sa pioche.
 * @param pioche : Set que l'on va associer à la pioche de la faction.
 */
void set_pioche(faction f, ensemble_entier pioche);

/**
 * Fonction permettant de changer la main de la faction.
 * @param f : pointeur sur la faction dont on veut changer sa main.
 * @param main : liste chainee que l'on va associer à la main de la faction.
 */
void set_main(faction f, liste_chainee_carte main);

/**
 * Renvoie la faction passée en paramètre sous forme de chaîne de caractères
 * @param f la faction dont on veut obtenir les informations
 * @return la chaîne sous la forme: "identifiant_faction|nom|a_remelanger|points_DDRS|manches_gagnees_main"
 */
char* faction_to_string(faction f);

#endif //ORIIEFLAMME_GR_11_FACTION_H