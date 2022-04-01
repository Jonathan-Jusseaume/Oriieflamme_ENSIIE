#include "../headers/constante.h"
#include "../headers/carte.h"

/**
 * Structure représentant une faction.
 */
typedef struct s_faction {
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
     *  Booléen qui vaut VRAI si la faction a déjà remélangé sa main, et FAUX sinon. 
     */
    booleen a_remelanger;
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
 * Fonction permettant de recupérer le nom de la faction.
 * @param faction : pointeur sur la faction dont on veut récuperer le nom.
 * @return chaîne de caractères représentant le nom de la faction.
 */
char *get_nom(faction faction) {
    return faction->nom;
}

/**
 * Fonction permettant de recupérer l'identifiant_faction de la faction.
 * @param faction : pointeur sur la faction dont on veut récuperer l'identifiant_faction.
 * @return entier représentant l'identifiant_faction de la faction.
 */
int get_identifiant_faction(faction faction) {
    return faction->identifiant_faction;
}

/**
 * Fonction permettant de recupérer les points_DDRS de la faction.
 * @param faction : pointeur sur la faction dont on veut récuperer les points_DDRS.
 * @return entier représentant les points_DDRS de la faction.
 */
int get_points_DDRS(faction faction) {
    return faction->points_DDRS;
}

/**
 * Fonction permettant de recupérer les manches_gagnees de la faction.
 * @param faction : pointeur sur la faction dont on veut récuperer les manches_gagnees.
 * @return entier représentant les manches_gagnees de la faction.
 */
int get_manches_gagnees(faction faction) {
    return faction->manches_gagnees;
}

/**
 * Fonction permettant de recupérer le a_remelanger de la faction.
 * @param faction : pointeur sur la faction dont on veut récuperer le a_remelanger.
 * @return booleen représentant le a_remelanger de la faction.
 */
booleen get_a_remelanger(faction faction) {
    return faction->a_remelanger;
}

/**
 * Fonction permettant de recupérer la pioche de la faction.
 * @param faction : pointeur sur la faction dont on veut récuperer la pioche.
 * @return tableau 1D de carte représentant la pioche de la faction.
 */
carte *get_pioche(faction faction) {
    return faction->pioche;
}

/**
 * Fonction permettant de recupérer la main de la faction.
 * @param faction : pointeur sur la faction dont on veut récuperer la main.
 * @return tableau 1D de carte représentant la main de la faction.
 */
carte *get_main(faction faction) {
    return faction->main;
}

/**
 * Fonction permettant de changer le nom de la faction.
 * @param faction : pointeur sur la faction dont on veut changer son nom.
 * @param nom : chaîne de caractères que l'on va associer au nom de la faction.
 */
void set_nom(faction faction, char *nom) {
    faction->nom = nom;
}

/**
 * Fonction permettant de changer l'identifiant_faction de la faction.
 * @param faction : pointeur sur la faction dont on veut changer son identifiant_faction.
 * @param identifiant_faction : entier que l'on va associer à l'identifiant_faction de la faction.
 */
void set_identifiant_faction(faction faction, int identifiant_faction) {
    faction->identifiant_faction = identifiant_faction;
}

/**
 * Fonction permettant de changer les points_DDRS de la faction.
 * @param faction : pointeur sur la faction dont on veut changer ses points_DDRS.
 * @param points_DDRS : entier que l'on va associer à les points_DDRS de la faction.
 */
void set_points_DDRS(faction faction, int points_DDRS) {
    faction->points_DDRS = points_DDRS;
}

/**
 * Fonction permettant de changer les manches_gagnees de la faction.
 * @param faction : pointeur sur la faction dont on veut changer ses manches_gagnees.
 * @param manches_gagnees : entier que l'on va associer à les manches_gagnees de la faction.
 */
void set_manches_gagnees(faction faction, int manches_gagnees) {
    faction->manches_gagnees = manches_gagnees;
}

/**
 * Fonction permettant de changer le a_remelanger de la faction.
 * @param faction : pointeur sur la faction dont on veut changer son a_remelanger.
 * @param a_remelanger : entier que l'on va associer à le a_remelanger de la faction.
 */
void set_a_remelanger(faction faction, char *a_remelanger) {
    faction->a_remelanger = a_remelanger;
}

/**
 * Fonction permettant de changer la pioche de la faction.
 * @param faction : pointeur sur la faction dont on veut changer sa pioche.
 * @param pioche : entier que l'on va associer à la pioche de la faction.
 */
void set_pioche(faction faction, char *pioche) {
    faction->pioche = pioche;
}

/**
 * Fonction permettant de changer la main de la faction.
 * @param faction : pointeur sur la faction dont on veut changer sa main.
 * @param main : entier que l'on va associer à la main de la faction.
 */
void set_main(faction faction, char *main) {
    faction->main = main;
}