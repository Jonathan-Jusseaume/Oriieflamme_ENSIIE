/**
 * @file structure.h
 * @brief Fichier contenant les différentes structures nécessaires au bon fonctionnement de notre jeu
 */
#ifndef ORIIEFLAMME_GR_11_STRUCTURE_H
#define ORIIEFLAMME_GR_11_STRUCTURE_H

#include "carte.h"
#include "constante.h"

/**
 * Structure qui correspond à une liste chainee de cartes. Nous l'utiliserons pour gérer la main de
 * nos factions
 */
typedef struct s_liste_chainee_carte *liste_chainee_carte;

/**
 * Fonction qui permet d'initialiser la liste chainee des cartes
 * @return un pointeur vers cette liste chainee
 */
liste_chainee_carte initialiser_liste_chainee();

/**
 * Permet d'ajouter en tete de la liste chainée des cartes, la carte passée
 * en paramètre
 * @param l la liste à laquelle on veut ajouter notre carte
 * @param c la carte que l'on veut ajouter à notre liste
 */
void ajouter_tete_liste_chainee(liste_chainee_carte l, carte c);

/**
 * Supprime la carte à l'indice passée en paramètre, et la renvoie
 * @param l la liste à laquelle on veut supprimer notre carte
 * @param indice_carte l'indice de la carte que l'on veut supprimer
 * @return la carte supprimée ou NULL si l'indice passée en paramètre est trop élevé
 */
carte supprimer_carte_liste_chainee(liste_chainee_carte l, int indice_carte);

/**
 * Renvoie la taille de la liste chainee passée en paramètre
 * @param l la liste chainée dont on veut connaître la date
 * @return la taille de la liste
 */
int taille_liste_chainee(liste_chainee_carte l);

/**
 * Renvoie la carte à l'indice passée en paramètre
 * @param l la liste dont on veut obtenir un indice
 * @param indice_carte l'indice de la carte que l'on obtenir
 * @return la carte à l'indice passée en paramètre ou NULL si l'indice passée en paramètre est trop élevé
 */
carte get_carte_liste_chainee(liste_chainee_carte l, int indice_carte);

/**
 * Permet de vérifier si la liste est vide ou non
 * @param l la liste dont on veut savoir si elle est vide ou non
 * @return VRAI si la liste est vide, FAUX sinon
 */
booleen liste_chainee_est_vide(liste_chainee_carte l);


#endif //ORIIEFLAMME_GR_11_STRUCTURE_H
