#include "CUnit/Basic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/structure.h"
#include "../headers/constante.h"

// @todo Changer les tests avec les nouvelles fonctions de carte.h
// @todo Ajouter les tests pour les prochains fichiers

/**
 * On teste que la création de l'ensemble d'entier renvoie un pointeur qui n'est pas NULL
 * et que la taille de cet ensemble vaut 0
 */
void test_creer_ensemble_entier(void) {
    ensemble_entier e = creer_ensemble_entier();
    CU_ASSERT(e != NULL);
    CU_ASSERT(get_taille_ensemble_entier(e) == 0);
    liberer_ensemble_entier(e);
}

/**
 * On teste la fonction qui vérifie si une valeur est dans l'ensemble d'entier
 */
void test_contient_ensemble_entier(void) {
    ensemble_entier e = creer_ensemble_entier();
    CU_ASSERT(FAUX == contient_ensemble_entier(e, 10));
    ajouter_ensemble_entier(e, 10);
    CU_ASSERT(VRAI == contient_ensemble_entier(e, 10));
    liberer_ensemble_entier(e);
}

/**
 * On teste l'ajout en vérifiant qu'il n'y a pas d'ajout si la valeur est déjà présente
 */
void test_ajouter_ensemble_entier(void) {
    ensemble_entier e = creer_ensemble_entier();
    CU_ASSERT(VRAI == ajouter_ensemble_entier(e, 1));
    CU_ASSERT(get_taille_ensemble_entier(e) == 1);
    // On teste quand on ajoute un entier déjà présent
    CU_ASSERT(FAUX == ajouter_ensemble_entier(e, 1));
    CU_ASSERT(get_taille_ensemble_entier(e) == 1);
    CU_ASSERT(VRAI == ajouter_ensemble_entier(e, 2));
    CU_ASSERT(get_taille_ensemble_entier(e) == 2);
    CU_ASSERT(VRAI == ajouter_ensemble_entier(e, 15));
    CU_ASSERT(get_taille_ensemble_entier(e) == 3);
    liberer_ensemble_entier(e);
}

/**
 * On teste la fonction qui donne le i-e élément dans l'ensemble d'entier
 */
void test_get_valeur_indice_ensemble_entier(void) {
    ensemble_entier e = creer_ensemble_entier();
    // On teste quand on donne un trop grand indice
    CU_ASSERT(-1 == get_valeur_indice_ensemble_entier(e, 10));
    ajouter_ensemble_entier(e, 10);
    CU_ASSERT(10 == get_valeur_indice_ensemble_entier(e, 0));
    ajouter_ensemble_entier(e, 15);
    ajouter_ensemble_entier(e, 18);
    CU_ASSERT(18 == get_valeur_indice_ensemble_entier(e, 2));
    CU_ASSERT(-1 == get_valeur_indice_ensemble_entier(e, 3));
    liberer_ensemble_entier(e);
}

/**
 * On s'assure que la fonction renvoie bien le pointeur NULL
 */
void test_initialiser_liste_chainee(void) {
    liste_chainee_carte lc = initialiser_liste_chainee();
    CU_ASSERT(NULL == lc);
    liberer_liste_chainee(lc);
}

/**
 * On teste l'ajout d'un élément en tete la liste
 */
void test_ajouter_tete_liste_chainee(void) {
    liste_chainee_carte lc = initialiser_liste_chainee();
    carte c = initialiser_carte("T", "EFFET", NULL, 1, -1, VRAI);
    lc = ajouter_tete_liste_chainee(lc, c);
    CU_ASSERT(taille_liste_chainee(lc) == 1);
    CU_ASSERT(get_est_face_cachee(get_valeur_tete_liste_chainee(lc)) == VRAI);
    carte c2 = initialiser_carte("T", "EFFET", NULL, 1, -1, FAUX);
    lc = ajouter_tete_liste_chainee(lc, c2);
    CU_ASSERT(taille_liste_chainee(lc) == 2);
    CU_ASSERT(get_est_face_cachee(get_valeur_tete_liste_chainee(lc)) == FAUX);
    liberer_liste_chainee(lc);
}

/**
 * On teste l'obtention du i-e élément de la liste
 */
void test_get_carte_liste_chainee(void) {
    liste_chainee_carte lc = initialiser_liste_chainee();
    CU_ASSERT(get_carte_liste_chainee(lc, 1) == NULL);
    carte c = initialiser_carte("T", "EFFET", NULL, 1, -1, VRAI);
    lc = ajouter_tete_liste_chainee(lc, c);
    carte c2 = initialiser_carte("T", "EFFET", NULL, 1, -1, FAUX);
    lc = ajouter_tete_liste_chainee(lc, c2);
    CU_ASSERT(get_est_face_cachee(get_carte_liste_chainee(lc, 1)) == VRAI);
    liberer_liste_chainee(lc);
}

/**
 * On teste la suppression d'un élément de la liste chainée
 */
void test_supprimer_carte_liste_chainee(void) {
    liste_chainee_carte lc = initialiser_liste_chainee();
    CU_ASSERT(supprimer_carte_liste_chainee(lc, 1) == NULL);
    carte c = initialiser_carte("T", "EFFET", NULL, 1, -1, VRAI);
    lc = ajouter_tete_liste_chainee(lc, c);
    carte c2 = initialiser_carte("T", "EFFET", NULL, 1, -1, FAUX);
    lc = ajouter_tete_liste_chainee(lc, c2);
    carte carte_supprimee = supprimer_carte_liste_chainee(lc, 1);
    CU_ASSERT(get_est_face_cachee(carte_supprimee) == VRAI);
    CU_ASSERT(taille_liste_chainee(lc) == 1);
    free(carte_supprimee);
    liberer_liste_chainee(lc);
}

/**
 * On teste l'initialisation de la grille
 */
void test_initialiser_grille(void) {
    grille_carte g = initialiser_grille(32);
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            // On vérifie que toutes les cases sont bien à null
            CU_ASSERT(get_carte_grille(g, i, j) == NULL);
        }
    }
    // On vérifie que les max et min sont bien aux deux extremes
    CU_ASSERT(get_max_x_grille(g) == 0);
    CU_ASSERT(get_max_y_grille(g) == 0);
    CU_ASSERT(get_min_x_grille(g) == 31);
    CU_ASSERT(get_min_y_grille(g) == 31);
    liberer_grille(g);
}

/**
 * On teste la pose d'une carte sur la grille et de la bonne affectation
 * des max_x min_x min_y max_y
 */
void test_poser_carte_grille(void) {
    grille_carte g = initialiser_grille(32);
    carte c = initialiser_carte("T", "EFFET", NULL, 1, -1, VRAI);
    CU_ASSERT(VRAI == poser_carte_grille(g, c, 15, 15));
    CU_ASSERT(FAUX == poser_carte_grille(g, c, 50, 15));
    CU_ASSERT(get_max_x_grille(g) == 15);
    CU_ASSERT(get_max_y_grille(g) == 15);
    CU_ASSERT(get_min_x_grille(g) == 15);
    CU_ASSERT(get_min_y_grille(g) == 15);
    CU_ASSERT(get_est_face_cachee(get_carte_grille(g, 15, 15)) == VRAI);
    carte c2 = initialiser_carte("T", "EFFET", NULL, 1, -1, FAUX);
    CU_ASSERT(VRAI == poser_carte_grille(g, c2, 14, 15));
    CU_ASSERT(get_max_x_grille(g) == 15);
    CU_ASSERT(get_max_y_grille(g) == 15);
    CU_ASSERT(get_min_x_grille(g) == 15);
    CU_ASSERT(get_min_y_grille(g) == 14);
    CU_ASSERT(get_est_face_cachee(get_carte_grille(g, 14, 15)) == FAUX);
    carte c3 = initialiser_carte("T", "EFFET", NULL, 1, -1, FAUX);
    CU_ASSERT(VRAI == poser_carte_grille(g, c3, 16, 14));
    CU_ASSERT(get_max_x_grille(g) == 15);
    CU_ASSERT(get_max_y_grille(g) == 16);
    CU_ASSERT(get_min_x_grille(g) == 14);
    CU_ASSERT(get_min_y_grille(g) == 14);
    liberer_grille(g);
}

/**
 * On teste l'obtention de la carte la plus en haut à gauche
 */
void test_get_position_carte_haut_gauche_grille(void) {
    grille_carte g = initialiser_grille(32);
    position p = get_position_carte_haut_gauche_grille(g);
    CU_ASSERT(-1 == p.ordonnee);
    CU_ASSERT(-1 == p.abscisse);
    carte c = initialiser_carte("T", "EFFET", NULL, 1, -1, VRAI);
    CU_ASSERT(VRAI == poser_carte_grille(g, c, 15, 15));
    p = get_position_carte_haut_gauche_grille(g);
    CU_ASSERT(15 == p.ordonnee);
    CU_ASSERT(15 == p.abscisse);
    carte c2 = initialiser_carte("T", "EFFET", NULL, 1, -1, FAUX);
    CU_ASSERT(VRAI == poser_carte_grille(g, c2, 0, 0));
    p = get_position_carte_haut_gauche_grille(g);
    CU_ASSERT(15 == p.ordonnee);
    CU_ASSERT(15 == p.abscisse);
    liberer_grille(g);
}

/**
 * On teste la suppression d'une carte sur la grille et de la bonne affectation
 * des max_x min_x min_y max_y
 */
void test_supprimer_carte_grille(void) {
    grille_carte g = initialiser_grille(32);
    carte c = initialiser_carte("T", "EFFET", NULL, 1, -1, VRAI);
    poser_carte_grille(g, c, 15, 15);
    poser_carte_grille(g, c, 0, 15);
    poser_carte_grille(g, c, 31, 15);
    CU_ASSERT(FAUX == poser_carte_grille(g, c, 50, 15));
    CU_ASSERT(get_max_x_grille(g) == 15);
    CU_ASSERT(get_max_y_grille(g) == 31);
    CU_ASSERT(get_min_x_grille(g) == 15);
    CU_ASSERT(get_min_y_grille(g) == 0);
    CU_ASSERT(get_est_face_cachee(supprimer_carte_grille(g, 0, 15)) == VRAI);
    CU_ASSERT(get_max_x_grille(g) == 15);
    CU_ASSERT(get_max_y_grille(g) == 31);
    CU_ASSERT(get_min_x_grille(g) == 15);
    CU_ASSERT(get_min_y_grille(g) == 15);
    CU_ASSERT(supprimer_carte_grille(g, 12, 15) == NULL);
    CU_ASSERT(get_max_x_grille(g) == 15);
    CU_ASSERT(get_max_y_grille(g) == 31);
    CU_ASSERT(get_min_x_grille(g) == 15);
    CU_ASSERT(get_min_y_grille(g) == 15);
    CU_ASSERT(get_est_face_cachee(supprimer_carte_grille(g, 31, 15)) == VRAI);
    CU_ASSERT(get_max_x_grille(g) == 15);
    CU_ASSERT(get_max_y_grille(g) == 15);
    CU_ASSERT(get_min_x_grille(g) == 15);
    CU_ASSERT(get_min_y_grille(g) == 15);
    liberer_grille(g);
}

/**
 * On teste la réinitialisation de la grille
 */
void test_reinitialiser_grille(void) {
    grille_carte g = initialiser_grille(32);
    carte c = initialiser_carte("T", "EFFET", NULL, 1, -1, VRAI);
    poser_carte_grille(g, c, 15, 15);
    reinitialiser_grille(g);
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            // On vérifie que toutes les cases sont bien à NULL
            CU_ASSERT(get_carte_grille(g, i, j) == NULL);
        }
    }
    CU_ASSERT(get_max_x_grille(g) == 0);
    CU_ASSERT(get_max_y_grille(g) == 0);
    CU_ASSERT(get_min_x_grille(g) == 31);
    CU_ASSERT(get_min_y_grille(g) == 31);
    liberer_grille(g);
}

int run_all_tests() {
    CU_pSuite pSuite = NULL;
    // Initialisation du registre C_UNIT
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    // On ajoute la première suite de tests sur le type "ensemble_entier"
    pSuite = CU_add_suite("Tests sur ensemble_entier:", NULL, NULL);
    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    // On ajoute les tests sur le type "ensemble_entier"
    if ((NULL == CU_add_test(pSuite, "creer_ensemble_entier():", test_creer_ensemble_entier))
        || (NULL == CU_add_test(pSuite, "contient_ensemble_entier():", test_contient_ensemble_entier))
        || (NULL == CU_add_test(pSuite, "ajouter_ensemble_entier():", test_ajouter_ensemble_entier))
        ||
        (NULL == CU_add_test(pSuite, "get_valeur_indice_ensemble_entier():", test_get_valeur_indice_ensemble_entier))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // On ajoute la deuxième suite de tests sur le type "liste_chainee_carte"
    pSuite = CU_add_suite("Tests sur liste_chainee:", NULL, NULL);
    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    // On ajoute les tests sur le type "liste_chainee_carte"
    if ((NULL == CU_add_test(pSuite, "initialiser_liste_chainee():", test_initialiser_liste_chainee))
        || (NULL == CU_add_test(pSuite, "ajouter_tete_liste_chainee():", test_ajouter_tete_liste_chainee))
        || (NULL == CU_add_test(pSuite, "get_carte_liste_chainee():", test_get_carte_liste_chainee))
        || (NULL == CU_add_test(pSuite, "supprimer_carte_liste_chainee():", test_supprimer_carte_liste_chainee))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // On ajoute la troisième suite de tests sur le type "grille_carte"
    pSuite = CU_add_suite("Tests sur grille_carte:", NULL, NULL);
    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    // On ajoute les tests sur le type "grille_carte"
    if ((NULL == CU_add_test(pSuite, "initialiser_grille():", test_initialiser_grille))
        || (NULL == CU_add_test(pSuite, "poser_carte_grille():", test_poser_carte_grille))
        || (NULL == CU_add_test(pSuite, "supprimer_carte_grille():", test_supprimer_carte_grille))
        || (NULL ==
            CU_add_test(pSuite, "get_position_carte_haut_gauche_grille():", test_get_position_carte_haut_gauche_grille))
        || (NULL == CU_add_test(pSuite, "reinitialiser_grille():", test_reinitialiser_grille))) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
