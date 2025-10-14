#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <stdint.h>

struct noeud {
    uint8_t c;
    uint32_t occurrence;
    uint32_t code;
    uint32_t tailleCode;
    struct noeud *gauche;
    struct noeud *droite;
};


void occurrence(uint8_t *chaine, uint32_t tab[256]);
uint32_t creerFeuille(struct noeud* arbre[256], uint32_t tab[256]);
void afficherTabArbreHuffman(struct noeud* arbre[256], uint32_t taille);
void triArbre(struct noeud* arbre[256] , uint32_t taille);
struct noeud* creerArbreHuffman(struct noeud* arbre[256], uint32_t taille);



#endif
