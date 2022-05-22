#include <stdlib.h>
#include <stdio.h>
#include "unistd.h"

#include "../headers/constante.h"
#include "../headers/carte.h"
#include "../headers/plateau.h"
#include "../headers/faction.h"
#include <ctype.h>

/**
 * Regarde si la chaîne de caractères passée en paramètre est bien un nombre
 * @param str la chaine dont on veut vérifier qu'elle est un nombre
 * @return VRAI si la chaîne est un nombre, FAUX sinon
 */
booleen est_un_nombre(char *str) {
    for (int i = 0; i < ((int) strlen(str)); i++) {
        if (!isdigit(str[i])) {
            return FAUX;
        }
    }
    return VRAI;
}

/**
 * Une fonction pour afficher le plateau de jeu.
 * @param p : le plateau de jeu à afficher.
 */
void afficher_plateau(plateau p) {
    printf("PLATEAU : \n");
    for (int x = get_min_x_grille(get_grille(p)); x <= get_max_x_grille(get_grille(p)); x++) {
        printf("---");
    }
    printf("\n");
    for (int y = get_min_y_grille(get_grille(p)); y <= get_max_y_grille(get_grille(p)); y++) {
        for (int x = get_min_x_grille(get_grille(p)); x <= get_max_x_grille(get_grille(p)); x++) {
            if (get_carte_grille(get_grille(p), y, x) != NULL) {
                if (get_est_face_cachee(get_carte_grille(get_grille(p), y, x)) == VRAI) {
                    printf("%2d ", get_numero_plateau(get_carte_grille(get_grille(p), y, x)));
                } else {
                    char *nom_carte = get_nom_carte(get_carte_grille(get_grille(p), y, x));
                    printf("%c%c ", nom_carte[0], nom_carte[strlen(nom_carte) - 1]);
                }

            } else {
                printf("   ");
            }
        }
        printf("\n");
    }
    for (int x = get_min_x_grille(get_grille(p)); x <= get_max_x_grille(get_grille(p)); x++) {
        printf("---");
    }
    printf("\n");
}

/**
 * Une fonction pour afficher la main d'une faction.
 * @param f : La faction dont on va afficher la main.
 */
void afficher_main_faction(faction f) {
    liste_chainee_carte main_faction = get_main(f);
    int i = 0;
    printf("\nMain de la faction %d : \n--------------------- \n", get_identifiant_faction(f));
    while (main_faction != NULL) {
        i++;
        printf("%d : %s", i, get_nom_carte(get_valeur_tete_liste_chainee(main_faction)));
        main_faction = get_queue_liste_chainee(main_faction);
        if (main_faction != NULL) {
            printf(", ");
        }
    }
    printf("\n");
}

/**
 * Une fonction pour demander à une faction si elle veut renouveller sa main.
 * @param f : la faction à laquelle on va demander si elle veut renouveller sa main.
 * @return booleen : VRAI si la faction veut vider sa main, mélanger sa pioche et repiocher, FAUX sinon.
 */
booleen demander_renouvellement_main() {
    char rep[10];
    do {
        printf("Voulez vous renouveller votre main ? (O/N) \n");
        scanf("%s", rep);
    } while (strcmp(rep, "O") != 0 && strcmp(rep, "o") != 0 && strcmp(rep, "N") != 0 && strcmp(rep, "n") != 0);
    return strcmp(rep, "O") == 0 || strcmp(rep, "o") == 0 ? VRAI : FAUX;
}

/**
 * Une fonction pour demander à une faction quelle carte de sa main elle veut poser face cachée.
 * @param f : la faction à laquelle on va demander quelle carte de sa main elle veut poser face cachée.
 * @return carte : la carte que la faction veut poser face cachée.
 */
carte demander_carte_poser_face_cachee(faction f) {
    carte carte_choisie = NULL;

    if (f != NULL) {
        char numero_carte[10];
        liste_chainee_carte main_faction = get_main(f);
        int taille = taille_liste_chainee(main_faction);

        do {
            printf("Quelle carte voulez vous placer face cachée sur le plateau ? ");
            scanf("%s", numero_carte);
        } while (!est_un_nombre(numero_carte) || atoi(numero_carte) > taille || atoi(numero_carte) <= 0);
        carte_choisie = supprimer_carte_liste_chainee(&main_faction, atoi(numero_carte) - 1);
        set_main(f, main_faction);
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
    PARAMETRE_NON_UTILISE(f);
    set_numero_plateau(c, get_nombre_cartes_posees(p));
    int carte_a_coller;
    direction dir = INCONNU;
    char dirs[10];
    position pos_carte = {15, 15};

    if (get_nombre_cartes_posees(p) == 0) {
        return pos_carte;
    }
    char carte_entree_utilisateur[10];
    do {

        printf("Tapez le numéro de la carte face cachée à côté de laquelle vous voulez vous placer ? \n");
        scanf("%s", carte_entree_utilisateur);
        // La chaine saisie doit être un nombre
        if (est_un_nombre(carte_entree_utilisateur)) {
            for (int x = get_min_x_grille(get_grille(p)); x <= get_max_x_grille(get_grille(p)); x++) {
                for (int y = get_min_y_grille(get_grille(p)); y <= get_max_y_grille(get_grille(p)); y++) {
                    if (get_carte_grille(get_grille(p), y, x) != NULL &&
                        atoi(carte_entree_utilisateur) == get_numero_plateau(get_carte_grille(get_grille(p), y, x))) {
                        if (get_carte_grille(get_grille(p), y, x + 1) != NULL &&
                            get_carte_grille(get_grille(p), y, x - 1) != NULL &&
                            get_carte_grille(get_grille(p), y - 1, x) != NULL &&
                            get_carte_grille(get_grille(p), y + 1, x) != NULL) {
                            printf("Vous ne pouvez pas placer votre carte à côte de cette carte, toute les places sont prises.\n");
                            carte_a_coller = -1;
                        } else {
                            carte_a_coller = atoi(carte_entree_utilisateur);
                            do {
                                printf("Quelle direction voulez vous placer votre carte ? (H/B/D/G) ");
                                scanf("%s", dirs);
                                dir = (direction) dirs[0];

                                switch (dir) {
                                    case HAUT:
                                        if (get_carte_grille(get_grille(p), y - 1, x) != NULL) {
                                            printf("Vous ne pouvez pas placer votre carte à côte de cette carte, la place est prise.\n");
                                            dir = INCONNU;
                                        } else {
                                            pos_carte.abscisse = x;
                                            pos_carte.ordonnee = y - 1;
                                            return pos_carte;
                                        }
                                        break;

                                    case BAS:
                                        if (get_carte_grille(get_grille(p), y + 1, x) != NULL) {
                                            printf("Vous ne pouvez pas placer votre carte à côte de cette carte, la place est prise.\n");
                                            dir = INCONNU;
                                        } else {
                                            pos_carte.abscisse = x;
                                            pos_carte.ordonnee = y + 1;
                                            return pos_carte;
                                        }
                                        break;

                                    case DROITE:
                                        if (get_carte_grille(get_grille(p), y, x + 1) != NULL) {
                                            printf("Vous ne pouvez pas placer votre carte à côte de cette carte, la place est prise.\n");
                                            dir = INCONNU;
                                        } else {
                                            pos_carte.abscisse = x + 1;
                                            pos_carte.ordonnee = y;
                                            return pos_carte;
                                        }
                                        break;

                                    case GAUCHE:
                                        if (get_carte_grille(get_grille(p), y, x - 1) != NULL) {
                                            printf("Vous ne pouvez pas placer votre carte à côte de cette carte, la place est prise.\n");
                                            dir = INCONNU;
                                        } else {
                                            pos_carte.abscisse = x - 1;
                                            pos_carte.ordonnee = y;
                                            return pos_carte;
                                        }
                                        break;

                                    default:
                                        break;
                                }
                            } while (dir != HAUT && dir != BAS && dir != DROITE && dir != GAUCHE);
                        }
                    }
                }
            }
        } else {
            carte_a_coller = -1;
            printf("Pas de cartes ici.\n");
        }
    } while (carte_a_coller == -1);
    return (position) {-1, -1};
}

/**
 * Une fonction pour afficher l'effet d'une carte qui vient d'être retournée face visible.
 * @param c : La carte dont on veut afficher l'effet.
 */
void afficher_effet_carte_retournee(carte c) {
    printf("L'effet de la carte %s de la faction %d est : %s \n", get_nom_carte(c), get_identifiant_faction_carte(c),
           get_effet(c));
};

/**
 * Une fonction pour afficher la faction victorieuse de la partie.
 * @param f : la faction victorieuse de la partie.
 */
void afficher_vainqueur(faction f) {
    printf("La faction victorieuse est la faction : %s", get_nom_faction(f));
}

void demander_appuyer_sur_entree(char *message, booleen flush_stdin) {
    if (flush_stdin) {
        int ch;
        do {
            ch = fgetc(stdin);
        } while (ch != EOF && ch != '\n');
    }
    clearerr(stdin);
    printf("%s\n", message);
    fflush(stdout);
    getchar();
    // On met des espaces
    for (int i = 0; i < 20; i++) {
        printf("\n");
    }
}