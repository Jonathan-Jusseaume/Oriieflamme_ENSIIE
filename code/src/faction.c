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
     * Pointeur vers un Set représentant les cartes dans la pioche de la faction.
     */
    ensemble_entier pioche;
    /**
     * Pointeur vers une liste chainée représentant les cartes dans la main de la faction.
     */
    liste_chainee_carte main;
} *faction;

char *get_nom_faction(faction f) {
    return f->nom;
}

int get_identifiant_faction(faction f) {
    return f->identifiant_faction;
}

int get_points_DDRS(faction f) {
    return f->points_DDRS;
}

int get_manches_gagnees(faction f) {
    return f->manches_gagnees;
}

booleen get_a_remelanger(faction f) {
    return f->a_remelanger;
}

ensemble_entier get_pioche(faction f) {
    return f->pioche;
}

liste_chainee_carte get_main(faction f) {
    return f->main;
}

void set_nom_faction(faction f, char *nom) {
    f->nom = nom;
}

void set_identifiant_faction(faction f, int identifiant_faction) {
    f->identifiant_faction = identifiant_faction;
}

void set_points_DDRS(faction f, int points_DDRS) {
    f->points_DDRS = points_DDRS;
}

void set_manches_gagnees(faction f, int manches_gagnees) {
    f->manches_gagnees = manches_gagnees;
}

void set_a_remelanger(faction f, char *a_remelanger) {
    f->a_remelanger = a_remelanger;
}

void set_pioche(faction f, ensemble_entier pioche) {
    f->pioche = pioche;
}

void set_main(faction f, liste_chainee_carte main) {
    f->main = main;
}