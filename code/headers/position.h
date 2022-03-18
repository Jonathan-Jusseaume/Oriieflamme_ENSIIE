/**
 * @file position.h
 * @brief Fichier contenant la structure liée à la position de la carte sur la grille
 */
#ifndef ORIIEFLAMME_GR_11_POSITION_H
#define ORIIEFLAMME_GR_11_POSITION_H


/**
 * structure correspondant à la position de la carte qui va être placée sur la grille
 */
typedef struct position {
    /**
     * abscisse de la carte qui va être posée sur la grille
     */
    int abscisse;

    /**
     * ordonnée de la carte qui va être posée sur la grille
     */
    int ordonnee;

}position;

#endif //ORIIEFLAMME_GR_11_POSITION_H


