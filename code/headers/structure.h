/**
 * @file structure.h
 * @brief Fichier contenant les différentes structures nécessaires au bon fonctionnement de notre jeu
 */
#ifndef ORIIEFLAMME_GR_11_STRUCTURE_H
#define ORIIEFLAMME_GR_11_STRUCTURE_H

#include "carte.h"
#include "constante.h"


/**
 * Structure qui correspond à une liste chaînée de cartes. Nous l'utiliserons pour gérer la main de
 * nos factions
 */
typedef struct s_liste_chainee_carte *liste_chainee_carte;

/**
 * Structure qui correspond à un ensemble d'entiers. Nous l'utiliserons pour savoir
 * les indices des cartes que l'utilisateur doit piocher parmi la liste des cartes possibles (pioche).
 * Dans un ensemble, chaque élément ne peut être présent qu'une fois.
 */
typedef struct s_ensemble_entier *ensemble_entier;

/**
 * Fonction qui permet d'initialiser la liste chaînée des cartes
 * @return un pointeur vers cette liste chaînée
 */
liste_chainee_carte initialiser_liste_chainee();

/**
 * Permet d'ajouter en tete de la liste chaînée des cartes, la carte passée
 * en paramètre
 * @param l la liste à laquelle on veut ajouter notre carte
 * @param c la carte que l'on veut ajouter à notre liste
 * @return Retourne la liste chaînée avec la carte ajoutée en tête
 */
liste_chainee_carte ajouter_tete_liste_chainee(liste_chainee_carte l, carte c);

/**
 * Supprime la carte à l'indice passée en paramètre, et la renvoie
 * @param l la liste à laquelle on veut supprimer notre carte
 * @param indice_carte l'indice de la carte que l'on veut supprimer
 * @return la carte supprimée ou NULL si l'indice passée en paramètre est trop élevé
 */
carte supprimer_carte_liste_chainee(liste_chainee_carte l, int indice_carte);

/**
 * Renvoie la taille de la liste chainee passée en paramètre
 * @param l la liste chainée dont on veut connaître la taille
 * @return la taille de la liste
 */
int taille_liste_chainee(liste_chainee_carte l);

/**
 * Renvoie la carte à l'indice passée en paramètre
 * @param l la liste dont on veut obtenir un indice
 * @param indice_carte l'indice de la carte que l'on veut obtenir
 * @return la carte à l'indice passée en paramètre ou NULL si l'indice passée en paramètre est en dehors de la liste
 */
carte get_carte_liste_chainee(liste_chainee_carte l, int indice_carte);

/**
 * Permet de vérifier si la liste est vide ou non
 * @param l la liste dont on veut savoir si elle est vide ou non
 * @return VRAI si la liste est vide, FAUX sinon
 */
booleen liste_chainee_est_vide(liste_chainee_carte l);

/**
 * Renvoie la valeur de la tête de la chaine passée en paramètre
 * @param l la chaine dont on veut la tete
 * @return NULL s'il y a pas de tete, la carte sinon
 */
carte get_valeur_tete_liste_chainee(liste_chainee_carte l);

/**
 * Renvoie la queue de la liste chaînée passée en paramètre
 * @param l la liste chainée dont veut la queue
 * @return la queue de la liste chainée, NULL si la liste passée en paramètre est vide
 */
liste_chainee_carte get_queue_liste_chainee(liste_chainee_carte l);

/**
 * Libère la mémoire de la liste chainée passée en paramètre
 * @param l la liste que l'on veut libérer
 */
void liberer_liste_chainee(liste_chainee_carte l);

/**
 * Permet de créer un ensemble d'entiers
 * @return l'ensemble des entiers
 */
ensemble_entier creer_ensemble_entier();

/**
 * Ajoute l'entier à l'ensemble passé en paramètre
 * @param ee l'ensemble auquel on ajoute la valeur
 * @param valeur la valeur que l'on veut ajouter
 * @return VRAI si la valeur a été ajoutée, FAUX sinon
 */
booleen ajouter_ensemble_entier(ensemble_entier ee, int valeur);

/**
 * Vérifie si la valeur passée en paramètre appartient à l'ensemble
 * passé en paramètre
 * @param ee l'ensemble dans lequel on veut vérifier la valeur
 * @param valeur la valeur dont on veut vérifier la présence
 * @return VRAI si l'ensemble contient la valeur, FAUX si l'ensemble ne contient pas la valeur
 */
booleen contient_ensemble_entier(ensemble_entier ee, int valeur);

/**
 * Renvoie la valeur contenue dans l'ensemble d'entiers à l'indice passé en paramètre
 * @param ee l'ensemble d'entiers dans lequel on veut la valeur
 * @param indice l'indice auquel on veut la valeur
 * @return -1 si l'indice est trop grand (on assume que cet ensemble ne contiendra que des nombres positifs),
 * la valeur à l'indice sinon
 */
int get_valeur_indice_ensemble_entier(ensemble_entier ee, int indice);

/**
 * Renvoie la taille de l'ensemble d'entiers passé en paramètre
 * @param ee l'ensemble d'entiers dont on veut la taille
 * @return la taille
 */
int get_taille_ensemble_entier(ensemble_entier ee);

/**
 * Libérer le pointeur de l'ensemble d'entiers passé en paramètre
 * @param ee l'ensemble d'entiers que l'on va libérer
 */
void liberer_ensemble_entier(ensemble_entier ee);


#endif //ORIIEFLAMME_GR_11_STRUCTURE_H
