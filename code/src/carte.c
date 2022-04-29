#include "../headers/constante.h"

/**
 * Structure représentant une carte.
 */
typedef struct s_carte {
    /**
     * Chaîne de caractère représentant le nom de la carte.
     */
    char *nom;
    /**
     * Chaîne de caractère représentant l'effet de la carte.
     */
    char *effet;
    /**
     * Entier représentant l'identifiant de la faction qui possède la carte.
     */
    int identifiant_faction;
    /**
     * Entier représentant la numéro de la carte sur le plateau.
     * Il sera initialisé à -1 pour signifier que la carte n'est pas présente sur le plateau.
     * (par exemple la première carte aura son champ numero_plateau = 0).
     */
    int numero_plateau;
    /**
     * Booléen représentant l'état de la carte : VRAI = face cachée, FAUX = face visible.
     */
    booleen est_face_cachee;

}*carte;

char *get_nom_carte(carte c) {
    return c->nom;
}

char *get_effet(carte c) {
    return c->effet;
}

int get_identifiant_faction_carte(carte c) {
    return c->identifiant_faction;
}

int get_numero_plateau(carte c) {
    return c->numero_plateau;
}

booleen get_est_face_cachee(carte carte) {
    return carte->est_face_cachee;
}

void set_nom_carte(carte c, char *nom) {
    c->nom = nom;
}

void set_effet(carte c,char *effet) {
    c->effet = effet;
}

void set_identifiant_faction_carte(carte c, int identifiant_faction) {
    c->identifiant_faction = identifiant_faction;
}
void set_numero_plateau(carte c, int numero_plateau) {
    c->numero_plateau = numero_plateau;
}

void set_est_face_cachee(carte c, booleen est_face_cachee) {
    c->est_face_cachee = est_face_cachee;
}