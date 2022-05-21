/**
 * @file socket.h
 * @brief Fichier contenant les fonctions concernant les différents événements de communication
 * entre le serveur webSocket et ses clients
 */
#ifndef ORIIEFLAMME_GR_11_SOCKET_H
#define ORIIEFLAMME_GR_11_SOCKET_H

#include "../lib/wsServer/include/ws.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * La fonction se déclenchant à l'ouverture d'une connexion par un client
 * @param client le client qui vient de se connecter
 */
void ouverture_connexion(ws_cli_conn_t *client);

/**
 * La fonction se déclenchant à la fermeture de la connexion par un client
 * @param client le client qui vient de se déconnecter
 */
void fermeture_connexion(ws_cli_conn_t *client);

/**
 * La fonction se déclenchant à la fermeture d'un message
 * @param client le client qui envoie le message
 * @param msg le contenu du message
 * @param size la taille du message
 * @param type le type de message
 */
void reception_message(ws_cli_conn_t *client,
                       const unsigned char *msg, uint64_t size, int type);


#endif //ORIIEFLAMME_GR_11_SOCKET_H
