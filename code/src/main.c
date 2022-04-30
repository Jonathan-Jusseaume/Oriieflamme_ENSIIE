#include "../headers/interface.h"
#include "../headers/plateau.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../headers/test.h"

#define PARTIE_NON_TERMINEE -1
#define NOMBRE_FACTIONS 2

int *generer_ordre_partie();

int main(int argc, char **argv) {
    // Si l'argument --test est passé au programme, alors on lance les tests unitaires et non le jeu
    if (argc == 2 && strcmp("--test", argv[1]) == 0) {
        run_all_tests();
    }
    // S'il n'y a pas --test, on lance le jeu
  /*  else {
        plateau p = nouveau_plateau();
        faction *factions = get_factions(p);
        int resultat_partie = initialiser_manche(p);
        // Tableau contenant des entiers allant de 0 à 1 qui correspond à l'indice du joueur qui débute le tour
        int *ordre_faction = generer_ordre_partie();
        // Variable qui nous permet de compter le numéro de la manche
        int numero_manche = 0;
        // Boucle pour faire jouer tant que la partie n'est pas finie
        do {
            // Création de la main des joueurs
            for (int i = 0; i < NOMBRE_FACTIONS; i++) {
                melanger_pioche(factions[i]);
                repioche(factions[i]);
                afficher_main_faction(factions[i]);
                // Si la faction n'a pas déjà remélangé alors on lui demande si elle veut
                if (a_remelanger(factions[i]) == FAUX) {
                    // Si elle accepte de renouveler sa main alors on la renouvelle
                    if (demander_renouvellement_main(factions[i]) == VRAI) {
                        vider_main_dans_pioche(factions[i]);
                        melanger_pioche(factions[i]);
                        repioche(factions[i]);
                        // On indique que la faction a utilisé sa fonction pour remelanger
                        remelanger(factions[i]);
                        afficher_main_faction(factions[i]);
                    }
                }
            }
            // Phase 1, les joueurs posent les cartes à tour de rôle
            // On définit dans une variable l'indice de la faction active
            int indice_faction_active = ordre_faction[numero_manche];
            // On demande à tour de rôle à un joueur de poser une carte jusqu'à avoir 16 cartes sur le plateau
            for (int nombre_cartes_posees = 0; nombre_cartes_posees < NOMBRE_CARTES_MAXIMUM; nombre_cartes_posees++) {
                // On affiche la main de la faction
                afficher_main_faction(factions[indice_faction_active]);
                // On lui demande la carte à prendre
                carte carte_a_poser = demander_carte_poser_face_cachee(factions[indice_faction_active]);
                // On lui demande la position de la carte à poser en lui affichant le plateau actif
                afficher_plateau(p);
                position position_carte = demander_position_poser_carte(p, factions[indice_faction_active],
                                                                        carte_a_poser);
                poser_carte(p, factions[indice_faction_active], carte_a_poser, position_carte);
                afficher_plateau(p);
                // On passe à la faction suivante
                indice_faction_active = (indice_faction_active + 1) % 2;
            }
            // Phase 2, on retourne les cartesK
            carte carte_retournee = retourner_carte(p);
            // Quand la carte retournée vaut NULL, ça veut dire qu'il n'y a plus de cartes à retourner
            while (carte_retournee != NULL) {
                afficher_effet_carte_retournee(carte_retournee);
                afficher_plateau(p);
                carte_retournee = retourner_carte(p);
            }
            afficher_plateau(p);
            // On initialise la prochaine manche si le jeu n'est pas déjà terminé
            resultat_partie = initialiser_manche(p);
            numero_manche++;
        } while (resultat_partie == PARTIE_NON_TERMINEE);
        afficher_vainqueur(factions[resultat_partie]);
        liberer_plateau(p);
    } */
    return 0;
}

int *generer_ordre_partie() {
    int *ordre_partie = (int *) malloc(3 * sizeof(int));
    // On tire au sort un nombre entre 0 et 1
    srand(time(NULL));
    ordre_partie[0] = rand() % 2;
    // On fait en sorte que la manche 2 soit une valeur différente de la première
    ordre_partie[1] = (ordre_partie[0] + 1) % 2;
    // On retire au sort pour la dernière manche
    ordre_partie[2] = rand() % 2;
    return ordre_partie;
}