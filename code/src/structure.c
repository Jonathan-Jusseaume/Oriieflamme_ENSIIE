
#include "../headers/structure.h"
#include <stdlib.h>
#include <stdio.h>

struct s_liste_chainee_carte {
    carte tete;
    liste_chainee_carte queue;
};

struct s_ensemble_entier {
    int *tableau;
    int taille;
};

liste_chainee_carte initialiser_liste_chainee() {
    return NULL;
}

liste_chainee_carte ajouter_tete_liste_chainee(liste_chainee_carte l, carte c) {
    liste_chainee_carte nouvelle_liste = (liste_chainee_carte) malloc(1 * sizeof(liste_chainee_carte));
    nouvelle_liste->tete = c;
    nouvelle_liste->queue = l;
    return nouvelle_liste;
}

carte supprimer_carte_liste_chainee(liste_chainee_carte l, int indice_carte) {
    if (liste_chainee_est_vide(l)) {
        return NULL;
    }
    liste_chainee_carte courant = l;
    if (indice_carte == 0) {
        l = l->queue;
        return courant->tete;
    }
    for (int i = 0; courant != NULL && i < indice_carte - 1; i++)
        courant = courant->queue;
    if (courant == NULL || courant->queue == NULL)
        return NULL;
    liste_chainee_carte nouvelle_queue = courant->queue->queue;
    carte carte_supprimee = courant->queue->tete;
    courant->queue = nouvelle_queue;
    return carte_supprimee;
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

ensemble_entier creer_ensemble_entier() {
    ensemble_entier nouvel_ensemble = (ensemble_entier) malloc(1 * sizeof(ensemble_entier));
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

void liberer_liste_chainee(liste_chainee_carte l) {
    if (l == NULL) {
        return;
    }
    liberer_liste_chainee(l->queue);
    free(l->tete);
    free(l);
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