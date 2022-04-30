/**
 * @file constante.h
 * @brief Fichier contenant différentes constantes qui seront utiles pour l'application
 */
#ifndef ORIIEFLAMME_GR_11_CONSTANTE_H
#define ORIIEFLAMME_GR_11_CONSTANTE_H
#define NOMBRE_CARTES_MAXIMUM 16
#define NOMBRE_FACTIONS 2
#define NOMBRE_CARTES_MAIN 8
#define NOMBRE_CARTES_TOTALES 47
#define TAILLE_NOMBRE_OCCURRENCES 32
#define FACTION1 0
#define FACTION2 1
#include "effets.h"

/**
 * Enumération contenant les valeurs booléenes VRAI et FAUX valant respectivement 1 et 0
 */
typedef enum booleen {
    FAUX = 0, VRAI = 1
} booleen;

/**
 * Enumération pour la direction de la carte à placer
 */
typedef enum direction {
    NORD, SUD, EST, OUEST
} direction;

/**
 * Enumération contenant les noms des différentes cartes
 */
enum cartes {
    FISE,
    FISA,
    FC,
    EcologIIE,
    lIIEns,
    Soiree_sans_alcool,
    Alcool,
    Cafe,
    The,
    Ecocup,
    Reprographie,
    Isolation_du_batiment,
    Parcours_sobriete_numerique,
    Heures_supplementaires,
    Kahina_Bouchama,
    Kevin_Goilard,
    Massinissa_Merabet,
    Vitera_Y,
    Jonas_Senizergues,
    Fetia_Bannour,
    Catherine_Dubois,
    Anne_Laure_Ligozat,
    Guillaume_Burel,
    Christophe_Mouilleron,
    Thomas_Lim,
    Julien_Forest,
    Dimitri_Watel,
    Djibril_Aurelien_Dembele_Cabot,
    Eric_Lejeune,
    Lucienne_Pacave,
    Katrin_Salhab,
    Laurent_Prevel
};

/*
 * Tableau statique constant contenant le nombre d'occurrences de chaque carte
 */
static const int nombre_occurrences[] = {4, 4, 4, 2, 2, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                         1, 1,
                                         1, 1, 1, 1};
/**
 * Tableau de chaine de caractère contenant les noms des cartes
 */
static char *nom_cartes[] = {
        "FISE",
        "FISA",
        "FC",
        "EcologIIE",
        "lIIEns",
        "Soiree sans alcool",
        "Alcool",
        "Cafe",
        "The",
        "Ecocup",
        "Reprographie",
        "Isolation_du_batiment",
        "Parcours sobriete numerique",
        "Heures supplementaires",
        "Kahina Bouchama",
        "Kevin Goilard",
        "Massinissa Merabet",
        "Vitera Y",
        "Jonas Senizergues",
        "Fetia Bannour",
        "Catherine Dubois",
        "Anne Laure Ligozat",
        "Guillaume Burel",
        "Christophe Mouilleron",
        "Thomas Lim",
        "Julien Forest",
        "Dimitri Watel",
        "Djibril Aurelien Dembele Cabot",
        "Eric Lejeune",
        "Lucienne Pacave",
        "Katrin Salhab",
        "Laurent Prevel"
};
/**
 * Tableau de pointeurs sur les différentes fonctions
 */

static void *effets[] = {
        fise,
        fisa,
        fc,
        ecologiie,
        liiens,
        soiree_sans_alcool,
        alcool,
        cafe,
        the,
        ecocup,
        reprographie,
        isolation_batiment,
        parcours_sobriete_numerique,
        heures_supplementaires,
        kahina_bouchama,
        kevin_goilard,
        massinissa_merabet,
        vitera_y,
        jonas_senizergues,
        fetia_bannour,
        catherine_dubois,
        anne_laure_ligozat,
        guillaume_burel,
        christophe_mouilleron,
        thomas_lim,
        julien_forest,
        dimitri_watel,
        djibril_aurelien_dembele_cabot,
        eric_lejeune,
        lucienne_pacave,
        katrin_salhab,
        laurent_prevel
};

/**
 * Tableau de chaine de caractère contenant les différents effets
 */
static char *effets_description[] = {
        "La faction qui a posé cette carte gagne 1 point DDRS.",
        "La faction qui a posé cette carte gagne 2 points DDRS si le nombre de cartes retournées sur le plateau (y compris celle-ci) est pair, et 0 sinon.",
        "La faction qui a posé cette carte gagne 4 points DDRS si au moins une autre carte FC est retournée sur le plateau et 0 sinon",
        "La faction qui a posé cette carte gagne 1 point DDRS par carte FISE/FISA/FC retournée.",
        "Prenez toutes les cartes FISE/FISA/FC retournées, retirez les du plateau, mélangez les et reposez les face cachées une par une sur la gauche de la carte la plus en haut à gauche du plateau, dans cet ordre. Les prochaines cartes à être retournées sont ces cartes là.",
        "Si au moins une carte alcool est retournée, supprimez toutes les cartes FISE/FISA/FC retournées du plateau. Supprimez ensuite la première et la dernière ligne du plateau. Sinon la faction qui a posé cette carte gagne 5 points DDRS.",
        "Supprimez du plateau toutes les cartes qui touchent cette carte-ci (mais laissez la carte Alcool sur le plateau).",
        "Supprimez toutes les cartes Thé et Alcool retournées sur le plateau. Si une carte Ecocup est retournée sur le plateau, la faction qui a posé cette carte gagne 1 point DDRS. Sinon elle perd 1 point DDRS.",
        "Supprimez toutes les cartes Café et Alcool retournées sur le plateau. Si une carte Ecocup est retournée sur le plateau, la faction qui a posé cette carte gagne 1 point DDRS. Sinon elle perd 1 point DDRS.",
        "Cette carte est sans effet.",
        "La faction adverse de celle qui a posé cette carte perd 1 points DDRS pour chaque paire de cartes retournées et identiques sur le plateau. (S'il y a 3 cartes identiques, cela fait 3 paires).",
        "Chaque faction gagne 1 point DDRS par carte non retournée et non supprimée du plateau qu'elle a posée sur le plateau.",
        "Retournez toutes les cartes non retournées les plus à gauche et à droite de chaque ligne, sans appliquer leur effet.",
        "La faction adverse de celle qui a posé cette carte perd 3 points DDRS par carte Heures supplémentaires retournée sur le plateau (y compris celle-ci).",
        "Supprimez une carte non retournée du plateau choisie au hasard.",
        "Supprimez une ligne au hasard, la faction qui a posé cette carte gagne 2 points DDRS par carte supprimée ainsi.",
        "La faction qui a posé cette carte réactive l'effet de la dernière carte retournée avant Massinissa Merabet, en faisant comme elle l'avait posée elle-même, même si ce n'est pas le cas.",
        "La faction qui a le moins de points DDRS gagne 3 points DDRS.",
        "Supprimez toutes les cartes Heures supplémentaires retournées du plateau.",
        "Si la carte Heures supplémentaires est retournée sur le plateau, supprimez toutes les cartes de la ligne et de la colonne où est posée cette carte (y compris celle-ci). Sinon la faction qui a posé cette carte gagne 1 point DDRS par carte Catherine Dubois, Anne-Laure Ligozat, Guillaume Burel, Christophe Mouilleron, Thomas Lim, Julien Forest et Dimitri Watel retournée sur le plateau.",
        "Supprimez la première et la dernière cartes de la ligne et de la colonne où est posée cette carte.",
        "Pour chaque carte EcologIIE, Ecocup, Isolation du bâtiment et parcours Sobriété numérique retournées, la faction qui a posé cette carte gagne 3 points DDRS et la dernière carte non retournée du plateau est supprimée.",
        "Si la faction adverse de celle qui a posé cette carte a plus de points DDRS, la seconde lui vole 3 points DDRS.",
        "Si la carte Heures supplémentaires est retournée sur le plateau, supprimez toutes les cartes retournées du plateau sauf les cartes Christophe Mouilleron et Heures supplémentaires.",
        "Si Julien Forest n'est par retourné sur le plateau, la faction qui a posé cette carte gagne 3 points DDRS par carte FISE retournée sur le plateau. Sinon la faction adverse perd 1 point DDRS par carte FISE retournée sur le plateau.",
        "La faction qui a posé cette carte gagne 6 points DDRS par carte FISE retournée sur le plateau si au moins une carte Café est retournée sur le plateau.",
        "La faction qui a posé cette carte gagne 3 points DDRS par carte FISA ou FC retournée sur le plateau si au moins une carte Thé est retournée sur le plateau.",
        "S'il y a plus de 3 cartes retournées sur la ligne de cette carte, la faction qui a posé cette carte gagne 5 points DDRS.",
        "Prenez au hasard 5 cartes retournées du plateau (ou toutes les cartes retournées du plateau s'il y a moins de 5). Si une de ces cartes est une carte Catherine Dubois, Anne-Laure Ligozat, Guillaume Burel, Christophe Mouilleron, Thomas Lim, Julien Forest ou Dimitri Watel, mélangez les et placez les à gauche de la case la plus à gauche de la première ligne. Les prochaines cartes à être retournées sont ces cartes là. Sinon, supprimez ces cartes du plateau.",
        "S'il y a une carte FISA retournée dans la même ligne ou la même colonne que cette carte, la faction qui a posé cette carte gagne 5 points DDRS.",
        "Si les cartes Djibril-Aurélien Djembele-Cabeau, Eric Lejeune et Lucienne Pacavé sont retournées, la faction qui a posé cette carte gagne 10 points DDRS. Sinon, retournez toutes les cartes dans la même ligne de cette carte sans appliquer leurs effets.",
        "Si Laurent Prével est la dernière carte retournée du plateau, la faction qui a posé cette carte gagne la manche, quel que soit le nombre de points DDRS des deux factions."
};
#endif //ORIIEFLAMME_GR_11_CONSTANTE_H