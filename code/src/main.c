#include "../headers/interface.h"
#include "../headers/plateau.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "../headers/test.h"
#include "../headers/aleatoire.h"
#include "../headers/socket.h"

#define PARTIE_NON_TERMINEE -1
#define NOMBRE_FACTIONS 2


int main(int argc, char **argv) {
    // Si l'argument --test est passé au programme, alors on lance les tests unitaires et non le jeu
    if (argc == 2 && strcmp("--test", argv[1]) == 0) {
        run_all_tests();
    }
        // Si l'argument --test est passé au programme, alors on lance le serveur websocket
    else if (argc == 2 && strcmp("--online", argv[1]) == 0) {
        // La librairie nous fait associer chaque événement a une méthode
        struct ws_events evs;
        evs.onopen = &ouverture_connexion;
        evs.onclose = &fermeture_connexion;
        evs.onmessage = &reception_message;

        // On écoute sur le port 8080, chaque client aura son propre thread
        ws_socket(&evs, 8080, 0, 1000);

    }
        // Par défaut on lance une partie en local
    else {
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
                // system("clear");
                afficher_main_faction(factions[i]);
                // Si la faction n'a pas déjà remélangé alors on lui demande si elle veut
                if (a_remelanger(factions[i]) == FAUX) {
                    // Si elle accepte de renouveler sa main alors on la renouvelle
                    if (demander_renouvellement_main() == VRAI) {
                        vider_main_dans_pioche(factions[i]);
                        melanger_pioche(factions[i]);
                        repioche(factions[i]);
                        // On indique que la faction a utilisé sa fonction pour remelanger
                        remelanger(factions[i]);
                        afficher_main_faction(factions[i]);
                        demander_appuyer_sur_entree("Appuyer sur entrée pour passer à la faction suivante...", VRAI);
                    }
                } else {
                    demander_appuyer_sur_entree("Appuyer sur entrée pour passer à la faction suivante...", FAUX);
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
                if (nombre_cartes_posees != 0) {
                    afficher_plateau(p);
                }
                position position_carte = demander_position_poser_carte(p, factions[indice_faction_active],
                                                                        carte_a_poser);
                poser_carte(p, carte_a_poser, position_carte);
                afficher_plateau(p);
                demander_appuyer_sur_entree("Appuyer sur entrée pour passer à la faction suivante...", VRAI);
                afficher_plateau(p);

                // On passe à la faction suivante
                indice_faction_active = (indice_faction_active + 1) % 2;
            }
            // Phase 2, on retourne les cartesK
            carte carte_retournee = retourner_carte(p);
            // Quand la carte retournée vaut NULL, ça veut dire qu'il n'y a plus de cartes à retourner
            while (carte_retournee != NULL) {
                afficher_plateau(p);
                for (int i = 0; i < NOMBRE_FACTIONS; i++) {
                    printf("Points DDRS faction %d: %d \n", get_identifiant_faction(factions[i]),
                           get_points_DDRS(factions[i]));
                }
                demander_appuyer_sur_entree("Appuyer sur entrée pour retourner la carte suivante...", FAUX);
                carte_retournee = retourner_carte(p);
            }
            afficher_plateau(p);
            // On initialise la prochaine manche si le jeu n'est pas déjà terminé
            resultat_partie = initialiser_manche(p);
            numero_manche++;
        } while (resultat_partie == PARTIE_NON_TERMINEE);
        afficher_vainqueur(factions[resultat_partie]);
        free(ordre_faction);
        liberer_plateau(p);
    }


    return 0;
}


/*
int main(int argc, char **argv) {


    return 0;
} */

