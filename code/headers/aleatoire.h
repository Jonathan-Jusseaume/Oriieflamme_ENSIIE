/**
 * @file aleatoire.h
 * @brief Fichier contenant les fonctions générant de l'aléatoire dans notre jeu
 */
#ifndef ORIIEFLAMME_GR_11_RANDOM_H
#define ORIIEFLAMME_GR_11_RANDOM_H

/**
 * Fonction renvoyant un tableau de taille 3 contenant les indices
 * de faction jouant en premier pour chaque manche
 * @return un tableau de taille qui a les indices de faction débutant à chaque manche
 */
int *generer_ordre_partie();

#endif //ORIIEFLAMME_GR_11_RANDOM_H
