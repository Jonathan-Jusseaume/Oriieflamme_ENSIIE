/**
 * @file effets.h
 * @brief Fichier contenant les différents effets des cartes
 */
#ifdef __GNUC__
#define VARIABLE_NOT_USED_IGNORE __attribute__ ((unused))
#else
#define VARIABLE_NOT_USED_IGNORE
#endif

#ifndef ORIIEFLAMME_GR_11_EFFETS_H
#define ORIIEFLAMME_GR_11_EFFETS_H


#include "carte.h"
#include "plateau.h"
#include "faction.h"
#include <stdio.h>

/**
 * Le prototype des fonctions correspondant à l'effet des cartes qui est toujouo
 */
typedef void (*effet_fonction)(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte FISE
 * La faction qui a posé cette carte gagne 1 point DDRS
 * @param c pointeur sur une carte FISE
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void fise(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte FISA
 * La faction qui a posé cette carte gagne 2 points DDRS si le nombre de cartes retournées sur le plateau est pair
 * @param c pointeur sur une carte FISA
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void fisa(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte FC
 * La faction qui a posé cette carte gagne 4 points DDRS si une autre carte FC est retournée sur le plateau
 * @param c pointeur sur une carte FC
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void fc(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Ecologiie
 * La faction qui a posé cette carte gagne 1 points DDRS par carte FISE,FISA et FC retournée sur le plateau
 * @param c pointeur sur une carte Ecologiie
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void ecologiie(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Liiens
 * Prends toutes les cartes FISE,FISA et FC retournées, les mélange et les place face cachées tout en haut à gauche du plateau
 * @param c pointeur sur une carte Liiens
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void liiens(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Soirees_sans_alcool
 * Si une carte alcool est retournée, supprime toutes les cartes FISE, FISA et FC retournées et supprime la première et dernière ligne du plateau
 * Sinon, la faction qui a posé cette carte de gagner 1 point DDRS
 * @param c pointeur sur la carte Soirees_sans_alcool
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void soirees_sans_alcool(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Alcool
 * Supprime toutes les cartes touchant celle-ci (supprime la carte posée au-dessus, en-desssus, à sa gauche et à sa droite)
 * @param c pointeur sur la carte Alcool
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void alcool(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Café
 * Supprime toutes les cartes Thé et Alcool retournées du plateau.
 * Si une carte Ecocup est retournée, la faction qui a posé cette carte gagne 1 points DDRS
 * Sinon, la faction qui a posé cette carte gagne 1 points DDRS
 * @param c pointeur sur une carte Café
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void cafe(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Thé
 * Supprime toutes les cartes Café et Alcool retournées du plateau.
 * Si une carte Ecocup est retournée, la faction qui a posé cette carte gagne 1 points DDRS
 * Sinon, la faction qui a posé cette carte gagne 1 points DDRS
 * @param c pointeur sur une carte Thé
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void the(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Ecocup
 * Ne fait rien
 * @param c pointeur sur la carte Ecocup
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien car la carte ne fait rien
 */
void ecocup(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Reprographie
 * La faction adverse à celle qui a posé cette carte perd 1 point DDRS pour chaque pair de cartes retournées et identiques du plateau
 * @param c pointeur sur la carte Reprographie
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void reprographie(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Isolation du bâtiment
 * Chaque faction gagne 1 point DDRS par carte face cachée du plateau qu'elle a posé
 * @param c pointeur sur la carte Isolation du bâtiment
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void isolation_batiment(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Parcours sobriété numérique
 * Retourne toutes les cartes les plus à gauche et à droite de chaque ligne sans appliquer leur effet
 * @param c pointeur sur la carte Parcours sobriété numérique
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void parcours_sobriete_numerique(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Heures supplémentaires
 * Cette carte fait perdre 3 points DDRS à la faction adverse de celle qui a posé cette carte.
 * La faction adverse de celle qui a posé cette carte perd également 3 points DDRS par autre carte Heures supplémentaires retournée sur le plateau
 * @param c pointeur sur la carte Heures supplémentaires
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void heures_supplementaires(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Kahina Bouchama
 * Supprime du plateau une carte face cachée au hasard
 * @param c pointeur sur la carte Kahina Bouchama
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void kahina_bouchama(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Kevin Goilard
 * Supprime du plateau une ligne au hasard.
 * La faction qui a posé cette carte gagne 2 points DDRS par carte supprimée dans cette ligne supprimée.
 * @param c pointeur sur la carte Kevin Goilard
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void kevin_goilard(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Massinissa Merabet
 * La dernière carte retournée voit son effet s'activer à nouveau telle qu'elle appartient à la faction qui a posé la carte Massinissa Merabet.
 * @param c pointeur sur la carte Massinissa Merabet
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void massinissa_merabet(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Vitéra Y
 * La faction qui a le moins de points DRRS se voit conférer 3 points DDRS.
 * @param c pointeur sur la carte Vitéra Y
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void vitera_y(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Jonas Senizergues
 * Supprime toutes les cartes Heures supplémentaires retournées du plateau
 * @param c pointeur sur la carte Jonas Senizergues
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void jonas_senizergues(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Fetia Bannour
 * Si la carte Heures Supplémentaires est retournée, supprime du plateau toutes les cartes de la ligne et de la colonne où cette carte est posée (y compris elle-même)
 * Sinon, la faction qui a posé cette carte gagne 1 points DDRS par carte Catherine Dubois, Anne-Laure Ligozat,
 * Guillaume Burel, Christophe Mouilleron, Thomas Lim, Julien Forest et Dimitri Watel retournée sur le plateau.
 * @param c pointeur sur la carte Fetia Bannour
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void fetia_bannour(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Catherine Dubois
 * Supprime du plateau la première et dernière carte de la ligne où est posée cette carte
 * @param c pointeur sur la carte Catherine Dubois
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void catherine_dubois(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Anne-Laure Ligozat
 * La faction qui a posé cette carte gagne 3 points DDRS et la dernière carte face cachée du plateau est supprimée pour chaque carte Ecologiie,
 * Ecocup, Isolation du bâtiment et parcours Sobriété numérique retournées
 * @param c pointeur sur la carte Anne-Laure Ligozat
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void anne_laure_ligozat(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Guillaume Burel
 * Si la faction adverse de celle qui a posé cette carte a plus de points DDRS, la faction qui a posé cette carte lui vole 3 points DDRS.
 * @param c pointeur sur la carte Guillaume Burel
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void guillaume_burel(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Christophe Mouilleron
 * Supprime du plateau toutes les cartes retournées sauf les cartes Christophe Mouilleron et Heures supplémentaires si la carte Heures supplémentaires est retournée.
 * @param c pointeur sur la carte Christophe Mouilleron
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void christophe_mouilleron(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Thomas Lim
 * Si la carte Julien Forest n'est pas retournée sur le plateau, la faction qui a posé cette carte gagne 3 points DDRS par carte FISE retournée sur le plateau.
 * Sinon, la faction adverse perd 3 points DDRS par carte FISE retournée sur le plateau.
 * @param c pointeur sur la carte Thomas Lim
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void thomas_lim(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Julien Forest
 * Si une carte café est retournée sur le plateau, la faction qui a posé cette carte gagne 6 points DDRS par carte FISE retournée sur le plateau
 * @param c pointeur sur la carte Julien Forest
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void julien_forest(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Dimitri Watel
 * Si une carte thé est retournée sur le plateau, la faction qui a posé cette carte gagne 3 points DDRS par carte FISA ou FC retournée sur le plateau
 * @param c pointeur sur la carte Dimitri Watel
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void dimitri_watel(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Djibril-Aurélien-Dembele-Cabot
 * S'il y a plus de 3 cartes retournées sur la ligne de cette carte sur le plateau, la faction qui a posé cette carte gagne 5 points DDRS
 * @param c pointeur sur la carte Djibril-Aurélien-Dembele-Cabot
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void djibril_aurelien_dembele_cabot(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Eric Lejeune
 * 	Prend au hasard 5 cartes retournées du plateau (ou toutes les cartes retournées du plateau s'il y a moins de 5).
 * 	Si une de ces cartes est une carte Catherine Dubois, Anne-Laure Ligozat, Guillaume Burel, Christophe Mouilleron, Thomas Lim, Julien Forest ou Dimitri Watel,
 * 	mélange les et les place à gauche de la case la plus à gauche de la première ligne.
 * 	Les prochaines cartes à être retournées sont ces cartes là. Sinon, supprimez ces cartes du plateau.
 * @param c pointeur sur la carte Eric Lejeune
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void eric_lejeune(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Lucienne Pacave
 * S'il y a une carte FISA retournée dans la même ligne ou la même colonne que cette carte, la faction qui a posé cette carte gagne 5 points DDRS.
 * @param c pointeur sur la carte Lucienne Pacave
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void lucienne_pacave(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Katrin Salhab
 * Si les cartes Djibril-Aurélien Djembele-Cabeau, Eric Lejeune et Lucienne Pacavé sont retournées, la faction qui a posé cette carte gagne 10 points DDRS.
 * Sinon, retourne toutes les cartes dans la même ligne de cette carte sans appliquer leurs effets.
 * @param c pointeur sur la carte Katrin Salhab
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void katrin_salhab(carte c, plateau p);

/**
 * Fonction pour l'effet de la carte Laurent Prével
 * Si Laurent Prével est la dernière carte retournée du plateau, la faction qui a posé cette carte gagne la manche, quel que soit le nombre de points DDRS des deux factions.
 * @param c pointeur sur la carte Laurent Prével
 * @param p pointeur sur le plateau de jeu
 * @return On ne retourne rien, on agit juste sur la manche courante
 */
void laurent_prevel(carte c, plateau p);

/**
 * Tableau de pointeurs sur les différentes fonctions qui n'a pas été mis dans constante pour éviter
 * des problèmes d'include circulaire
 */
static VARIABLE_NOT_USED_IGNORE void (*effets[])(carte c, plateau p) = {
        fise,
        fisa,
        fc,
        ecologiie,
        liiens,
        soirees_sans_alcool,
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

#endif //ORIIEFLAMME_GR_11_EFFETS_H
