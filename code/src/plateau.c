#include "../headers/carte.h"
#include "../headers/faction.h"
#include "../headers/constante.h"
#include "../headers/position.h"
#include "../headers/structure.h"
#include "../headers/interface.h"
#include "../headers/effets.h"
#include <string.h>
#include <stdio.h>


/**
 * Structure correspondant à notre plateau de jeu
 */
typedef struct s_plateau {

    /**
      * pointeur vers la grille de cartes : en effet celle-ci s'occupe de la gestion du plateau
      */
    grille_carte grille;

    /**
     * tableau de pointeurs contenant un pointeur sur chaque joueur
     */
    faction *factions;

    /**
     * nombre de cartes déposées sur le plateau
     */
    int nombre_cartes_posees;

    /**
     * champs de la dernière carte retournée. En effet le plateau doit se souvenir de cette dernière carte dans le cas où celle-ci correspond à "Laurent Prevel"
     */
    carte derniere_carte_retournee;
    /**
     * champs correspondant au nombre de cartes retournées.
     */
    int nombre_cartes_retournees;
    /**
     * champ correspondant à la liste chaînée des cartes qui ont supprimées durant une manche
     * Cette liste a pour but de libérer la mémoire à la fin de chaque manche
     */
    liste_chainee_carte cartes_supprimees;
} *plateau;


plateau nouveau_plateau() {
    /*allocation de la mémoire pour notre plateau*/
    plateau p = (plateau) malloc(sizeof(struct s_plateau));
    /*initialisation des factions*/
    p->grille = initialiser_grille(NOMBRE_CARTES_MAXIMUM * 2);
    p->factions = initialiser_factions();
    p->derniere_carte_retournee = NULL;
    p->nombre_cartes_retournees = 0;
    p->nombre_cartes_posees = 0;
    p->cartes_supprimees = initialiser_liste_chainee();
    return p;
}

void liberer_plateau(plateau p) {
    if (p == NULL) {
        return;
    }
    /*libération de la mémoire pour les factions*/
    liberer_grille(p->grille);
    if (p->cartes_supprimees != NULL) {
        liberer_liste_chainee(p->cartes_supprimees);
    }
    for (int i = 0; i < NOMBRE_FACTIONS; i++) {
        free(p->factions[i]);
    }
    free(p->factions);
    free(p);
}

int initialiser_manche(plateau p) {
    int manche_gagnee; /* variable qui va contenir le nombre de manches gagnées par le joueur en question*/
    int identifiant_fac_derniere_carte; /*variable qui contiendra l'identifiant de la faction correspondant à la dernière retournée*/

    /*on vérifie que la dernière carte retournée n'est pas nulle et si la carte retournée est Laurent Prevel : en effet, le joueur qui a déposé cette carte a gagné la manche*/
    if (p->derniere_carte_retournee != NULL &&
        strcmp(get_nom_carte(p->derniere_carte_retournee), nom_cartes[Laurent_Prevel]) == 0) {
        /*identifiant de la faction qui a posé la dernière carte retournée "Laurent Prevel"*/
        identifiant_fac_derniere_carte = get_identifiant_faction_carte(p->derniere_carte_retournee);
        manche_gagnee = get_manches_gagnees(p->factions[identifiant_fac_derniere_carte]);
        /*on incrémente le nombre de manches de la faction qui a déposé la carte "Laurent Prével"*/
        set_manches_gagnees(p->factions[identifiant_fac_derniere_carte], ++manche_gagnee);
        printf("La faction %d a gagné la manche grâce à Laurent Prével \n", identifiant_fac_derniere_carte);
    } else {
        /*Permet d'incrémenter la manche en fonction du joueur gagnant*/
        /*si le joueur 1 a gagné la manche grâce à son nombre de points*/
        if (get_points_DDRS(p->factions[FACTION1]) > get_points_DDRS(p->factions[FACTION2])) {
            /*on incrémente le nombre de manches pour le joueur 1*/
            manche_gagnee = get_manches_gagnees(p->factions[FACTION1]);
            set_manches_gagnees(p->factions[FACTION1], ++manche_gagnee);
            /*si le joueur 2 a gagné la manche grâce à son nombre de points*/
            printf("La faction %d a gagné la manche grâce à ses points \n", FACTION1);
        } else if (get_points_DDRS(p->factions[FACTION1]) < get_points_DDRS(p->factions[FACTION2])) {
            /*on incrémente le nombre de manches pour le joueur 2*/
            manche_gagnee = get_manches_gagnees(p->factions[FACTION2]);
            set_manches_gagnees(p->factions[FACTION2], ++manche_gagnee);
            /* sinon si les deux joueurs ont le même nombre de points : le joueur qui a la carte la plus en haut à gauche a gagné*/
            printf("La faction %d a gagné la manche grâce à ses points \n", FACTION2);
        } else {
            int identifiant_fac_carte_plus_a_gauche;
            for (int i = get_min_x_grille(p->grille); i <= get_max_x_grille(p->grille); i++) {
                if (get_carte_grille(p->grille, get_min_y_grille(p->grille), i) != NULL) {
                    /*récupération de l'identifiant de la faction qui posé la carte la plus en haut à gauche*/
                    identifiant_fac_carte_plus_a_gauche = get_identifiant_faction_carte(
                            get_carte_grille(p->grille, get_min_y_grille(p->grille), i));
                    manche_gagnee = get_manches_gagnees(p->factions[identifiant_fac_carte_plus_a_gauche]);
                    set_manches_gagnees(p->factions[identifiant_fac_carte_plus_a_gauche], ++manche_gagnee);
                    printf("La faction %d a gagné la manche\n", identifiant_fac_carte_plus_a_gauche);
                    break;
                }
            }
        }
    }
    // On remet le nombre de points DDRS à 0
    for (int i = 0; i < NOMBRE_FACTIONS; i++) {
        set_points_DDRS(p->factions[i], 0);
        if (get_pioche(p->factions[i]) != NULL) {
            liberer_ensemble_entier(get_pioche(p->factions[i]));
        }
        if (get_main(p->factions[i]) != NULL) {
            liberer_liste_chainee(get_main(p->factions[i]));
        }
    }

    /*Sinon la partie n'est pas terminée : initialisation de la grille et de ses différents champs : min_x/max_x/min_y/max_y*/
    if (p->cartes_supprimees != NULL) {
        liberer_liste_chainee(p->cartes_supprimees);
    }
    reinitialiser_grille(p->grille);
    p->derniere_carte_retournee = NULL;
    p->nombre_cartes_retournees = 0;
    p->nombre_cartes_posees = 0;
    p->cartes_supprimees = initialiser_liste_chainee();


    /*Permet de savoir le joueur gagnant de la partie en fonction de son nombre de manches gagnées.*/
    if (get_manches_gagnees(p->factions[FACTION1]) == 2) {
        /*Le joueur 1 a gagné*/
        return FACTION1;
    } else if (get_manches_gagnees(p->factions[FACTION2]) == 2) {
        /*Le joueur 2 a gagné*/
        return FACTION2;
    }

    return -1;
}

void poser_carte(plateau p, carte c, position pos) {
    set_position(c, pos);
    poser_carte_grille(p->grille, c, pos.ordonnee, pos.abscisse);
    p->nombre_cartes_posees++;
}

carte retourner_carte(plateau p) {
    position pos = get_position_carte_haut_gauche_grille(p->grille, VRAI);
    /*si abscisse vaut -1 : les cartes ont été toutes retournées*/
    if (pos.abscisse == -1) {
        return NULL;
    }
    /*sinon, on récupère la carte en question et on la retourne en activant son effet*/
    carte carte = get_carte_grille(p->grille, pos.ordonnee, pos.abscisse);
    /*on modifie le booléan associé afin que la carte devienne visible*/
    set_est_face_cachee(carte, FAUX);

    /*on augmente de 1 le nombre de cartes retournées*/
    p->nombre_cartes_retournees++;

    afficher_effet_carte_retournee(carte);

    /*on applique l'effet de la carte : on récupère la fonction associée à la carte*/
    (get_effet_fonction(carte))(carte, p);
    /*mise à jour de la dernière carte retournée*/
    p->derniere_carte_retournee = carte;

    return carte;
}


grille_carte get_grille(plateau p) {
    return p->grille;
}

faction *get_factions(plateau p) {
    return p->factions;
}

int get_nombre_cartes_posees(plateau p) {
    return p->nombre_cartes_posees;
}

int get_nombre_cartes_retournees(plateau p) {
    return p->nombre_cartes_retournees;
}

carte get_derniere_carte_retournee(plateau p) {
    return p->derniere_carte_retournee;
}

liste_chainee_carte get_cartes_supprimees(plateau p) {
    return p->cartes_supprimees;
}

void set_grille(plateau p, grille_carte g) {
    p->grille = g;
}

void set_factions(plateau p, faction *factions) {
    free(p->factions);
    p->factions = factions;
}

void set_nombre_cartes_posees(plateau p, int nombre_cartes_posees) {
    p->nombre_cartes_posees = nombre_cartes_posees;
}

void set_derniere_carte_retournee(plateau p, carte derniere_carte_retournee) {
    p->derniere_carte_retournee = derniere_carte_retournee;
}

void set_cartes_supprimees(plateau p, liste_chainee_carte lc) {
    p->cartes_supprimees = lc;
}

char *plateau_to_string(plateau p) {
    size_t taille = 0;
    char *grille = grille_carte_to_string(p->grille);
    char *faction_1 = faction_to_string(get_factions(p)[0]);
    char *faction_2 = faction_to_string(get_factions(p)[1]);
    // On fait un snprintf afin de déterminer la taille à réserver
    taille = snprintf(NULL, taille, "PLATEAU\n%s\n%s\n%s",
                      grille,
                      faction_1,
                      faction_2);
    char *str = (char *) malloc((taille + 1) * sizeof(char));
    taille = snprintf(str, taille + 1, "PLATEAU\n%s\n%s\n%s",
                      grille,
                      faction_1,
                      faction_2);
    free(grille);
    free(faction_1);
    free(faction_2);
    return str;
}