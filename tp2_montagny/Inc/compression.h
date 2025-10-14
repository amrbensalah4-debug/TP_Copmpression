#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <stdint.h>


void occurrence(uint8_t *chaine, uint32_t tab[256]);

typedef struct noeud {
    uint8_t c;
    uint32_t occurrence;
    uint32_t code;
    uint32_t tailleCode;
    struct noeud *gauche;
    struct noeud *droite;
} noeud_t;


#endif
