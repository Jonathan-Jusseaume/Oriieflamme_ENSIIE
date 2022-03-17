
#ifndef ORIIEFLAMME_GR_11_INTERFACE_H
#define ORIIEFLAMME_GR_11_INTERFACE_H

#include "faction.h"
#include "plateau.h"
#include "carte.h"
#include "constante.h"

/**
 * Une fonction pour afficher le plateau de jeu.
 */
void afficher_plateau();

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
carte demander_quelle_carte_poser_face_cachee(faction f);

/**
 * Une fonction pour demander à une faction à quelle position elle veut poser sa carte face cachée qu'elle a choisie précédemment.
 * @param f : la faction à laquelle on va demander à quelle position elle veut poser sa carte.
 * @param c : la carte que l'on veut poser à une position que la faction va choisir.
 */
void demander_quelle_position_poser_carte(faction f, carte c);

/**
 * Une fonction pour afficher l'effet d'une carte qui vient d'être retournée face visible.
 * @param c : la carte dont on veut afficher l'effet.
 */
void afficher_effet_carte_retournee(carte c);

/**
 * Une fonction pour afficher l'effet d'une carte qui vient d'être retournée face visible.
 * @param f : la faction victorieuse.
 */
void afficher_vainqueur_partie(faction f);

#endif //ORIIEFLAMME_GR_11_INTERFACE_H
