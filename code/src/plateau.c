#include "../headers/carte.h"
#include "../headers/faction.h"
#include "../headers/constante.h"
#include "../headers/position.h"
#include "../headers/structure.h"


/**
 * Structure correspondant à notre plateau de jeu
 */
typedef struct s_plateau {

    /**
     * tableau de pointeurs statiques contenant les cartes déposées par les factions
     */
    grille_carte grille;

    /**
     * tableau de pointeurs contenant un pointeur sur chaque joueur
     */
    faction* factions;

    /**
     * nombre de cartes déposées sur le plateau
     */
    int nombre_cartes_posees;

    /**
     * champs de la dernière carte retournée. En effet le plateau doit se souvenir de cette dernière carte dans le cas où celle-ci correspond à "Laurent Prevel"
     */
    carte derniere_carte_retournee;


} *plateau;

/**
 * Fonction permettant de recupérer la grille du plateau.
 * @param p : pointeur sur le plateau dont on veut récuperer la grille.
 * @return tableau 2D de carte représentant la grille du plateau.
 */
grille_carte *get_grille(plateau p) {
    return p->grille;
}

/**
 * Fonction permettant de recupérer les factions du plateau.
 * @param p : pointeur sur le plateau dont on veut récuperer les factions.
 * @return tableau 1D de faction représentant les factions du plateau.
 */
faction *get_factions(plateau p) {
    return p->factions;
}

/**
 * Fonction permettant de recupérer le nombre_cartes_posees du plateau.
 * @param p : pointeur sur le plateau dont on veut récuperer le nombre_cartes_posees.
 * @return entier représentant le nombre_cartes_posees du plateau.
 */
int get_nombre_cartes_posees(plateau p) {
    return p->nombre_cartes_posees;
}

/**
 * Fonction permettant de recupérer le max_x du plateau.
 * @param p : pointeur sur le plateau dont on veut récuperer le max_x.
 * @return entier représentant le max_x du plateau.
 */
carte get_derniere_carte_retournee(plateau p) {
    return p->derniere_carte_retournee;
}

/**
 * Fonction permettant de changer la grille du plateau.
 * @param p : pointeur sur le plateau dont on veut changer sa grille.
 * @param grille : tableau 2D de carte que l'on va associer à la grille du plateau.
 */
void set_grille(plateau p, grille_carte g) {
    p->grille = g;
}

/**
 * Fonction permettant de changer les factions du plateau.
 * @param p : pointeur sur le plateau dont on veut changer ses factions.
 * @param factions : tableau 1D de faction que l'on va associer aux factions du plateau.
 */
void set_factions(plateau p,faction *factions) {
    free(p->factions);
    p->factions = factions;
}

/**
 * Fonction permettant de changer le nombre_cartes_posees du plateau.
 * @param p : pointeur sur le plateau dont on veut changer son nombre_cartes_posees.
 * @param nombre_cartes_posees : entier que l'on va associer au nombre_cartes_posees du plateau.
 */
void set_nombre_cartes_posees(plateau p, int nombre_cartes_posees) {
    p->nombre_cartes_posees = nombre_cartes_posees;
}

/**
 * Fonction permettant de changer la derniere_carte_retournee du plateau.
 * @param p : pointeur sur le plateau dont on veut changer sa derniere_carte_retournee.
 * @param derniere_carte_retournee : carte que l'on va associer à la derniere_carte_retournee du plateau.
 */
void set_derniere_carte_retournee(plateau p, carte derniere_carte_retournee) {
    p->derniere_carte_retournee = derniere_carte_retournee;
}
