#ifndef ARBRE_H
#define ARBRE_H

#include <stdint.h>
#include "occurence.h" // pour struct noeud

uint32_t creerFeuille(struct noeud* arbre[256], uint32_t tab[256]);
void afficherTabArbreHuffman(struct noeud* arbre[256], uint32_t taille);
void triArbre(struct noeud* arbre[256], uint32_t taille);
void afficherArbreTrier(struct noeud* arbre[256], uint32_t taille);
struct noeud* creerArbreHuffman(struct noeud* arbre[256], uint32_t taille);
void parcourirArbre(struct noeud* ptrNoeud);
void free_malloc(struct noeud* racine);

#endif
