#include "CUnit/Basic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/structure.h"
#include "../headers/constante.h"
#include "../headers/interface.h"
#include "../headers/test.h"
#include "../headers/aleatoire.h"
#include "../headers/effets.h"
#include <unistd.h>
#include <fcntl.h>

// @todo Ajouter les tests pour les prochains fichiers

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

    // On ajoute la quatrième suite de tests sur le type "interface"
    pSuite = CU_add_suite("Tests sur renouvellement main:", NULL, NULL);
    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    // On ajoute les tests concernant l'interface de test
    if ((NULL == CU_add_test(pSuite, "demander_renouvellement_main():", test_demander_renouvellement_main))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // On ajoute la cinquième suite de tests sur le type carte
    pSuite = CU_add_suite("Tests sur carte:", NULL, NULL);
    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    // On ajoute les tests concernant le type carte
    if ((NULL == CU_add_test(pSuite, "initialiser_carte():", test_initialiser_carte))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // On ajoute la sixième suite de tests sur le type plateau
    pSuite = CU_add_suite("Tests sur plateau:", NULL, NULL);
    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    // On ajoute les tests concernant le type plateau
    if ((NULL == CU_add_test(pSuite, "initialiser_plateau():", test_initialiser_plateau))
        || (NULL == CU_add_test(pSuite, "poser_carte():", test_poser_carte))
        || (NULL == CU_add_test(pSuite, "initialiser_manche()", test_initialiser_manche))
        || (NULL == CU_add_test(pSuite, "retourner_carrte()", test_retourner_carte))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // On ajoute la septième suite de tests sur le type faction
    pSuite = CU_add_suite("Tests sur les factions:", NULL, NULL);
    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    // On ajoute les tests concernant la génération aléatoire des manches
    if ((NULL == CU_add_test(pSuite, "initialiser_factions():", test_initialiser_factions))
        || (NULL == CU_add_test(pSuite, "melanger_pioche():", test_melanger_pioche))
        || (NULL == CU_add_test(pSuite, "repioche():", test_repioche))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // On ajoute la huitième suite de tests sur l'aléatoire
    pSuite = CU_add_suite("Tests sur l'aléatoire:", NULL, NULL);
    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    // On ajoute les tests concernant la génération aléatoire des manches
    if ((NULL == CU_add_test(pSuite, "generer_ordre_partie():", test_generer_ordre_partie))) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}

void test_creer_ensemble_entier() {
    ensemble_entier e = creer_ensemble_entier();
    CU_ASSERT(e != NULL);
    CU_ASSERT(get_taille_ensemble_entier(e) == 0);
    liberer_ensemble_entier(e);
}

void test_contient_ensemble_entier() {
    ensemble_entier e = creer_ensemble_entier();
    CU_ASSERT(FAUX == contient_ensemble_entier(e, 10));
    ajouter_ensemble_entier(e, 10);
    CU_ASSERT(VRAI == contient_ensemble_entier(e, 10));
    liberer_ensemble_entier(e);
}

void test_ajouter_ensemble_entier() {
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

void test_get_valeur_indice_ensemble_entier() {
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

void test_initialiser_liste_chainee() {
    liste_chainee_carte lc = initialiser_liste_chainee();
    CU_ASSERT(NULL == lc);
    liberer_liste_chainee(lc);
}

void test_ajouter_tete_liste_chainee() {
    liste_chainee_carte lc = initialiser_liste_chainee();
    carte c = initialiser_carte("T", "EFFET", NULL, 1, -1, VRAI);
    ajouter_tete_liste_chainee(&lc, c);
    CU_ASSERT(taille_liste_chainee(lc) == 1);
    CU_ASSERT(get_est_face_cachee(get_valeur_tete_liste_chainee(lc)) == VRAI);
    carte c2 = initialiser_carte("T", "EFFET", NULL, 1, -1, FAUX);
    ajouter_tete_liste_chainee(&lc, c2);
    CU_ASSERT(taille_liste_chainee(lc) == 2);
    CU_ASSERT(get_est_face_cachee(get_valeur_tete_liste_chainee(lc)) == FAUX);
    liberer_liste_chainee(lc);
}

void test_get_carte_liste_chainee() {
    liste_chainee_carte lc = initialiser_liste_chainee();
    CU_ASSERT(get_carte_liste_chainee(lc, 1) == NULL);
    carte c = initialiser_carte("T", "EFFET", NULL, 1, -1, VRAI);
    ajouter_tete_liste_chainee(&lc, c);
    carte c2 = initialiser_carte("T", "EFFET", NULL, 1, -1, FAUX);
    ajouter_tete_liste_chainee(&lc, c2);
    CU_ASSERT(get_est_face_cachee(get_carte_liste_chainee(lc, 1)) == VRAI);
    liberer_liste_chainee(lc);
}

void test_supprimer_carte_liste_chainee() {
    liste_chainee_carte lc = initialiser_liste_chainee();
    CU_ASSERT(supprimer_carte_liste_chainee(&lc, 1) == NULL);
    carte c = initialiser_carte("T", "EFFET", NULL, 1, -1, VRAI);
    ajouter_tete_liste_chainee(&lc, c);
    carte c2 = initialiser_carte("T", "EFFET", NULL, 1, -1, FAUX);
    carte c3 = initialiser_carte("T", "EFFET", NULL, 1, -1, FAUX);
    carte c4 = initialiser_carte("T", "EFFET", NULL, 1, -1, FAUX);
    carte c5 = initialiser_carte("T", "EFFET", NULL, 1, -1, FAUX);
    ajouter_tete_liste_chainee(&lc, c2);
    ajouter_tete_liste_chainee(&lc, c3);
    ajouter_tete_liste_chainee(&lc, c4);
    ajouter_tete_liste_chainee(&lc, c5);
    supprimer_carte_liste_chainee(&lc, 0);
    CU_ASSERT(taille_liste_chainee(lc) == 4);
    supprimer_carte_liste_chainee(&lc, 3);
    CU_ASSERT(taille_liste_chainee(lc) == 3);
    supprimer_carte_liste_chainee(&lc, 1);
    CU_ASSERT(taille_liste_chainee(lc) == 2);
    free(c5);
    free(c);
    free(c3);
    liberer_liste_chainee(lc);
}

void test_initialiser_grille() {
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

void test_poser_carte_grille() {
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

void test_get_position_carte_haut_gauche_grille() {
    grille_carte g = initialiser_grille(32);
    position p = get_position_carte_haut_gauche_grille(g, VRAI);
    CU_ASSERT(-1 == p.ordonnee);
    CU_ASSERT(-1 == p.abscisse);
    carte c = initialiser_carte("T", "EFFET", NULL, 1, -1, VRAI);
    CU_ASSERT(VRAI == poser_carte_grille(g, c, 15, 15));
    p = get_position_carte_haut_gauche_grille(g, VRAI);
    CU_ASSERT(15 == p.ordonnee);
    CU_ASSERT(15 == p.abscisse);
    carte c2 = initialiser_carte("T", "EFFET", NULL, 1, -1, FAUX);
    CU_ASSERT(VRAI == poser_carte_grille(g, c2, 0, 0));
    p = get_position_carte_haut_gauche_grille(g, VRAI);
    CU_ASSERT(15 == p.ordonnee);
    CU_ASSERT(15 == p.abscisse);
    liberer_grille(g);
}

void test_supprimer_carte_grille() {
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

void test_reinitialiser_grille() {
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

void test_demander_renouvellement_main() {
    // On définit un fichier simulant des entrées utilisateurs
    int fd = open("../test/renouvellement_main_input.txt", O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de tests \n");
        return;
    }
    int stdin = dup(0);
    dup2(fd, 0);
    // La fonction est censé s'arreter quand on est tombé sur une entrée qui nous intéresse
    CU_ASSERT(FAUX == demander_renouvellement_main());
    CU_ASSERT(VRAI == demander_renouvellement_main());
    CU_ASSERT(VRAI == demander_renouvellement_main());
    CU_ASSERT(FAUX == demander_renouvellement_main());
    dup2(stdin, 0);
    close(fd);
}

void test_initialiser_carte() {
    carte c = initialiser_carte(nom_cartes[FISA], effets_description[FISA], NULL, 1, -1, VRAI);
    CU_ASSERT(strcmp(get_nom_carte(c), nom_cartes[FISA]) == 0);
    CU_ASSERT(strcmp(get_effet(c), effets_description[FISA]) == 0);
    CU_ASSERT(get_position(c).abscisse == -1);
    CU_ASSERT(get_position(c).ordonnee == -1);
    CU_ASSERT(get_identifiant_faction_carte(c) == 1);
    CU_ASSERT(get_numero_plateau(c) == -1);
    CU_ASSERT(get_est_face_cachee(c) == VRAI);
    set_est_face_cachee(c, FAUX);
    CU_ASSERT(get_est_face_cachee(c) == FAUX);
    free(c);
}

void test_initialiser_plateau() {
    plateau p = nouveau_plateau();
    CU_ASSERT(get_taille_grille(get_grille(p)) == 2 * NOMBRE_CARTES_MAXIMUM);
    CU_ASSERT(get_factions(p) != NULL);
    CU_ASSERT(get_nombre_cartes_posees(p) == 0);
    CU_ASSERT(get_derniere_carte_retournee(p) == NULL);
    CU_ASSERT(get_nombre_cartes_retournees(p) == 0);
    liberer_plateau(p);
}

void test_poser_carte() {
    plateau p = nouveau_plateau();
    carte c = initialiser_carte(nom_cartes[FISA], effets_description[FISA], NULL, 1, -1, VRAI);
    carte c2 = initialiser_carte(nom_cartes[FISE], effets_description[FISE], NULL, 1, -1, VRAI);
    poser_carte(p, c, (position) {15, 15});
    poser_carte(p, c2, (position) {0, 8});
    CU_ASSERT(get_nombre_cartes_posees(p));
    CU_ASSERT(get_position(c).abscisse == 15);
    CU_ASSERT(get_position(c).ordonnee == 15);
    CU_ASSERT(get_position(c2).abscisse == 0);
    CU_ASSERT(get_position(c2).ordonnee == 8);
    CU_ASSERT(strcmp(get_nom_carte(get_carte_grille(get_grille(p), 8, 0)), nom_cartes[FISE]) == 0);
    liberer_plateau(p);
}

void test_initialiser_manche() {
    plateau p = nouveau_plateau();
    carte c = initialiser_carte(nom_cartes[FISA], effets_description[FISA], NULL, 1, -1, VRAI);
    poser_carte(p, c, (position) {15, 15});
    // On teste que la faction avec le plus de points gagne la manche
    set_points_DDRS(get_factions(p)[0], 10);
    set_points_DDRS(get_factions(p)[1], 15);
    CU_ASSERT(initialiser_manche(p) == -1);
    CU_ASSERT(get_manches_gagnees(get_factions(p)[0]) == 0);
    CU_ASSERT(get_manches_gagnees(get_factions(p)[1]) == 1);
    CU_ASSERT(get_points_DDRS(get_factions(p)[0]) == 0);
    CU_ASSERT(get_points_DDRS(get_factions(p)[1]) == 0);
    for (int i = 0; i < NOMBRE_CARTES_MAXIMUM * 2; i++) {
        for (int j = 0; j < NOMBRE_CARTES_MAXIMUM * 2; j++) {
            // On vérifie que toutes les cases sont bien à NULL
            CU_ASSERT(get_carte_grille(get_grille(p), i, j) == NULL);
        }
    }
    // On teste que si la dernière carte retournée est Laurent Prével alors peu importe le score, c'est la faction de Laurent Prével qui gagne
    carte laurent = initialiser_carte(nom_cartes[Laurent_Prevel], effets_description[Laurent_Prevel], NULL, FACTION1,
                                      -1, FAUX);
    poser_carte(p, laurent, (position) {12, 10});
    set_points_DDRS(get_factions(p)[FACTION1], -12);
    set_points_DDRS(get_factions(p)[FACTION2], 115);
    set_derniere_carte_retournee(p, laurent);
    CU_ASSERT(initialiser_manche(p) == -1)
    CU_ASSERT(get_manches_gagnees(get_factions(p)[FACTION1]) == 1);
    CU_ASSERT(get_manches_gagnees(get_factions(p)[FACTION2]) == 1);
    CU_ASSERT(get_points_DDRS(get_factions(p)[FACTION1]) == 0);
    CU_ASSERT(get_points_DDRS(get_factions(p)[FACTION2]) == 0);

    // On teste que s'il y a égalité alors c'est la faction qui a la carte la plus en haut à gauche qui gagne
    carte bas_droite = initialiser_carte(nom_cartes[FISA], effets_description[FISA], NULL, FACTION1, -1, VRAI);
    carte haut_gauche = initialiser_carte(nom_cartes[FISE], effets_description[FISE], NULL, FACTION2, -1, VRAI);
    set_points_DDRS(get_factions(p)[FACTION1], 8);
    set_points_DDRS(get_factions(p)[FACTION2], 8);
    poser_carte(p, bas_droite, (position) {16, 15});
    poser_carte(p, haut_gauche, (position) {3, 3});
    CU_ASSERT(initialiser_manche(p) == FACTION2);
    CU_ASSERT(get_manches_gagnees(get_factions(p)[FACTION1]) == 1);
    CU_ASSERT(get_manches_gagnees(get_factions(p)[FACTION2]) == 2);
    liberer_plateau(p);

}

void test_retourner_carte() {
    // On crée un plateau
    plateau p = nouveau_plateau();
    // On ajoute les cartes dont l'on veut tester l'effet
    carte fise = initialiser_carte(nom_cartes[FISE], effets_description[FISE], effets[FISE], FACTION1, 0, VRAI);
    carte fisa_faction_2 = initialiser_carte(nom_cartes[FISA], effets_description[FISA], effets[FISA], FACTION2, 1,
                                             VRAI);
    carte fisa_faction_1 = initialiser_carte(nom_cartes[FISA], effets_description[FISA], effets[FISA], FACTION1, 2,
                                             VRAI);
    carte fc_1 = initialiser_carte(nom_cartes[FC], effets_description[FC], effets[FC], FACTION2, 3, VRAI);
    carte fc_2 = initialiser_carte(nom_cartes[FC], effets_description[FC], effets[FC], FACTION1, 4, VRAI);
    carte ecologiie = initialiser_carte(nom_cartes[EcologIIE], effets_description[EcologIIE], effets[EcologIIE],
                                        FACTION2, 5, VRAI);
    carte lIIens = initialiser_carte(nom_cartes[lIIEns], effets_description[lIIEns], effets[lIIEns], FACTION2, 6, VRAI);
    carte alcool = initialiser_carte(nom_cartes[Alcool], effets_description[Alcool], effets[Alcool], FACTION2, 7, VRAI);
    carte soiree_sans_alcool = initialiser_carte(nom_cartes[Soiree_sans_alcool], effets_description[Soiree_sans_alcool],
                                                 effets[Soiree_sans_alcool], FACTION2, 8, VRAI);
    carte ecocup = initialiser_carte(nom_cartes[Ecocup], effets_description[Ecocup], effets[Ecocup], FACTION2, 9, VRAI);
    carte cafe = initialiser_carte(nom_cartes[Cafe], effets_description[Cafe], effets[Cafe], FACTION2, 10, VRAI);
    carte heures_supplementaires = initialiser_carte(nom_cartes[Heures_supplementaires],
                                                     effets_description[Heures_supplementaires],
                                                     effets[Heures_supplementaires], FACTION1, 11, VRAI);
    carte fetia_bannour = initialiser_carte(nom_cartes[Fetia_Bannour], effets_description[Fetia_Bannour],
                                            effets[Fetia_Bannour], FACTION1, 12, VRAI);
    poser_carte(p, fisa_faction_1, (position) {10, 8});
    poser_carte(p, fisa_faction_2, (position) {9, 8});
    poser_carte(p, fise, (position) {8, 8});
    poser_carte(p, fc_1, (position) {9, 9});
    poser_carte(p, fc_2, (position) {10, 9});
    poser_carte(p, ecologiie, (position) {10, 10});
    poser_carte(p, lIIens, (position) {11, 10});
    poser_carte(p, alcool, (position) {11, 11});
    poser_carte(p, soiree_sans_alcool, (position) {13, 12});
    poser_carte(p, cafe, (position) {14, 12});
    poser_carte(p, heures_supplementaires, (position) {15, 12});
    poser_carte(p, fetia_bannour, (position) {16, 12});
    poser_carte(p, ecocup, (position) {13, 13});
    // On retourne la première carte
    carte c_retournee = retourner_carte(p);
    // On vérifie qu'on a bien retourné la bonne carte et qu'elle n'est plus face cachée
    CU_ASSERT(strcmp(get_nom_carte(c_retournee), nom_cartes[FISE]) == 0);
    CU_ASSERT(get_est_face_cachee(c_retournee) == FAUX);
    // FISE a rajouté 1 point à l'équipe FACTION1
    CU_ASSERT(get_points_DDRS(get_factions(p)[FACTION1]) == 1);

    // On retourne la deuxième carte
    c_retournee = retourner_carte(p);
    // On vérifie qu'on a bien retourné la bonne carte et qu'elle n'est plus face cachée
    CU_ASSERT(strcmp(get_nom_carte(c_retournee), nom_cartes[FISA]) == 0);
    CU_ASSERT(get_est_face_cachee(c_retournee) == FAUX);
    // FISA a rajouté 2 points à l'équipe FACTION2 car il y a deux cartes retournées
    CU_ASSERT(get_points_DDRS(get_factions(p)[FACTION2]) == 2);

    // On retourne la troisième carte
    c_retournee = retourner_carte(p);
    // On vérifie qu'on a bien retourné la bonne carte et qu'elle n'est plus face cachée
    CU_ASSERT(strcmp(get_nom_carte(c_retournee), nom_cartes[FISA]) == 0);
    CU_ASSERT(get_est_face_cachee(c_retournee) == FAUX);
    // FISA n'a pas rajouté deux points à la faction 1 car il y a trois cartes retournées
    CU_ASSERT(get_points_DDRS(get_factions(p)[FACTION1]) == 1);

    // On retourne la quatrième carte
    c_retournee = retourner_carte(p);
    // On vérifie qu'on a bien retourné la bonne carte et qu'elle n'est plus face cachée
    CU_ASSERT(strcmp(get_nom_carte(c_retournee), nom_cartes[FC]) == 0);
    CU_ASSERT(get_est_face_cachee(c_retournee) == FAUX);
    // FC n'a pas rajouté quatre points à la faction 2 car il n'y pas d'autres cartes FC retournées
    CU_ASSERT(get_points_DDRS(get_factions(p)[FACTION2]) == 2);

    // On retourne la cinquième carte
    c_retournee = retourner_carte(p);
    // On vérifie qu'on a bien retourné la bonne carte et qu'elle n'est plus face cachée
    CU_ASSERT(strcmp(get_nom_carte(c_retournee), nom_cartes[FC]) == 0);
    CU_ASSERT(get_est_face_cachee(c_retournee) == FAUX);
    // FC a rajouté quatre points à la faction 2 car il y a une autre carte FC retournée
    CU_ASSERT(get_points_DDRS(get_factions(p)[FACTION1]) == 5);

    // On retourne la sixième carte
    c_retournee = retourner_carte(p);
    // On vérifie qu'on a bien retourné la bonne carte et qu'elle n'est plus face cachée
    CU_ASSERT(strcmp(get_nom_carte(c_retournee), nom_cartes[EcologIIE]) == 0);
    CU_ASSERT(get_est_face_cachee(c_retournee) == FAUX);
    // Ecologiie rapporte 1 point par carte FC/FISE/FISA retournée, il y en a 5 donc faction 2 prend 5 points
    CU_ASSERT(get_points_DDRS(get_factions(p)[FACTION2]) == 7);

    // On retourne la septième carte
    c_retournee = retourner_carte(p);
    // On vérifie qu'on a bien retourné la bonne carte et qu'elle n'est plus face cachée
    CU_ASSERT(strcmp(get_nom_carte(c_retournee), nom_cartes[lIIEns]) == 0);
    CU_ASSERT(get_est_face_cachee(c_retournee) == FAUX);
    // On vérifie que les cartes FC/FISA/FC sont replacées face cachée en haut à gauche
    for (int x = 9; x >= 5; x--) {
        CU_ASSERT(strcmp(get_nom_carte(get_carte_grille(get_grille(p), 10, x)), nom_cartes[FISE]) == 0
                  || strcmp(get_nom_carte(get_carte_grille(get_grille(p), 10, x)), nom_cartes[FC]) == 0
                  || strcmp(get_nom_carte(get_carte_grille(get_grille(p), 10, x)), nom_cartes[FISA]) == 0);
        CU_ASSERT(get_est_face_cachee(get_carte_grille(get_grille(p), 10, x)) == VRAI);
    }
    // On re retourne les cartes
    for (int i = 0; i < 5; i++) {
        retourner_carte(p);
    }

    // On retourne la huitième carte (ALCOOL)
    c_retournee = retourner_carte(p);
    // On vérifie qu'on a bien retourné la bonne carte et qu'elle n'est plus face cachée
    CU_ASSERT(strcmp(get_nom_carte(c_retournee), nom_cartes[Alcool]) == 0);
    CU_ASSERT(get_est_face_cachee(c_retournee) == FAUX);
    // On vérifie que les cartes adjacentes ont été détruites car il s'agit de la carte alcool qui a été retournée
    position pos_alcool = get_position(c_retournee);
    CU_ASSERT(get_carte_grille(get_grille(p), pos_alcool.ordonnee - 1, pos_alcool.abscisse) == NULL
              && get_carte_grille(get_grille(p), pos_alcool.ordonnee + 1, pos_alcool.abscisse) == NULL
              && get_carte_grille(get_grille(p), pos_alcool.ordonnee, pos_alcool.abscisse - 1) == NULL
              && get_carte_grille(get_grille(p), pos_alcool.ordonnee, pos_alcool.abscisse + 1) == NULL);

    // On retourne la neuvième carte (Soiree sans alcool)
    afficher_plateau(p);

    c_retournee = retourner_carte(p);
    // On vérifie que les cartes FISE/FISA/FC ont été supprimées et que la première et la dernière ligne ont été supprimés
    CU_ASSERT(strcmp(get_nom_carte(c_retournee), nom_cartes[Soiree_sans_alcool]) == 0);
    CU_ASSERT(get_est_face_cachee(c_retournee) == FAUX);
    for (int i = 0; i < 2 * NOMBRE_CARTES_MAXIMUM; i++) {
        CU_ASSERT(get_carte_grille(get_grille(p), 10, i) == NULL);
        CU_ASSERT(get_carte_grille(get_grille(p), 13, i) == NULL);
    }
    int score_faction_1 = get_points_DDRS(get_factions(p)[FACTION1]);
    int score_faction_2 = get_points_DDRS(get_factions(p)[FACTION2]);
    // On retourne la carte Café pour vérifier que notre faction perd des points et que la carte Alcool a été supprimée
    c_retournee = retourner_carte(p);
    CU_ASSERT(strcmp(get_nom_carte(c_retournee), nom_cartes[Cafe]) == 0);
    CU_ASSERT(get_est_face_cachee(c_retournee) == FAUX);
    CU_ASSERT(get_carte_grille(get_grille(p), get_position(alcool).ordonnee, get_position(alcool).abscisse) == NULL);
    CU_ASSERT(get_points_DDRS(get_factions(p)[FACTION2]) == (score_faction_2 - 1));
    score_faction_2 -= 1;
    // On retourne la carte Heures supplémentaires pour vérifier que la faction adverse perd 3 points car il y a
    // une carte Heure supplémentaires
    c_retournee = retourner_carte(p);
    CU_ASSERT(strcmp(get_nom_carte(c_retournee), nom_cartes[Heures_supplementaires]) == 0);
    CU_ASSERT(get_est_face_cachee(c_retournee) == FAUX);
    CU_ASSERT(get_points_DDRS(get_factions(p)[FACTION2]) == (score_faction_2 - 3));
    score_faction_2 -= 3;

    // On retourne la carte Heures supplémentaires pour vérifier que la faction adverse perd 3 points car il y a
    // une carte Heure supplémentaires
    c_retournee = retourner_carte(p);
    CU_ASSERT(strcmp(get_nom_carte(c_retournee), nom_cartes[Fetia_Bannour]) == 0);
    // On vérifie que toute la ligne vaut NULL et que toute sa colone vaut NULL également
    for (int i = 0; i < NOMBRE_CARTES_MAXIMUM * 2; i++) {
        CU_ASSERT(get_carte_grille(get_grille(p), get_position(fetia_bannour).ordonnee, i) == NULL);
        CU_ASSERT(get_carte_grille(get_grille(p), i, get_position(fetia_bannour).abscisse) == NULL);
    }
    afficher_plateau(p);
    liberer_plateau(p);
}

void test_initialiser_factions() {
    faction *factions = initialiser_factions();
    for (int i = 0; i < NOMBRE_FACTIONS; i++) {
        CU_ASSERT(get_manches_gagnees(factions[i]) == 0);
        CU_ASSERT(get_identifiant_faction(factions[i]) == i);
        CU_ASSERT(get_points_DDRS(factions[i]) == 0);
        CU_ASSERT(get_a_remelanger(factions[i]) == FAUX);
        CU_ASSERT(get_main(factions[i]) == NULL);
        CU_ASSERT(get_pioche(factions[i]) == NULL);
        free(factions[i]);
    }
    free(factions);
}

void test_melanger_pioche() {
    faction *factions = initialiser_factions();
    ensemble_entier entiers_generer = creer_ensemble_entier();
    for (int i = 0; i < NOMBRE_FACTIONS; i++) {
        for (int j = 0; j < 10; j++) {
            melanger_pioche(factions[i]);
            CU_ASSERT(get_taille_ensemble_entier(get_pioche(factions[i])) == NOMBRE_CARTES_MAIN);
            for (int l = 0; l < get_taille_ensemble_entier(get_pioche(factions[i])); l++) {
                CU_ASSERT(get_valeur_indice_ensemble_entier(get_pioche(factions[i]), l) >= 0 &&
                          get_valeur_indice_ensemble_entier(get_pioche(factions[i]), l) < NOMBRE_CARTES_TOTALES);
                ajouter_ensemble_entier(entiers_generer, get_valeur_indice_ensemble_entier(get_pioche(factions[i]), l));
            }
            vider_main_dans_pioche(factions[i]);
        }
    }
    // On vérifie qu'on a généré plus de huit entiers différents pour vérifier qu'on ne tombe pas tout le temps sur les mêmes chiffres
    CU_ASSERT(get_taille_ensemble_entier(entiers_generer) > NOMBRE_CARTES_MAIN);
    for (int i = 0; i < NOMBRE_FACTIONS; i++) {
        free(factions[i]);
    }
    free(factions);
    liberer_ensemble_entier(entiers_generer);
}

void test_repioche() {
    plateau p = nouveau_plateau();
    ensemble_entier pioche_faction_1 = creer_ensemble_entier();
    // On vérifie que quand on associe un entier alors on pioche la bonne carte associée
    ajouter_ensemble_entier(pioche_faction_1, 0);
    ajouter_ensemble_entier(pioche_faction_1, 4);
    ajouter_ensemble_entier(pioche_faction_1, 5);
    ajouter_ensemble_entier(pioche_faction_1, 8);
    ajouter_ensemble_entier(pioche_faction_1, 46);
    set_pioche(get_factions(p)[FACTION1], pioche_faction_1);
    repioche(get_factions(p)[FACTION1]);
    liste_chainee_carte main_faction = get_main(get_factions(p)[FACTION1]);
    // On vérifie qu'on a bien pioché les bonnes cartes
    CU_ASSERT(strcmp(get_nom_carte(get_carte_liste_chainee(main_faction, 4)), nom_cartes[FISE]) == 0);
    CU_ASSERT(strcmp(get_nom_carte(get_carte_liste_chainee(main_faction, 3)), nom_cartes[FISA]) == 0);
    CU_ASSERT(strcmp(get_nom_carte(get_carte_liste_chainee(main_faction, 2)), nom_cartes[FISA]) == 0);
    CU_ASSERT(strcmp(get_nom_carte(get_carte_liste_chainee(main_faction, 1)), nom_cartes[FC]) == 0);
    CU_ASSERT(strcmp(get_nom_carte(get_carte_liste_chainee(main_faction, 0)), nom_cartes[Laurent_Prevel]) == 0);
    liberer_ensemble_entier(pioche_faction_1);
    liberer_liste_chainee(main_faction);
    liberer_plateau(p);
}

void test_generer_ordre_partie() {
    // On veut montrer qu'on peut avoir soit un 0 soit un 1 pour la première et la troisième manche, à chaque fois on vérifie que la valeur de la deuxième manche
    // est toujours l'opposée de la première manche
    // On regarde si la faction a déjà été première au moins une fois pour voir si c'est possible
    booleen faction_0_premiere = FAUX;
    booleen faction_1_premiere = FAUX;
    // On regarde si la faction a déjà été première à la troisième manche au moins une fois pour voir si c'est possible
    booleen faction_0_troisieme = FAUX;
    booleen faction_1_troisieme = FAUX;
    do {
        int *ordre = generer_ordre_partie();
        if (ordre[0] == 0) {
            CU_ASSERT(ordre[1] == 1);
            faction_0_premiere = VRAI;
        } else if (ordre[0] == 1) {
            CU_ASSERT(ordre[1] == 0);
            faction_1_premiere = VRAI;
        }
        if (ordre[2] == 0) {
            faction_0_troisieme = VRAI;
        } else if (ordre[2] == 1) {
            faction_1_troisieme = VRAI;
        }
        free(ordre);
    } while (!faction_0_premiere || !faction_0_troisieme || !faction_1_premiere || !faction_1_troisieme);
    CU_ASSERT(faction_1_premiere == VRAI);
    CU_ASSERT(faction_0_premiere == VRAI);
    CU_ASSERT(faction_1_troisieme == VRAI);
    CU_ASSERT(faction_0_troisieme == VRAI);

}
