/**
 * @file interface.h
 * @brief Fichier qui contient les fonctions faisant appel à des interactions utilisateurs
 * et à des affichages
 */
#ifndef ORIIEFLAMME_GR_11_INTERFACE_H
#define ORIIEFLAMME_GR_11_INTERFACE_H

#include "faction.h"
#include "plateau.h"
#include "carte.h"
#include "constante.h"

/**
 * Une fonction pour afficher le plateau de jeu.
 * @param p : le plateau de jeu à afficher.
 */
void afficher_plateau(plateau p);

/**
 * Une fonction pour afficher la main d'une faction.
 * @param f : La faction dont on va afficher la main.
 */
void afficher_main_faction(faction f);

/**
 * Une fonction pour demander à une faction si elle veut renouveller sa main.
 * @param f : la faction à laquelle on va demander si elle veut renouveller sa main.
 * @return booleen : VRAI si la faction veut vider sa main, mélanger sa pioche et repiocher, FAUX sinon.
 */
booleen demander_renouvellement_main(faction f);

/**
 * Une fonction pour demander à une faction quelle carte de sa main elle veut poser face cachée.
 * @param f : la faction à laquelle on va demander quelle carte de sa main elle veut poser face cachée.
 * @return carte : la carte que la faction veut poser face cachée.
 */
carte demander_carte_poser_face_cachee(faction f);

/**
 * Une fonction pour demander à une faction à quelle position elle veut poser sa carte face cachée qu'elle a choisie précédemment,
 * et faire des vérifications sur cette position choisie.
 * @param p : Le plateau de jeu sur lequel on va faire des vérifications pour la position choisie.
 * @param f : La faction à laquelle on va demander à quelle position elle veut poser sa carte.
 * @param c : La carte que l'on veut poser à une position que la faction va choisir.
 * @return position : Position en abscisse et en ordonnée de la carte à poser, calculée à partir des entrées de l'utilisateur.
 */
position demander_position_poser_carte(plateau p, faction f, carte c);

/**
 * Une fonction pour afficher l'effet d'une carte qui vient d'être retournée face visible.
 * @param c : La carte dont on veut afficher l'effet.
 */
void afficher_effet_carte_retournee(carte c);

/**
 * Une fonction pour afficher la faction victorieuse de la partie.
 * @param f : la faction victorieuse de la partie.
 */
void afficher_vainqueur(faction f);

#endif //ORIIEFLAMME_GR_11_INTERFACE_H
