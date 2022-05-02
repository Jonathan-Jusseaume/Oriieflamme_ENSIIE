
#include "../headers/structure.h"
#include <stdlib.h>
#include <stdio.h>

struct s_grille_carte {
    /**
     * Tableau 2D de pointeurs contenant les cartes déposées par les factions
     * S'il n'y pas de cartes sur la case, alors le pointeur vaut NULL
     */
    carte **grille;

    /**
     * Les dimensions de notre grille
     */
    int taille;

    /**
     * Abscisse de la carte la plus à gauche
     */
    int min_x;

    /**
    * Abscisse de la carte la plus à droite
    */
    int max_x;

    /**
     * Ordonnée de la carte la plus en haut
     */
    int min_y;

    /**
     * Ordonnée de la carte la plus en bas du tableau
     */
    int max_y;
};


grille_carte initialiser_grille(int taille_grille) {
    // On alloue la mémoire à notre grille
    grille_carte g = (grille_carte) malloc(1 * sizeof(struct s_grille_carte));
    // On lui donne la taille passée en paramètre
    g->taille = taille_grille;
    /*
     * Par défaut on met le min/max à taille_grille - 1 pour le min et 0 pour le max
     * ainsi quand on pose une carte, les min et max seront immédiatement changés
     * pour correspondre à la position de la carte
     */
    g->min_x = g->taille - 1;
    g->max_x = 0;
    g->min_y = g->taille - 1;
    g->max_y = 0;
    /*
     * On alloue la mémoire pour notre tableau 2D
     * D'abord la mémoire des lignes
     */
    g->grille = (carte **) malloc(taille_grille * sizeof(carte *));
    // Puis la mémoire des colonnes
    for (int i = 0; i < g->taille; i++) {
        g->grille[i] = (carte *) malloc(taille_grille * sizeof(carte));
    }
    for (int i = 0; i < g->taille; i++) {
        for (int j = 0; j < g->taille; j++) {
            g->grille[i][j] = NULL;
        }
    }
    return g;
}

void reinitialiser_grille(grille_carte g) {
    // On parcourt la partie de la grille où il y a des cartes
    for (int y = 0; y < g->taille; y++) {
        for (int x = 0; x < g->taille; x++) {
            // S'il y a une carte sur cette position
            if (g->grille[y][x] != NULL) {
                carte carte_a_liberer = g->grille[y][x];
                g->grille[y][x] = NULL;
                free(carte_a_liberer);
            }
        }
    }
    // On remet les valeurs min et max
    g->min_x = g->taille - 1;
    g->max_x = 0;
    g->min_y = g->taille - 1;
    g->max_y = 0;
}

void liberer_grille(grille_carte g) {
    // On libère la grille
    reinitialiser_grille(g);
    for (int i = 0; i < g->taille; i++) {
        free(g->grille[i]);
    }
    free(g->grille);
    free(g);
}

booleen poser_carte_grille(grille_carte g, carte c, int y, int x) {
    // On vérifie qu'on peut poser cette carte
    if (y < 0 || y >= g->taille || x < 0 || x >= g->taille) {
        return FAUX;
    }
    g->grille[y][x] = c;
    // On met à jour le max_y si c'est nécessaire
    if (y > g->max_y) {
        g->max_y = y;
    }
    // On met à jour le min_y si c'est nécessaire
    if (y < g->min_y) {
        g->min_y = y;
    }
    // On met à jour le max_x si c'est nécessaire
    if (x > g->max_x) {
        g->max_x = x;
    }
    // On met à jour le min_x si c'est nécessaire
    if (x < g->min_x) {
        g->min_x = x;
    }
    return VRAI;
}

carte get_carte_grille(grille_carte g, int y, int x) {
    // On vérifie que les coordonnées sont bonnes
    if (y < 0 || y >= g->taille || x < 0 || x >= g->taille) {
        return NULL;
    }
    return g->grille[y][x];
}

carte supprimer_carte_grille(grille_carte g, int y, int x) {
    // On vérifie qu'on peut supprimer cette carte
    if (y < 0 || y >= g->taille || x < 0 || x >= g->taille) {
        return NULL;
    }
    carte c_supprimee = g->grille[y][x];

    g->grille[y][x] = NULL;
    // On met à jour les min et max dans le cas où on a supprimé une carte qui était sur le max ou le min
    if (c_supprimee != NULL && (y == g->max_y || y == g->min_y || x == g->max_x || x == g->min_x)) {

        // On cherche les nouveaux maximum et minimum et les initialisant aux valeurs les plus grands ou plus petites possibles d'abord
        int new_min_x = g->taille - 1, new_max_x = 0, new_min_y = g->taille - 1, new_max_y = 0;
        for (int y = g->min_y; y <= g->max_y; y++) {
            for (int x = g->min_x; x <= g->max_x; x++) {
                // Si on trouve une carte, on teste si on peut changer les minimum/maximum
                if (g->grille[y][x] != NULL) {
                    if (y > new_max_y) {
                        new_max_y = y;
                    }
                    if (y < new_min_y) {
                        new_min_y = y;
                    }
                    if (x > new_max_x) {
                        new_max_x = x;
                    }
                    if (x < new_min_x) {
                        new_min_x = x;
                    }
                }
            }
        }
        g->max_y = new_max_y;
        g->min_y = new_min_y;
        g->max_x = new_max_x;
        g->min_x = new_min_x;
    }
    return c_supprimee;
}

int get_min_x_grille(grille_carte g) {
    return g->min_x;
}

int get_max_x_grille(grille_carte g) {
    return g->max_x;
}

int get_min_y_grille(grille_carte g) {
    return g->min_y;
}

int get_max_y_grille(grille_carte g) {
    return g->max_y;
}

int get_taille_grille(grille_carte g) {
    return g->taille;
}

position get_position_carte_haut_gauche_grille(grille_carte g, booleen veut_face_cachee) {
    // On initialise une valeur par défaut pour la position que l'on va retourner
    position p = {-1, -1};
    for (int y = g->min_y; y <= g->max_y; y++) {
        for (int x = g->min_x; x <= g->max_x; x++) {
            // Si on trouve une carte face cachée alors on retourne sa position
            if (g->grille[y][x] != NULL && (!veut_face_cachee || get_est_face_cachee(g->grille[y][x]) == VRAI)) {
                p.abscisse = x;
                p.ordonnee = y;
                return p;
            }
        }
    }
    return p;
}


struct s_liste_chainee_carte {
    carte tete;
    liste_chainee_carte queue;
};

liste_chainee_carte initialiser_liste_chainee() {
    return NULL;
}

void ajouter_tete_liste_chainee(liste_chainee_carte *l, carte c) {
    liste_chainee_carte nouvelle_liste = (liste_chainee_carte) malloc(1 * sizeof(struct s_liste_chainee_carte));
    nouvelle_liste->tete = c;
    nouvelle_liste->queue = *l;
    *l = nouvelle_liste;
}

carte supprimer_carte_liste_chainee(liste_chainee_carte *l, int indice_carte) {
    carte c_supprimee = NULL;
    if (liste_chainee_est_vide(*l)) {
        return NULL;
    }
    liste_chainee_carte courant = *l;
    if (indice_carte == 0) {
        c_supprimee = courant->tete;
        (*l) = courant->queue;
        free(courant);
        return c_supprimee;
    }
    liste_chainee_carte precedent = *l;
    int i = 0;
    while (courant != NULL && i != indice_carte) {
        precedent = courant;
        courant = courant->queue;
        i++;
    }
    if (courant == NULL) {
        return NULL;
    }
    c_supprimee = courant->tete;
    precedent->queue = courant->queue;
    free(courant);
    return c_supprimee;

}


carte get_carte_liste_chainee(liste_chainee_carte l, int indice_carte) {
    liste_chainee_carte courant = l;
    int parcours_indice = 0;
    while (!liste_chainee_est_vide(courant) && indice_carte != parcours_indice) {
        courant = courant->queue;
        parcours_indice++;
    }
    return !liste_chainee_est_vide(courant) ? courant->tete : NULL;
}

int taille_liste_chainee(liste_chainee_carte l) {
    liste_chainee_carte courant = l;
    int taille = 0;
    while (!liste_chainee_est_vide(courant)) {
        courant = courant->queue;
        taille++;
    }
    return taille;
}

booleen liste_chainee_est_vide(liste_chainee_carte l) {
    return l == NULL;
}

carte get_valeur_tete_liste_chainee(liste_chainee_carte l) {
    if (liste_chainee_est_vide(l)) {
        return NULL;
    }
    return l->tete;
}

liste_chainee_carte get_queue_liste_chainee(liste_chainee_carte l) {
    if (liste_chainee_est_vide(l)) {
        return NULL;
    }
    return l->queue;
}

void liberer_liste_chainee(liste_chainee_carte l) {
    if (l == NULL) {
        return;
    }
    liberer_liste_chainee(l->queue);
    free(l->tete);
    free(l);
}

struct s_ensemble_entier {
    int *tableau;
    int taille;
};

ensemble_entier creer_ensemble_entier() {
    ensemble_entier nouvel_ensemble = (ensemble_entier) malloc(1 * sizeof(struct s_ensemble_entier));
    nouvel_ensemble->taille = 0;
    nouvel_ensemble->tableau = (int *) malloc(nouvel_ensemble->taille * sizeof(int));
    return nouvel_ensemble;
}

booleen ajouter_ensemble_entier(ensemble_entier ee, int valeur) {
    if (contient_ensemble_entier(ee, valeur)) {
        return FAUX;
    }
    ee->taille = ee->taille + 1;
    ee->tableau = (int *) realloc(ee->tableau, ee->taille * sizeof(int));
    ee->tableau[ee->taille - 1] = valeur;
    return VRAI;
}

booleen contient_ensemble_entier(ensemble_entier ee, int valeur) {
    booleen contient = FAUX;
    for (int i = 0; i < ee->taille; i++) {
        if (ee->tableau[i] == valeur) {
            contient = VRAI;
            break;
        }
    }
    return contient;
}

int get_valeur_indice_ensemble_entier(ensemble_entier ee, int indice) {
    if (indice >= ee->taille) {
        return -1;
    }
    return ee->tableau[indice];
}

int get_taille_ensemble_entier(ensemble_entier ee) {
    return ee->taille;
}

void liberer_ensemble_entier(ensemble_entier ee) {
    free(ee->tableau);
    free(ee);
}