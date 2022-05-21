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
#include <stdlib.h>
#include <string.h>
#include "structure.h"


/**
 * Structure correspondant à notre plateau de jeu
 */
typedef struct s_plateau *plateau;

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
 * une fonction pour permettre à une faction de poser une carte face cachée sur le plateau
 * @param p pointeur sur le plateau
 * @param f pointeur la faction possédant la carte
 * @param c carte à déposer par la faction
 * @param pos position de la carte
 */
void poser_carte(plateau p, carte c, position pos);

/**
 * une fonction pour retourner la carte la plus en haut à gauche face visible et activer son effet
 * @param p pointeur sur le plateau
 * @return carte : pointeur sur la carte à renvoyer, et renvoi null s'il n'y a plus de carte à retourner
 */
carte retourner_carte(plateau p);

/**
 * Fonction permettant de recupérer la grille du plateau.
 * @param p : pointeur sur le plateau dont on veut récuperer la grille.
 * @return tableau 2D de carte représentant la grille du plateau.
 */
grille_carte get_grille(plateau p);

/**
 * Fonction permettant de recupérer les factions du plateau.
 * @param p : pointeur sur le plateau dont on veut récuperer les factions.
 * @return tableau 1D de faction représentant les factions du plateau.
 */
faction *get_factions(plateau p);

/**
 * Fonction permettant de recupérer le nombre_cartes_posees du plateau.
 * @param p : pointeur sur le plateau dont on veut récuperer le nombre_cartes_posees.
 * @return entier représentant le nombre_cartes_posees du plateau.
 */
int get_nombre_cartes_posees(plateau p);

/**
 * Fonction permettant de recupérer le nombre_cartes_retournees du plateau.
 * @param p : pointeur sur le plateau dont on veut récuperer le nombre_cartes_retournees.
 * @return entier représentant le nombre_cartes_retournees du plateau.
 */
int get_nombre_cartes_retournees(plateau p);

/**
 * Fonction permettant de recupérer le max_x du plateau.
 * @param p : pointeur sur le plateau dont on veut récuperer le max_x.
 * @return entier représentant le max_x du plateau.
 */
carte get_derniere_carte_retournee(plateau p);

/**
 * Fonction permettant de récupérer le nombre de cartes retournées sur le plateau
 * @param p : pointeur sur le plateau dont on veut récupérer l'information
 * @return entier représentant le nombre de carte retournées
 */
int get_nombre_cartes_retournees(plateau p);

/**
 * Fonction permettant de récupérer la liste chainée des cartes supprimées durant une manche.
 * @param p : pointeur sur le plateau dont on veut récupérer l'information
 * @return la liste des cartes supprimées durant la manche
 */
liste_chainee_carte get_cartes_supprimees(plateau p);

/**
 * Fonction permettant de changer la grille du plateau.
 * @param p : pointeur sur le plateau dont on veut changer sa grille.
 * @param grille : tableau 2D de carte que l'on va associer à la grille du plateau.
 */
void set_grille(plateau p, grille_carte g);

/**
 * Fonction permettant de changer les factions du plateau.
 * @param p : pointeur sur le plateau dont on veut changer ses factions.
 * @param factions : tableau 1D de faction que l'on va associer aux factions du plateau.
 */
void set_factions(plateau p, faction *factions);

/**
 * Fonction permettant de changer le nombre_cartes_posees du plateau.
 * @param p : pointeur sur le plateau dont on veut changer son nombre_cartes_posees.
 * @param nombre_cartes_posees : entier que l'on va associer au nombre_cartes_posees du plateau.
 */
void set_nombre_cartes_posees(plateau p, int nombre_cartes_posees);

/**
 * Fonction permettant de changer la derniere_carte_retournee du plateau.
 * @param p : pointeur sur le plateau dont on veut changer sa derniere_carte_retournee.
 * @param derniere_carte_retournee : carte que l'on va associer à la derniere_carte_retournee du plateau.
 */
void set_derniere_carte_retournee(plateau p, carte derniere_carte_retournee);

/**
 * Fonction permettant de changer la liste_chainee_carte du plateau
 * @param p : pointeur sur le plateau dont on veut changer sa liste_chainee
 * @param lc : la liste de la nouvelle carte
 */
void set_cartes_supprimees(plateau p, liste_chainee_carte lc);

/**
 * Fonction transformant le plateau en chaîne de caractères
 * @param p le plateau dont on veut obtenir la chaîne de caractères
 * @return renvoie une chaîne de caractères de la forme: "PLATEAU\ngrille\nfaction_1\nfaction_2"
 */
char *plateau_to_string(plateau p);

#endif //ORIIEFLAMME_GR_11_PLATEAU_H
