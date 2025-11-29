#ifndef ENTETE_H
#define ENTETE_H

#include <stdint.h>
#include "arbre.h"  // pour struct noeud

// Déclarations globales (visibles dans tout le projet)
extern uint8_t entete[512];
extern uint32_t tailleEntete;

/**
 * @brief Crée l’entête Huffman contenant toutes les infos nécessaires
 *        à la décompression du fichier compressé.
 */
void creerEntete(struct noeud* tableau[],
                 uint32_t index,
                 uint32_t tailleTexteCompresse,
                 uint32_t nbrCaractereTotal);

#endif
