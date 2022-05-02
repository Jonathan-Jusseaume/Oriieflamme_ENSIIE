#include <time.h>
#include "../headers/aleatoire.h"
#include <stdlib.h>

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
