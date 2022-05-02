#ifndef ORIIEFLAMME_GR_11_TEST_H
#define ORIIEFLAMME_GR_11_TEST_H

/**
 * Lance toutes les fonctions de tests
 * @return
 */
int run_all_tests();

/**
 * On teste que la création de l'ensemble d'entier renvoie un pointeur qui n'est pas NULL
 * et que la taille de cet ensemble vaut 0
 */
void test_creer_ensemble_entier();

/**
 * On teste la fonction qui vérifie si une valeur est dans l'ensemble d'entier
 */
void test_contient_ensemble_entier();

/**
 * On teste l'ajout en vérifiant qu'il n'y a pas d'ajout si la valeur est déjà présente
 */
void test_ajouter_ensemble_entier();

/**
 * On teste la fonction qui donne le i-e élément dans l'ensemble d'entier
 */
void test_get_valeur_indice_ensemble_entier();

/**
 * On s'assure que la fonction renvoie bien le pointeur NULL
 */
void test_initialiser_liste_chainee();

/**
 * On teste l'ajout d'un élément en tete la liste
 */
void test_ajouter_tete_liste_chainee();

/**
 * On teste l'obtention du i-e élément de la liste
 */
void test_get_carte_liste_chainee();

/**
 * On teste la suppression d'un élément de la liste chainée
 */
void test_supprimer_carte_liste_chainee();

/**
 * On teste l'initialisation de la grille
 */
void test_initialiser_grille();

/**
 * On teste la pose d'une carte sur la grille et de la bonne affectation
 * des max_x min_x min_y max_y
 */
void test_poser_carte_grille();

/**
 * On teste l'obtention de la carte la plus en haut à gauche
 */
void test_get_position_carte_haut_gauche_grille();

/**
 * On teste la suppression d'une carte sur la grille et de la bonne affectation
 * des max_x min_x min_y max_y
 */
void test_supprimer_carte_grille();

/**
 * On teste la réinitialisation de la grille
 */
void test_reinitialiser_grille();

/**
 * On teste la demande du renouvellement de la main
 */
void test_demander_renouvellement_main();

/**
 * Test d'initialisation d'une carte
 */
void test_initialiser_carte();

/**
 * Réalise un test sur l'initilisation du plateau
 */
void test_initialiser_plateau();

/**
 * Fonction testant la pose d'une carte pour vérifier que les champs sont bien mis à jour
 */
void test_poser_carte();

/**
 * Fonction testant la fonction initialiser_manche afin de vérifier que la réinitialisation
 * de la grille se passe bien, que les victoires des manches sont bien attribuées
 */
void test_initialiser_manche();

/**
 * Fonction testant certains effets de carte lorsqu'elles sont retournées
 */
void test_retourner_carte();

/**
 * Réalise un test sur l'initialisation des factions
 */
void test_initialiser_factions();

/**
 * Réalise un test pour vérifier que mélanger la pioche est bien aléatoire et qu'elle génère bien un ensemble entier
 * de taille 8 avec des chiffres de 0 à 46
 */
void test_melanger_pioche();

/**
 * On teste que les cartes piochées dans la main sont bien les cartes que l'on a dans notre pioche
 */
void test_repioche();

/**
 * On teste que l'ordre de la première et troisième manche est bien aléatoire
 * et que l'ordre de la deuxième manche est bien déterministe
 */
void test_generer_ordre_partie();

#endif //ORIIEFLAMME_GR_11_TEST_H
