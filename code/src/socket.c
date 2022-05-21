

#include "../headers/socket.h"
#include "../headers/plateau.h"
#include "../headers/constante.h"
#include "../headers/aleatoire.h"

#define PARTIE_NON_TERMINEE -1
#define NOMBRE_FACTIONS 2

// On stocke le nombre de clients connectés
int nombre_clients = 0;
// Chaque client est repertorié dans ce tableau, on ne peut en avoir plus de deux
ws_cli_conn_t *clients[2];
// L'indice de la faction qui doit jouer
int indice_faction_active = 0;
// Le plateau de jeu
plateau p = NULL;
// Les deux factions
faction *factions;
// L'ordre à chaque manche
int *ordre_faction = NULL;
// Numéro manche
int numero_manche = 0;
// booleen pour savoir si les ont dit si elles voulaient repiocher ou non
booleen factions_reponse_repioche[] = {FAUX, FAUX};

// Fonction envoyant un message à tous les clients
void envoie_message_broadcast(char *message) {
    printf("Envoi en broadcast: %s \n", message);
    for (int i = 0; i < 2; i++) {
        ws_sendframe_txt(clients[i], message);
    }
}

void lire_message_poser_carte_et_mettre_a_jour_plateau(const unsigned char *message) {
    int indice = 0;
    int indice_carte = 0;
    int abscisse = 0;
    int ordonnee = 0;
    sscanf(message, "%d;%d;%d;%d", &indice, &indice_carte, &abscisse, &ordonnee);
    liste_chainee_carte main_faction = get_main(factions[indice]);
    carte carte_choisie = supprimer_carte_liste_chainee(&main_faction, indice_carte - 1);
    set_main(factions[indice], main_faction);
    poser_carte(p, carte_choisie, (position) {abscisse, ordonnee});
    char *pl = plateau_to_string(p);
    envoie_message_broadcast(pl);
    free(pl);
}

void lire_message_demande_repioche(const unsigned char *msg) {
    int indice = 0;
    int veut_remelanger;
    sscanf(msg, "%d;%d", &indice, &veut_remelanger);
    // On dit que la faction a répondu
    factions_reponse_repioche[indice] = VRAI;
    if (veut_remelanger) {
        vider_main_dans_pioche(factions[indice]);
        melanger_pioche(factions[indice]);
        repioche(factions[indice]);
        // On indique que la faction a utilisé sa fonction pour remelanger
        remelanger(factions[indice]);
        char *pl = plateau_to_string(p);
        envoie_message_broadcast(pl);
        free(pl);
    }
}


void ouverture_connexion(ws_cli_conn_t *client) {
    // Si on a pas encore deux clients alors on l'ajoute à nos clients
    if (nombre_clients < 2) {
        char *cli;
        cli = ws_getaddress(client);
        printf("Ouverture connexion, addresse: %s\n", cli);
        clients[nombre_clients] = client;
        // On envoie à notre client son numéro de joueurs
        char buffer[5];
        snprintf(buffer, 5, "ID:%d", nombre_clients);
        ws_sendframe_txt(client, buffer);
        nombre_clients++;

        // Si on a nos deux joueurs alors la partie peut commencer
        if (nombre_clients == 2) {
            // On instancie le plateau
            p = nouveau_plateau();
            factions = get_factions(p);
            initialiser_manche(p);
            ordre_faction = generer_ordre_partie();
            for (int i = 0; i < NOMBRE_FACTIONS; i++) {
                melanger_pioche(factions[i]);
                repioche(factions[i]);
            }
            // On envoie le plateau et donc les mains aux joueurs
            char *message = plateau_to_string(p);
            envoie_message_broadcast(message);
            free(message);
            // On demande si le joueur 1 veut repiocher car il n'a pas encore pioché
            ws_sendframe_txt(clients[0], "PIOCHE");
            indice_faction_active = ordre_faction[numero_manche];
        }
    }
}


void fermeture_connexion(ws_cli_conn_t *client) {
    char *cli;
    cli = ws_getaddress(client);
    printf("Connection closed, addr: %s\n", cli);
    nombre_clients--;
    if (ordre_faction != NULL) {
        free(ordre_faction);
    }
    if (p != NULL) {
        liberer_plateau(p);
    }
    exit(1);
}

void reception_message(ws_cli_conn_t *client,
                       const unsigned char *msg, uint64_t size, int type) {
    booleen a_lu_message = FAUX;
    // On log les messages
    char *cli;
    cli = ws_getaddress(client);
    printf("Réception message: %s (%zu), de: %s\n", msg,
           size, cli);
    // Plusieurs scénarios selon les messages reçues/etat du jeu

    // Cas 1: tous les joueurs n'ont pas encore dit s'ils voulaient remelangé, il faut donc regarder leur réponse
    // Si la faction 1, n'a pas dit sa réponse, alors on s'attend à ce que ce soit le message envoyé
    if (!factions_reponse_repioche[0]) {
        lire_message_demande_repioche(msg);
        // On demande si le joueur 2 veut repiocher s'il n'a pas encore donné sa réponse
        if (!factions_reponse_repioche[1]) {
            ws_sendframe_txt(clients[1], "PIOCHE");
        }
        a_lu_message = VRAI;
    } else if (!factions_reponse_repioche[1]) {
        lire_message_demande_repioche(msg);
        a_lu_message = VRAI;
    }
    printf("%d \n", get_nombre_cartes_posees(p));
    // Si les deux joueurs ont donné leur réponse et qu'il y a encore des cartes à poser alors il faut demander
    if (factions_reponse_repioche[0] && factions_reponse_repioche[1] && get_nombre_cartes_posees(p) < NOMBRE_CARTES_MAXIMUM) {
        if (!a_lu_message) {
            lire_message_poser_carte_et_mettre_a_jour_plateau(msg);
            a_lu_message = VRAI;
            indice_faction_active = (indice_faction_active + 1) % 2;
        }
        printf("faction active: %d \n", indice_faction_active);
        if (get_nombre_cartes_posees(p) < NOMBRE_CARTES_MAXIMUM) {
            ws_sendframe_txt(clients[indice_faction_active], "POSE");
        }
    }





    // Lancement de fin de la manche, on retourne toutes les cartes une par une et on envoie les infos sur la fin de la manche
    if (get_nombre_cartes_posees(p) == NOMBRE_CARTES_MAXIMUM) {
        carte carte_retournee = retourner_carte(p);
        // Quand la carte retournée vaut NULL, ça veut dire qu'il n'y a plus de cartes à retourner, on envoie à chaque fois le tout en broadcast
        while (carte_retournee != NULL) {
            char *message = plateau_to_string(p);
            envoie_message_broadcast(message);
            free(message);
            sleep(5);
            carte_retournee = retourner_carte(p);
        }
        char *message = plateau_to_string(p);
        envoie_message_broadcast(message);
        free(message);
        int resultat_partie = initialiser_manche(p);
        char buffer[20];
        snprintf(buffer, 20, "RESULTAT:%d", resultat_partie);
        envoie_message_broadcast(buffer);
        if (resultat_partie != PARTIE_NON_TERMINEE) {
            free(ordre_faction);
            liberer_plateau(p);
            exit(0);
        } else {
            sleep(5);
            for (int i = 0; i < NOMBRE_FACTIONS; i++) {
                melanger_pioche(factions[i]);
                repioche(factions[i]);
            }
            char *message = plateau_to_string(p);
            envoie_message_broadcast(message);
            free(message);
            if (!a_remelanger(factions[0])) {
                factions_reponse_repioche[0] = FAUX;
                ws_sendframe_txt(clients[0], "PIOCHE");
            }
            if (!a_remelanger(factions[1])) {
                factions_reponse_repioche[1] = FAUX;
                if (factions_reponse_repioche[0]) {
                    ws_sendframe_txt(clients[1], "PIOCHE");
                }
            }


        }
        numero_manche++;
    }
}


