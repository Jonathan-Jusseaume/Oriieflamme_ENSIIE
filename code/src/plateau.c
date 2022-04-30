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

grille_carte *get_grille(plateau p) {
    return p->grille;
}

faction *get_factions(plateau p) {
    return p->factions;
}

int get_nombre_cartes_posees(plateau p) {
    return p->nombre_cartes_posees;
}

carte get_derniere_carte_retournee(plateau p) {
    return p->derniere_carte_retournee;
}

void set_grille(plateau p, grille_carte g) {
    p->grille = g;
}

void set_factions(plateau p,faction *factions) {
    free(p->factions);
    p->factions = factions;
}

void set_nombre_cartes_posees(plateau p, int nombre_cartes_posees) {
    p->nombre_cartes_posees = nombre_cartes_posees;
}

void set_derniere_carte_retournee(plateau p, carte derniere_carte_retournee) {
    p->derniere_carte_retournee = derniere_carte_retournee;
}
