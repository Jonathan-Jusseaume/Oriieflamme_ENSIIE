#include "../headers/constante.h"
#include "../headers/position.h"
#include "../headers/carte.h"
#include <stdlib.h>
#include <stdio.h>

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
     * Pointeur vers une fonction contenant l'effet de la carte
     */
    void (*effet_fonction)(carte c, plateau p);

    /**
     * Position de la carte
     */
    position pos;

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

} *carte;

carte initialiser_carte(char *nom, char *effet, void *effet_carte, int identifiant_faction, int numero_plateau,
                        booleen est_face_cachee) {
    /*initialisation de la carte avec les différents champs requis*/
    carte c = (carte) malloc(sizeof(struct s_carte));
    c->nom = nom;
    c->effet = effet;
    c->effet_fonction = effet_carte;
    c->pos.abscisse = -1;
    c->pos.ordonnee = -1;
    c->identifiant_faction = identifiant_faction;
    c->numero_plateau = numero_plateau;
    c->est_face_cachee = est_face_cachee;
    return c;
}

char *to_string_carte(carte c) {
    size_t taille = 0;
    char *str_pos = position_to_string(c->pos);
    // On fait un snprintf afin de déterminer la taille à réserver, on met donc volontaire aucune destination et pour ignorer le warning -Wformat-truncation, on rajoute une macro
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wformat-truncation"
    taille = snprintf(NULL, taille, "%s,%s,%d,%d,%d",
                      c->nom,
                      str_pos,
                      c->identifiant_faction,
                      c->numero_plateau,
                      c->est_face_cachee);
    #pragma GCC diagnostic pop

    char *str = (char *) malloc((taille + 2) * sizeof(char));
    snprintf(str, taille + 2, "%s,%s,%d,%d,%d",
             c->nom,
             str_pos,
             c->identifiant_faction,
             c->numero_plateau,
             c->est_face_cachee);
    free(str_pos);
    return str;
}


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

position get_position(carte c) {
    return c->pos;
}

void (*get_effet_fonction(carte c))(carte c, plateau p) {
    return c->effet_fonction;
}

void set_nom_carte(carte c, char *nom) {
    c->nom = nom;
}

void set_position(carte c, position p) {
    c->pos = p;
}

void set_effet(carte c, char *effet) {
    c->effet = effet;
}

void set_identifiant_faction_carte(carte c, int identifiant_faction) {
    c->identifiant_faction = identifiant_faction;
}

void set_effet_fonction_carte(carte c, void *effet_fonction) {
    c->effet_fonction = effet_fonction;
}

void set_numero_plateau(carte c, int numero_plateau) {
    c->numero_plateau = numero_plateau;
}

void set_est_face_cachee(carte c, booleen est_face_cachee) {
    c->est_face_cachee = est_face_cachee;
}

