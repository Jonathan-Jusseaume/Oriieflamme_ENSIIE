#include "../headers/carte.h"
#include "../headers/faction.h"
#include "../headers/constante.h"
#include "../headers/position.h"


/**
 * Structure correspondant à notre plateau de jeu
 */
typedef struct s_plateau {

    /**
     * tableau de pointeurs statiques contenant les cartes déposées par les factions
     */
    carte grille[NOMBRE_CARTES_MAXIMUM * 2][NOMBRE_CARTES_MAXIMUM * 2];

    /**
     * tableau de pointeurs contenant un pointeur sur chaque joueur
     */
    faction* factions;

    /**
     * nombre de cartes déposées sur le plateau
     */
    int nombre_cartes_posees;

    /**
    * abscisse de la carte la plus à gauche
    */
    int min_x;

    /**
    * abscisse de la carte la plus à droite
    */
    int max_x;

    /**
     * ordonnée de la carte la plus en haut
     */
    int min_y;

    /**
     *ordonnée de la carte la plus en bas
     */
    int max_y;

    /**
     * champs de la dernière carte retournée. En effet le plateau doit se souvenir de cette dernière carte dans le cas où celle-ci correspond à "Laurent Prevel"
     */
    carte derniere_carte_retournee;


} *plateau;

/**
 * Fonction permettant de recupérer la grille du plateau.
 * @param plateau : pointeur sur le plateau dont on veut récuperer la grille.
 * @return tableau 2D de carte représentant la grille du plateau.
 */
carte **get_grille(plateau plateau) {
    return plateau->grille;
}

/**
 * Fonction permettant de recupérer les factions du plateau.
 * @param plateau : pointeur sur le plateau dont on veut récuperer les factions.
 * @return tableau 1D de faction représentant les factions du plateau.
 */
faction *get_factions(plateau plateau) {
    return plateau->factions;
}

/**
 * Fonction permettant de recupérer le nombre_cartes_posees du plateau.
 * @param plateau : pointeur sur le plateau dont on veut récuperer le nombre_cartes_posees.
 * @return entier représentant le nombre_cartes_posees du plateau.
 */
int get_nombre_cartes_posees(plateau plateau) {
    return plateau->nombre_cartes_posees;
}

/**
 * Fonction permettant de recupérer le min_x du plateau.
 * @param plateau : pointeur sur le plateau dont on veut récuperer le min_x.
 * @return entier représentant le min_x du plateau.
 */
int get_min_x(plateau plateau) {
    return plateau->min_x;
}

/**
 * Fonction permettant de recupérer le max_x du plateau.
 * @param plateau : pointeur sur le plateau dont on veut récuperer le max_x.
 * @return entier représentant le max_x du plateau.
 */
int get_max_x(plateau plateau) {
    return plateau->max_x;
}

/**
 * Fonction permettant de recupérer le min_y du plateau.
 * @param plateau : pointeur sur le plateau dont on veut récuperer le min_y.
 * @return entier représentant le min_y du plateau.
 */
int get_min_y(plateau plateau) {
    return plateau->min_y;
}

/**
 * Fonction permettant de recupérer le max_y du plateau.
 * @param plateau : pointeur sur le plateau dont on veut récuperer le max_y.
 * @return entier représentant le max_y du plateau.
 */
int get_max_y(plateau plateau) {
    return plateau->max_y;
}

/**
 * Fonction permettant de recupérer le max_x du plateau.
 * @param plateau : pointeur sur le plateau dont on veut récuperer le max_x.
 * @return entier représentant le max_x du plateau.
 */
carte get_derniere_carte_retournee(plateau plateau) {
    return plateau->derniere_carte_retournee;
}

/**
 * Fonction permettant de changer la grille du plateau.
 * @param plateau : pointeur sur le plateau dont on veut changer sa grille.
 * @param grille : tableau 2D de carte que l'on va associer à la grille du plateau.
 */
void set_grille(plateau plateau, carte grille[NOMBRE_CARTES_MAXIMUM * 2][NOMBRE_CARTES_MAXIMUM * 2]) {
    for(int i;i<NOMBRE_CARTES_MAXIMUM * 2;i++) {
        for(int j;j<NOMBRE_CARTES_MAXIMUM * 2;j++) {
                plateau->grille[i][j] = grille[i][j];
        }    
    }
}

/**
 * Fonction permettant de changer les factions du plateau.
 * @param plateau : pointeur sur le plateau dont on veut changer ses factions.
 * @param factions : tableau 1D de faction que l'on va associer aux factions du plateau.
 */
void set_factions(plateau plateau,faction *factions) {
    free(plateau->factions);
    plateau->factions = factions;
}

/**
 * Fonction permettant de changer le nombre_cartes_posees du plateau.
 * @param plateau : pointeur sur le plateau dont on veut changer son nombre_cartes_posees.
 * @param nombre_cartes_posees : entier que l'on va associer au nombre_cartes_posees du plateau.
 */
void set_nombre_cartes_posees(plateau plateau, int nombre_cartes_posees) {
    plateau->nombre_cartes_posees = nombre_cartes_posees;
}

/**
 * Fonction permettant de changer le min_x du plateau.
 * @param plateau : pointeur sur le plateau dont on veut changer son min_x.
 * @param min_x : entier que l'on va associer au min_x du plateau.
 */
void set_min_x(plateau plateau, int min_x) {
    plateau->min_x = min_x;
}

/**
 * Fonction permettant de changer le max_x du plateau.
 * @param plateau : pointeur sur le plateau dont on veut changer son max_x.
 * @param max_x : entier que l'on va associer au max_x du plateau.
 */
void set_max_x(plateau plateau, int max_x) {
    plateau->max_x = max_x;
}

/**
 * Fonction permettant de changer le min_y du plateau.
 * @param plateau : pointeur sur le plateau dont on veut changer son min_y.
 * @param min_y : entier que l'on va associer au min_y du plateau.
 */
void set_min_y(plateau plateau, int min_y) {
    plateau->min_y = min_y;
}

/**
 * Fonction permettant de changer le max_y du plateau.
 * @param plateau : pointeur sur le plateau dont on veut changer son max_y.
 * @param max_y : entier que l'on va associer au max_y du plateau.
 */
void set_max_y(plateau plateau, int max_y) {
    plateau->max_y = max_y;
}

/**
 * Fonction permettant de changer la derniere_carte_retournee du plateau.
 * @param plateau : pointeur sur le plateau dont on veut changer sa derniere_carte_retournee.
 * @param derniere_carte_retournee : carte que l'on va associer à la derniere_carte_retournee du plateau.
 */
void set_derniere_carte_retournee(plateau plateau, carte derniere_carte_retournee) {
    plateau->derniere_carte_retournee = derniere_carte_retournee;
}
