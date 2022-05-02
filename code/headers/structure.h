/**
 * @file structure.h
 * @brief Fichier contenant les différentes structures nécessaires au bon fonctionnement de notre jeu
 */
#ifndef ORIIEFLAMME_GR_11_STRUCTURE_H
#define ORIIEFLAMME_GR_11_STRUCTURE_H

#include "carte.h"
#include "position.h"
#include "constante.h"


/**
 * Structure qui correspond à la grille qui va contenir les cartes posées
 */
typedef struct s_grille_carte *grille_carte;

/**
 * Initialise une grille de cartes de la taille passée en paramètre
 * @param taille_grille la taille de la grille que l'on veut créer
 * @return la grille initialisée
 */
grille_carte initialiser_grille(int taille_grille);

/**
 * Retire toutes les cartes de la grille en libérant leur mémoire associée
 * Remet la valeur de de min_x, min_y, max_x, max_y à la valeur par défaut
 * @param g la grille que l'on veut réinitialiser
 */
void reinitialiser_grille(grille_carte g);

/**
 * Libère la mémoire de la grille passée en paramètre
 * @param g la grille dont on veut libérer la mémoire
 */
void liberer_grille(grille_carte g);

/**
 * Pose la carte passée en paramètre sur la grille passée en paramètre
 * aux coordonnées y,x
 * @param g la grille sur laquelle on veut poser la carte
 * @param c la carte que l'on veut poser
 * @param y l'ordonnée où l'on veut mettre la carte
 * @param x l'abscisse où l'on veut mettre la carte
 * @return VRAI si la carte a pu être posée, FAUX sinon
 */
booleen poser_carte_grille(grille_carte g, carte c, int y, int x);

/**
 * Renvoie la carte de la grille à l'abscisse et l'ordonnée passée en paramètre
 * @param g la grille dont on veut récupérer la carte
 * @param y l'ordonnée de la carte
 * @param x l'abscisse de la carte
 * @return renvoie le pointeur vers la carte située à l'abscisse et l'ordonnée passée en paramètre, renvoie NULL
 * si les coordonnées sont trop élevées pour la grille
 */
carte get_carte_grille(grille_carte g, int y, int x);

/**
 * Renvoie la carte de la grille à l'abscisse et l'ordonnée passée en paramètre et la retire de la grille
 * sans la libérer de la mémoire
 * @param g la grille où l'on veut supprimer la carte
 * @param y l'ordonnée de la carte que l'on veut supprimer
 * @param x l'abscisse de la carte que l'on veut supprimer
 * @return renvoie le pointeur vers la carte située à l'abscisse et l'ordonnée passée en paramètre, renvoie NULL
 * si les coordonnées sont trop élevées pour la grille
 */
carte supprimer_carte_grille(grille_carte g, int y, int x);

/**
 * Renvoie la taille de la grille
 * @param g la grille dont on veut obtenir l'information
 * @return la taille de la grille
 */
int get_taille_grille(grille_carte g);

/**
 * Renvoie l'abscisse de la carte la plus à gauche de la grille
 * @param g la grille dont on veut obtenir l'information
 * @return l'abscisse de la carte la plus à gauche la grille
 */
int get_min_x_grille(grille_carte g);

/**
 * Renvoie l'abscisse de la carte la plus à droite de la grille
 * @param g la grille dont on veut obtenir l'information
 * @return l'abscisse de la carte la plus à droite de la grille
 */
int get_max_x_grille(grille_carte g);

/**
 * Renvoie l'ordonnée de la carte la plus en haut de la grille
 * @param g la grille dont on veut obtenir l'information
 * @return l'ordonnée de la carte la plus en haut de la grille
 */
int get_min_y_grille(grille_carte g);

/**
 * Renvoie l'ordonnée de la carte la plus en bas de la grille
 * @param g la grille dont on veut obtenir l'information
 * @return l'ordonnée de la carte la plus en bas de la grille
 */
int get_max_y_grille(grille_carte g);

/**
 * Renvoie la position de la carte non retournée la plus en haut à gauche de la grille
 * de carté passée en paramètre qui peut être soit non retourné, soit retourné selon qu'on veuille qu'elle soit face
 * cachée ou non
 * @param g la grille dont on veut récupérer l'information
 * @param veut_face_cachee vaut vrai si on veut la dernière carte en haut à gauche non retournée
 * @return {-1,-1} s'il n'y a pas de cartes non retournées dans la grille, la position de la carte non
 * retournée la plus en haut à gauche sinon
 */
position get_position_carte_haut_gauche_grille(grille_carte g, booleen veut_face_cachee);


/**
 * Structure qui correspond à une liste chaînée de cartes. Nous l'utiliserons pour gérer la main de
 * nos factions
 */
typedef struct s_liste_chainee_carte *liste_chainee_carte;

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
void ajouter_tete_liste_chainee(liste_chainee_carte *l, carte c);

/**
 * Supprime la carte à l'indice passée en paramètre
 * @param l la liste à laquelle on veut supprimer notre carte
 * @return la liste avec la carte supprimée
 */
carte supprimer_carte_liste_chainee(liste_chainee_carte* l, int indice_carte) ;

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
 * Structure qui correspond à un ensemble d'entiers. Nous l'utiliserons pour savoir
 * les indices des cartes que l'utilisateur doit piocher parmi la liste des cartes possibles (pioche).
 * Dans un ensemble, chaque élément ne peut être présent qu'une fois.
 */
typedef struct s_ensemble_entier *ensemble_entier;

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
