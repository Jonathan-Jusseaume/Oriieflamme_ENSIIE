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
     * tableau de pointeurs contenant un pointeur sur chaque faction
     */
    faction *factions;

    /**
     * pointeur vers la grille de cartes : en effet celle-ci s'occupe de la gestion du plateau
     */
    grille_carte grille_c;

    /**
     * nombre de cartes déposées sur le plateau
     */
    int nombre_cartes_posees;

    /**
     * champs de la dernière carte retournée. En effet le plateau doit se souvenir de cette dernière carte dans le cas où celle-ci correspond à "Massinissa Merabet"
     */
    carte derniere_carte_retournee;
    /**
     * champs correspondant au nombre de cartes retournées.
     */
    int nombre_cartes_retournees;

} *plateau;


plateau nouveau_plateau() {
    /*allocation de la mémoire pour notre plateau*/
    plateau p = (plateau) malloc(sizeof(struct s_plateau));
    /*initialisation des factions*/
    p->factions = initialiser_factions();
    p->derniere_carte_retournee = NULL;
    p->nombre_cartes_retournees = 0;
    p->nombre_cartes_posees = 0;
    return p;
}

void liberer_plateau(plateau p) {
    if (p == NULL) {
        return;
    }
    /*libération de la mémoire pour les factions*/
    free(p->factions);
    free(p);
}

int initialiser_manche(plateau p) {
    int manche_gagnee; /* variable qui va contenir le nombre de manches gagnées par le joueur en question*/
    int identifiant_fac_derniere_carte; /*variable qui contiendra l'identifiant de la faction correspondant à la dernière retournée*/

    p->grille_c = initialiser_grille(NOMBRE_CARTES_MAXIMUM * 2);
    /*on vérifie que la dernière carte retournée n'est pas nulle et si la carte retournée est Laurent Prevel : en effet, le joueur qui a déposé cette carte a gagné la manche*/
    if (p->derniere_carte_retournee != NULL &&
        strcmp(get_nom_carte(p->derniere_carte_retournee), nom_cartes[Laurent_Prevel]) == 0) {
        /*identifiant de la faction qui a posé la dernière carte retournée "Laurent Prevel"*/
        identifiant_fac_derniere_carte = get_identifiant_faction_carte(p->derniere_carte_retournee);
        manche_gagnee = get_manches_gagnees(p->factions[identifiant_fac_derniere_carte]);
        /*on incrémente le nombre de manches de la faction qui a déposé la carte "Laurent Prével"*/
        set_manches_gagnees(p->factions[identifiant_fac_derniere_carte], manche_gagnee++);
    } else {
        /*Permet d'incrémenter la manche en fonction du joueur gagnant*/
        /*si le joueur 1 a gagné la manche grâce à son nombre de points*/
        if (get_points_DDRS(p->factions[FACTION1]) > get_points_DDRS(p->factions[FACTION2])) {
            /*on incrémente le nombre de manches pour le joueur 1*/
            manche_gagnee = get_manches_gagnees(p->factions[1]);
            set_manches_gagnees(p->factions[FACTION1], manche_gagnee++);
            /*si le joueur 2 a gagné la manche grâce à son nombre de points*/
        } else if (get_points_DDRS(p->factions[FACTION1]) < get_points_DDRS(p->factions[FACTION2])) {
            /*on incrémente le nombre de manches pour le joueur 2*/
            manche_gagnee = get_manches_gagnees(p->factions[FACTION2]);
            set_manches_gagnees(p->factions[FACTION2], manche_gagnee++);
            /* sinon si les deux joueurs ont le même nombre de points : le joueur qui a la carte la plus en haut à gauche a gagné*/
        } else {
            int identifiant_fac_carte_plus_a_gauche;
            for (int i = get_min_x_grille(p->grille_c); i < get_max_x_grille(p->grille_c); i++) {
                if (get_grille(p->grille_c)[get_min_y_grille(p->grille_c)][i] != NULL) {
                    /*récupération de l'identifiant de la faction qui posé la carte la plus en haut à gauche*/
                    identifiant_fac_carte_plus_a_gauche = get_identifiant_faction_carte(
                            get_grille(p->grille_c)[get_min_y_grille(p->grille_c)][i]);
                    manche_gagnee = get_manches_gagnees(p->factions[identifiant_fac_carte_plus_a_gauche]);
                    set_manches_gagnees(p->factions[identifiant_fac_carte_plus_a_gauche], manche_gagnee++);
                }
            }
        }
    }
    /*Permet de savoir le joueur gagnant de la partie en fonction de son nombre de manches gagnées.*/
    if (get_manches_gagnees(p->factions[FACTION1]) == 2) {
        /*Le joueur 1 a gagné*/
        return 0;
    } else if (get_manches_gagnees(p->factions[FACTION2]) == 2) {
        /*Le joueur 2 a gagné*/
        return 1;
    }
    /*Sinon la partie n'est pas terminée : initialisation de la grille et de ses différents champs : min_x/max_x/min_y/max_y*/
    reinitialiser_grille(p->grille_c);
    return -1;
}

faction *get_factions(plateau p) {
    /*retourne les factions*/
    return p->factions;
}

void poser_carte(plateau p, carte c, position pos) {
    set_position(c, pos.absisse, pos.ordonnee);
    poser_carte_grille(p->grille_c, c, pos.ordonnee, pos.abscisse);
    p->nombre_cartes_posees++;
}

carte retourner_carte(plateau p) {
    position pos = get_position_carte_haut_gauche_grille(p->grille_c);
    /*si abscisse vaut -1 : les cartes ont été toutes retournées*/
    if (pos.abscisse == -1) {
        return NULL;
    }
    /*sinon, on récupère la carte en question et on la retourne en activant son effet*/
    carte carte = get_carte_grille(p->grille_c, pos.ordonnee, pos.abscisse);
    /*on modifie le booléan associé afin que la carte devienne visible*/
    set_est_face_cachee(carte, FAUX);

    /*on augmente de 1 le nombre de cartes retournées*/
    p->nombre_cartes_retournees++;

    /*on applique l'effet de la carte : on récupère la fonction associée à la carte*/
    get_active_effet_carte(carte, p);
    /*mise à jour de la dernière carte retournée*/
    p->derniere_carte_retournee = carte;

    return carte;
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
 * Fonction permettant de recupérer le min_x du plateau.
 * @param p : pointeur sur le plateau dont on veut récuperer le min_x.
 * @return entier représentant le min_x du plateau.
 */
int get_min_x(plateau p) {
    return p->min_x;
}

/**
 * Fonction permettant de recupérer le max_x du plateau.
 * @param p : pointeur sur le plateau dont on veut récuperer le max_x.
 * @return entier représentant le max_x du plateau.
 */
int get_max_x(plateau p) {
    return p->max_x;
}

/**
 * Fonction permettant de recupérer le min_y du plateau.
 * @param p : pointeur sur le plateau dont on veut récuperer le min_y.
 * @return entier représentant le min_y du plateau.
 */
int get_min_y(plateau p) {
    return p->min_y;
}

/**
 * Fonction permettant de recupérer le max_y du plateau.
 * @param p : pointeur sur le plateau dont on veut récuperer le max_y.
 * @return entier représentant le max_y du plateau.
 */
int get_max_y(plateau p) {
    return p->max_y;
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
void set_grille(plateau p, carte grille[NOMBRE_CARTES_MAXIMUM * 2][NOMBRE_CARTES_MAXIMUM * 2]) {
    for (int i; i < NOMBRE_CARTES_MAXIMUM * 2; i++) {
        for (int j; j < NOMBRE_CARTES_MAXIMUM * 2; j++) {
            p->grille[i][j] = grille[i][j];
        }
    }
}

/**
 * Fonction permettant de changer les factions du plateau.
 * @param p : pointeur sur le plateau dont on veut changer ses factions.
 * @param factions : tableau 1D de faction que l'on va associer aux factions du plateau.
 */
void set_factions(plateau p, faction *factions) {
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
 * Fonction permettant de changer le min_x du plateau.
 * @param p : pointeur sur le plateau dont on veut changer son min_x.
 * @param min_x : entier que l'on va associer au min_x du plateau.
 */
void set_min_x(plateau p, int min_x) {
    p->min_x = min_x;
}

/**
 * Fonction permettant de changer le max_x du plateau.
 * @param p : pointeur sur le plateau dont on veut changer son max_x.
 * @param max_x : entier que l'on va associer au max_x du plateau.
 */
void set_max_x(plateau p, int max_x) {
    p->max_x = max_x;
}

/**
 * Fonction permettant de changer le min_y du plateau.
 * @param p : pointeur sur le plateau dont on veut changer son min_y.
 * @param min_y : entier que l'on va associer au min_y du plateau.
 */
void set_min_y(plateau p, int min_y) {
    p->min_y = min_y;
}

/**
 * Fonction permettant de changer le max_y du plateau.
 * @param p : pointeur sur le plateau dont on veut changer son max_y.
 * @param max_y : entier que l'on va associer au max_y du plateau.
 */
void set_max_y(plateau p, int max_y) {
    p->max_y = max_y;
}

/**
 * Fonction permettant de changer la derniere_carte_retournee du plateau.
 * @param p : pointeur sur le plateau dont on veut changer sa derniere_carte_retournee.
 * @param derniere_carte_retournee : carte que l'on va associer à la derniere_carte_retournee du plateau.
 */
void set_derniere_carte_retournee(plateau p, carte derniere_carte_retournee) {
    p->derniere_carte_retournee = derniere_carte_retournee;
}
