
#include "../headers/structure.h"
#include <stdlib.h>

struct s_liste_chainee_carte {
    carte tete;
    liste_chainee_carte queue;
};

liste_chainee_carte initialiser_liste_chainee() {
    return NULL;
}

void ajouter_tete_liste_chainee(liste_chainee_carte l, carte c) {
    liste_chainee_carte nouvelle_queue = l;
    l = (liste_chainee_carte) malloc(1 * sizeof(liste_chainee_carte));
    l->tete = c;
    l->queue = nouvelle_queue;
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
