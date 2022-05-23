#include "../headers/position.h"
#include <stdlib.h>
#include <stdio.h>


char *position_to_string(position p) {
    char *buffer = (char *) malloc(150 * sizeof(char));
    snprintf(buffer, 150, "%d,%d", p.abscisse, p.ordonnee);
    return buffer;
}
