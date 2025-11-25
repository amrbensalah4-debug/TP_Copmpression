#ifndef CODE_H
#define CODE_H

#include <stdint.h>
#include "occurence.h" // permet d’accéder à struct noeud

void afficherBinaire(uint32_t code, uint32_t taille);
void creerCode(struct noeud* ptrNoeud, uint32_t code, uint32_t taille);
struct noeud* getAdress(struct noeud* ptrNoeud, uint8_t caractere);
void compresserTexte(struct noeud* racine, uint8_t* texte, uint8_t* texteCompresse);

#endif
