
#ifndef ORIIEFLAMME_GR_11_PLATEAU_H
#define ORIIEFLAMME_GR_11_PLATEAU_H


#include "carte.h"
#include "faction.h"
#include "plateau.h"

typedef struct s_plateau *plateau


/**
 * une fonction pour créer un nouveau plateau (et les deux factions qui joueront dessus)
 * @return plateau : pointeur sur le plateau créer
 */
plateau nouveau_plateau();


/**
 *une fonction pour libérer la mémoire associée à un plateau(et ses deux factions)
 * @param p : pointeur sur le plateau
 */
void liberer_plateau(plateau p);


/**
 * une fonction pour initialiser une nouvelle manche du jeu, ou, le cas échéant, indiquer que le jeu est terminé
 * @param p : pointeur sur le plateau
 */
void initialiser(plateau p);


/**
 * une fonction qui renvoie la liste des deux factions du jeu
 * @return pointeur sur la table des factions
 */
faction *get_factions();

/**
 *une fonction pour permettre à une faction de poser une carte face cachée sur le plateau
 * @param p pointeur sur le plateau
 * @param f pointeur la faction possédant la carte
 * @param c carte à déposer par la faction
 */
void poser_carte(plateau p, faction f, carte c);


/**
 * une fonction pour retourner une carte face visible et activer son effet
 * @param p pointeur sur le plateau
 * @param f pointeur sur la faction
 * @param c pointeur sur la carte
 */

void retourner_carte(plateau p, faction f, carte c);


#endif //ORIIEFLAMME_GR_11_PLATEAU_H



