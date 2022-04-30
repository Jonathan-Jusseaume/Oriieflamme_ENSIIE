#include "../headers/constante.h"
#include "../headers/faction.h"

/**
 * Structure représentant une faction.
 */
typedef struct s_faction {
    /**
     * Chaîne de caractère représentant le nom de la faction.
     */
    char *nom;
    /**
     * Entier représentant l'identifiant de la faction.
     */
    int identifiant_faction;
    /**
     * Entier représentant les points DDRS de la faction.
     */
    int points_DDRS;
    /**
     * Entier représentant les manches gagnées par la faction.
     */
    int manches_gagnees;
    /**
     *  Booléen qui vaut VRAI si la faction a déjà remélangé sa main, et FAUX sinon.
     */
    booleen a_remelanger;
    /**
     * Pointeur vers un Set représentant les cartes dans la pioche de la faction.
     */
    ensemble_entier pioche;
    /**
     * Pointeur vers une liste chainée représentant les cartes dans la main de la faction.
     */
    liste_chainee_carte main;
} *faction;

/**
 * Fonction qui utilise la technique de l'effectif cumule pour pouvoir retourner l'indice correspondant au nom de la carte associée
 * @param indice_ensemble : indice ne prenant pas en compte le nombre d'occurrences d'une carte obtenu
 * @return indice : indice correspondant au nom de la carte
 */
int indice_liste_carte(int indice_ensemble);

faction *initialiser_factions() {
    /*allocation dynamique de la mémoire pour la première dimension*/
    faction *f = (faction *) malloc(NOMBRE_FACTIONS * sizeof(faction));
    for (int i = 0; i < NOMBRE_FACTIONS; i++) {
        /*allocation dynamique de la mémoire pour la deuxième dimension*/
        f[i] = (faction) malloc(sizeof(struct s_faction));
        /*initalisation des champs pour la faction en question*/
        f[i]->manches_gagnees = 0;
        f[i]->identifiant_faction = i;
        f[i]->points_DDRS = 0;
        f[i]->a_remelanger = FAUX;
        f[i]->main = NULL;
        f[i]->pioche = NULL;
    }
    /*initialisation des champs suivants*/
    f[0]->nom = "joueur1";
    f[1]->nom = "joueur2";

    return f;
}

booleen a_remelanger(faction f) {
    /*permet de savoir si l'option pour remélanger a été utilisé*/
    return f->a_remelanger;
}

void melanger_pioche(faction f) {
    int indice_hasard = 0;
    /*création de l'ensemble où l'on va stocker nos indices*/
    f->pioche = creer_ensemble_entier();
    /*permet d'obtenir 8 indices entre 0 et 46 afin de mélanger la pioche*/
    while (get_taille_ensemble_entier(f->pioche) != NOMBRE_CARTES_MAIN) {
        indice_hasard = rand() % NOMBRE_CARTES_TOTALES;
        ajouter_ensemble_entier(f->pioche, indice_hasard);
    }
}

void remelanger(faction f) {
    /*Permet d'indiquer que la faction f a remélangée sa main*/
    f->a_remelanger = VRAI;
}

void vider_main_dans_pioche(faction f) {
    /*libération de la main et de l'ensemble d'entier(permettant de peupler la main)*/
    liberer_liste_chainee(f->main);
    liberer_ensemble_entier(f->pioche);
}

void repioche(faction f) {
    /*variable qui contiendra l'indice obtenu dans la liste de carte*/
    int indice_carte;
    /*on vide la main de la faction en question dans la pioche*/
    vider_main_dans_pioche(f);
    /*on mélange la pioche de la faction enq question*/
    melanger_pioche(f);
    f->main = initialiser_liste_chainee();

    for (int i = 0; i < get_taille_ensemble_entier(f->pioche); i++) {
        indice_carte = indice_liste_carte(get_valeur_indice_ensemble_entier(f->pioche, i));
        /*pointeur sur une carte initialisée : on initialise la carte avec les informations nécessaires en particulier son nom qui sera récupéré grâce à l'indice de l'ensemble*/
        carte c = initialiser_carte(nom_cartes[indice_carte],
                                    effets_description[indice_carte], effets[indice_carte], f->identifiant_faction, -1,
                                    FAUX);
        /*ajout de la carte en question dans la main*/
        ajouter_tete_liste_chainee(f->main, c);
    }
}

int indice_liste_carte(int indice_ensemble) {
    int effectif_cumule = 0;

    for (int i = 0; i < TAILLE_NOMBRE_OCCURRENCES; i++) {
        effectif_cumule = effectif_cumule + nombre_occurrences[i];
        /*on retourne un indice correspondant à notre liste de carte(et surtout qui prend en compte son nombre d'occurrences)
         lorsque l'indice de l'ensemble est supérieure à la somme cumulée des occurrences de chaque carte(de 0 à l'indice i)*/
        if (effectif_cumule >= indice_ensemble) {
            return i;
        }
    }
    return -1;
}

char *get_nom_faction(faction f) {
    return f->nom;
}

int get_identifiant_faction(faction f) {
    return f->identifiant_faction;
}

int get_points_DDRS(faction f) {
    return f->points_DDRS;
}

int get_manches_gagnees(faction f) {
    return f->manches_gagnees;
}

booleen get_a_remelanger(faction f) {
    return f->a_remelanger;
}

ensemble_entier get_pioche(faction f) {
    return f->pioche;
}

liste_chainee_carte get_main(faction f) {
    return f->main;
}

void set_nom_faction(faction f, char *nom) {
    f->nom = nom;
}

void set_identifiant_faction(faction f, int identifiant_faction) {
    f->identifiant_faction = identifiant_faction;
}

void set_points_DDRS(faction f, int points_DDRS) {
    f->points_DDRS = points_DDRS;
}

void set_manches_gagnees(faction f, int manches_gagnees) {
    f->manches_gagnees = manches_gagnees;
}

void set_a_remelanger(faction f, booleen a_remelanger) {
    f->a_remelanger = a_remelanger;
}

void set_pioche(faction f, ensemble_entier pioche) {
    f->pioche = pioche;
}

void set_main(faction f, liste_chainee_carte main) {
    f->main = main;
}