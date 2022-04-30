#include <stdlib.h>
#include <stdio.h>
#include "../headers/constante.h"
#include "../headers/carte.h"
#include "../headers/plateau.h"
#include "../headers/faction.h"

/**
 * Une fonction pour afficher le plateau de jeu.
 * @param p : le plateau de jeu à afficher.
 */
void afficher_plateau(plateau p) {
    for (int x = get_min_x_grille(get_grille(p)); x <= get_max_x_grille(get_grille(p)); x++) {
        for (int y = get_min_y_grille(get_grille(p)); x <= get_max_y_grille(get_grille(p)); y++) {
            if (get_carte_grille(get_grille(p), y, x) != NULL) {
                printf("%d ", get_numero_plateau(get_carte_grille(get_grille(p), y, x)));
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
}

/**
 * Une fonction pour afficher la main d'une faction.
 * @param f : La faction dont on va afficher la main.
 */
void afficher_main_faction(faction f) {
    liste_chainee_carte main = get_main(f);
    int i = 0;
    while (get_queue_liste_chainee(main) != NULL) {
        i++;
        main = get_queue_liste_chainee(main);
        printf("%d : %s \n", i, get_nom_carte(get_valeur_tete_liste_chainee(main)));
    }
};

/**
 * Une fonction pour demander à une faction si elle veut renouveller sa main.
 * @param f : la faction à laquelle on va demander si elle veut renouveller sa main.
 * @return booleen : VRAI si la faction veut vider sa main, mélanger sa pioche et repiocher, FAUX sinon.
 */
booleen demander_renouvellement_main() {
    char *rep = "";
    while (strcmp(rep, "O") != 0 || strcmp(rep, "o") != 0 || strcmp(rep, "N") != 0 || strcmp(rep, "n") != 0) {
        printf("Voulez vous renouveller votre main ? (O/N)");
        scanf("%s", rep);
    }
    return strcmp(rep, "O") || strcmp(rep, "o") ? VRAI : FAUX;
};

/**
 * Une fonction pour demander à une faction quelle carte de sa main elle veut poser face cachée.
 * @param f : la faction à laquelle on va demander quelle carte de sa main elle veut poser face cachée.
 * @return carte : la carte que la faction veut poser face cachée.
 */
carte demander_carte_poser_face_cachee(faction f) {
    carte carte_choisie = NULL;

    if (f != NULL) {
        afficher_main_faction(f);

        char *numero_carte = "";
        liste_chainee_carte main = get_main(f);
        int taille = taille_liste_chainee(main);

        do {
            printf("Quelle carte voulez vous placer face cachée sur le plateau ?");
            scanf("%s", numero_carte);
        } while (atoi(numero_carte) > taille && atoi(numero_carte) <= 0);
        carte_choisie = supprimer_carte_liste_chainee(main, atoi(numero_carte));
    }
    return carte_choisie;
}

/**
 * Une fonction pour demander à une faction à quelle position elle veut poser sa carte face cachée qu'elle a choisie précédemment,
 * et faire des vérifications sur cette position choisie.
 * @param p : Le plateau de jeu sur lequel on va faire des vérifications pour la position choisie.
 * @param f : La faction à laquelle on va demander à quelle position elle veut poser sa carte.
 * @param c : La carte que l'on veut poser à une position que la faction va choisir.
 * @return position : Position en abscisse et en ordonnée de la carte à poser, calculée à partir des entrées de l'utilisateur.
 */
position demander_position_poser_carte(plateau p, faction f, carte c) {
    char *carte_a_coller = "";
    direction dir = INCONNU;
    char *dirs = "";
    position pos_carte = {15, 15};

    if (get_nombre_cartes_posees(p) == 0) {
        return pos_carte;
    }
    do {
        printf("Tapez le numéro de la carte face cachée à côté de laquelle vous voulez vous placer ?\n");
        scanf("%s", carte_a_coller);

        for (int x = get_min_x_grille(get_grille(p)); x <= get_max_x_grille(get_grille(p)); x++) {
            for (int y = get_min_y_grille(get_grille(p)); y <= get_max_y_grille(get_grille(p)); y++) {
                if (get_carte_grille(get_grille(p), y, x) != NULL &&
                    atoi(carte_a_coller) == get_numero_plateau(get_carte_grille(get_grille(p), y, x))) {
                    if (get_carte_grille(get_grille(p), x + 1, y) != NULL &&
                        get_carte_grille(get_grille(p), x - 1, y) != NULL &&
                        get_carte_grille(get_grille(p), x, y - 1) != NULL &&
                        get_carte_grille(get_grille(p), x, y + 1) != NULL) {
                        printf("Vous ne pouvez pas placer votre carte à côte de cette carte, toute les places sont prises.\n");
                        carte_a_coller = "-1";
                    } else {
                        do {
                            printf("Quelle direction voulez vous placer votre carte ? (H/B/D/G)");
                            scanf("%s", dirs);
                            dir = (direction) dirs[0];

                            switch (dir) {
                                case HAUT:
                                    if (get_carte_grille(get_grille(p), x + 1, y) != NULL) {
                                        printf("Vous ne pouvez pas placer votre carte à côte de cette carte, la place est prise.\n");
                                        dir = INCONNU;
                                    } else {
                                        pos_carte.abscisse = x + 1;
                                        pos_carte.ordonnee = y;
                                        return pos_carte;
                                    }
                                    break;

                                case BAS:
                                    if (get_carte_grille(get_grille(p), x - 1, y) != NULL) {
                                        printf("Vous ne pouvez pas placer votre carte à côte de cette carte, la place est prise.\n");
                                        dir = INCONNU;
                                    } else {
                                        pos_carte.abscisse = x - 1;
                                        pos_carte.ordonnee = y;
                                        return pos_carte;
                                    }
                                    break;

                                case DROITE:
                                    if (get_carte_grille(get_grille(p), x, y + 1) != NULL) {
                                        printf("Vous ne pouvez pas placer votre carte à côte de cette carte, la place est prise.\n");
                                        dir = INCONNU;
                                    } else {
                                        pos_carte.abscisse = x;
                                        pos_carte.ordonnee = y + 1;
                                        return pos_carte;
                                    }
                                    break;

                                case GAUCHE:
                                    if (get_carte_grille(get_grille(p), x, y - 1) != NULL) {
                                        printf("Vous ne pouvez pas placer votre carte à côte de cette carte, la place est prise.\n");
                                        dir = INCONNU;
                                    } else {
                                        pos_carte.abscisse = x;
                                        pos_carte.ordonnee = y - 1;
                                        return pos_carte;
                                    }
                                    break;

                                default:
                                    break;
                            }
                        } while (dir != HAUT && dir != BAS && dir != DROITE && dir != GAUCHE);
                    }
                } else {
                    printf("Il pas de carte ici.\n");
                    carte_a_coller = "-1";
                }
            }
        }
    } while (atoi(carte_a_coller) > get_nombre_cartes_posees(p) && atoi(carte_a_coller) <= 0);
};

/**
 * Une fonction pour afficher l'effet d'une carte qui vient d'être retournée face visible.
 * @param c : La carte dont on veut afficher l'effet.
 */
void afficher_effet_carte_retournee(carte c) {
    printf("L'effet de la carte est : %s", get_effet(c));
};

/**
 * Une fonction pour afficher la faction victorieuse de la partie.
 * @param f : la faction victorieuse de la partie.
 */
void afficher_vainqueur(faction f) {
    printf("La faction victorieuse est la faction : %s", get_nom_faction(f));
};