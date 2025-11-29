#ifndef OCCURENCE_H
#define OCCURENCE_H

#include <stdint.h>

// Définition commune de la structure
typedef struct noeud {
    uint8_t c;
    uint32_t occurrence;
    uint32_t code;
    uint32_t tailleCode;
    struct noeud *gauche;
    struct noeud *droite;
} noeud_t;

// Prototypes
void occurrence(uint8_t *chaine, uint32_t tab[256]);
void afficheOccurence(uint8_t *chaine, uint32_t tab[256]);
#endif
