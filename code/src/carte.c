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

/**
 * Fonction permettant de recupérer le nom de la carte.
 * @param c : pointeur sur la carte dont on veut récuperer le nom.
 * @return chaîne de caractères représentant le nom de la carte.
 */
char *get_nom_carte(carte c) {
    return c->nom;
}

/**
 * Fonction permettant de recupérer l'effet de la carte.
 * @param c : pointeur sur la carte dont on veut récuperer l'effet.
 * @return chaîne de caractères représentant l'effet de la carte.
 */
char *get_effet(carte c) {
    return c->effet;
}

/**
 * Fonction permettant de recupérer l'identifiant_faction de la carte.
 * @param c : pointeur sur la carte dont on veut récuperer l'identifiant_faction.
 * @return entier représentant l'identifiant_faction de la carte.
 */
int get_identifiant_faction_carte(carte c) {
    return c->identifiant_faction;
}

/**
 * Fonction permettant de recupérer le numero_plateau de la carte.
 * @param c : pointeur sur la carte dont on veut récuperer le numero_plateau.
 * @return entier représentant le numero_plateau de la carte.
 */
int get_numero_plateau(carte c) {
    return c->numero_plateau;
}

/**
 * Fonction permettant de recupérer le est_face_cachee de la carte.
 * @param carte : pointeur sur la carte dont on veut récuperer le est_face_cachee.
 * @return booleen représentant le est_face_cachee de la carte.
 */
booleen get_est_face_cachee(carte carte) {
    return carte->est_face_cachee;
}

/**
 * Fonction permettant de changer le nom de la carte.
 * @param c : pointeur sur la carte dont on veut changer son nom.
 * @param nom : chaîne de caractères que l'on va associer au nom de la carte.
 */
void set_nom_carte(carte c, char *nom) {
    c->nom = nom;
}

/**
 * Fonction permettant de changer l'effet de la carte.
 * @param c : pointeur sur la carte dont on veut changer son effet.
 * @param effet : chaîne de caractères que l'on va associer à l'effet de la carte.
 */
void set_effet(carte c,char *effet) {
    c->effet = effet;
}

/**
 * Fonction permettant de changer l'identifiant_faction de la carte.
 * @param c : pointeur sur la carte dont on veut changer son identifiant_faction.
 * @param identifiant_faction : entier que l'on va associer à l'identifiant_faction de la carte.
 */
void set_identifiant_faction_carte(carte c, int identifiant_faction) {
    c->identifiant_faction = identifiant_faction;
}

/**
 * Fonction permettant de changer le numero_plateau de la carte.
 * @param c : pointeur sur la carte dont on veut changer son numero_plateau.
 * @param numero_plateau : entier que l'on va associer à le numero_plateau de la carte.
 */
void set_numero_plateau(carte c, int numero_plateau) {
    c->numero_plateau = numero_plateau;
}

/**
 * Fonction permettant de changer le est_face_cachee de la carte.
 * @param c : pointeur sur la carte dont on veut changer son est_face_cachee.
 * @param est_face_cachee : booleen que l'on va associer à le est_face_cachee de la carte.
 */
void set_est_face_cachee(carte c, booleen est_face_cachee) {
    c->est_face_cachee = est_face_cachee;
}