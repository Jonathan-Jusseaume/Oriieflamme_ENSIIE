/**
 * @file plateau.h
 * @brief Fichier contenant la structure et les fonctions liées à notre plateau de jeu
 */
#ifndef ORIIEFLAMME_GR_11_PLATEAU_H
#define ORIIEFLAMME_GR_11_PLATEAU_H


#include "carte.h"
#include "faction.h"
#include "constante.h"
#include "position.h"


/**
 * Structure correspondant à notre plateau de jeu
 */
typedef struct s_plateau {

    /**
     * tableau de pointeurs statiques contenant les cartes déposées par les factions
     */
    carte grille[NOMBRE_CARTES_MAXIMUM * 2][NOMBRE_CARTES_MAXIMUM * 2];

    /**
     * tableau de pointeurs contenant un pointeur sur chaque joueur
     */
    faction* factions;

    /**
     * nombre de cartes déposées sur le plateau
     */
    int nombre_cartes_posees;

    /**
    * abscisse de la carte la plus à gauche
    */
    int min_x;

    /**
    * abscisse de la carte la plus à droite
    */
    int max_x;

    /**
     * ordonnée de la carte la plus en haut
     */
    int min_y;

    /**
     *ordonnée de la carte la plus en bas
     */
    int max_y;

    /**
     * champs de la dernière carte retournée. En effet le plateau doit se souvenir de cette dernière carte dans le cas où celle-ci correspond à "Laurent Prevel"
     */
    carte derniere_carte_retournee;


} *plateau;

/**
 * Une fonction pour créer un nouveau plateau (et les deux factions qui joueront dessus)
 * @return plateau : pointeur sur le plateau créer
 */
plateau nouveau_plateau();


/**
 * une fonction pour libérer la mémoire associée à un plateau (et ses deux factions)
 * @param p : pointeur sur le plateau
 */
void liberer_plateau(plateau p);


/**
 * une fonction pour initialiser une nouvelle manche du jeu, ou, le cas échéant, indiquer que la partie est terminée
 * @param p : pointeur sur le plateau
 * @return int : -1 si la partie n'est pas terminée, 0 si le joueur1 a gagné, 1 si le joueur2 a gagné
 */
int initialiser_manche(plateau p);


/**
 * une fonction qui renvoie la liste des deux factions du jeu
 * @param p pointeur sur le plateau
 * @return faction : liste des deux factions
 */
faction* get_factions(plateau p);


/**
 * une fonction pour permettre à une faction de poser une carte face cachée sur le plateau
 * @param p pointeur sur le plateau
 * @param f pointeur la faction possédant la carte
 * @param c carte à déposer par la faction
 * @param pos position de la carte
 */
void poser_carte(plateau p, faction f, carte c, position pos);


/**
 * une fonction pour retourner la carte la plus en haut à gauche face visible et activer son effet
 * @param p pointeur sur le plateau
 * @return carte : pointeur sur la carte à renvoyer, et renvoi null s'il n'y a plus de carte à retourner
 */
carte retourner_carte(plateau p);

#endif //ORIIEFLAMME_GR_11_PLATEAU_H
