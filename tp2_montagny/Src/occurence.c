#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "occurence.h"
#include "code.h"

/*
  Compte le nombre d’occurrences de chaque caractère dans une chaîne.

  Paramètres :
    - chaine : tableau de caractères (texte à analyser)
    - tab : tableau d'entiers (256 cases) pour stocker le nombre d’occurrences
 */
void occurrence(uint8_t *chaine, uint32_t tab[256]) {
    for (int i = 0; i < 256; i++)
        tab[i] = 0;   // initialisation à 0

    int i = 0;
    while (chaine[i] != '\0') {
        uint8_t caractere = chaine[i];
        tab[caractere]++;    // incrémente le compteur du caractère
        i++;
    }
}

/*
  Affiche les caractères et leurs occurrences.

  Paramètres :
    - chaine : tableau de caractères (texte utilisé, ici non essentiel)
    - tab : tableau d'entiers contenant les occurrences
 */
void afficheOccurence(uint8_t *chaine, uint32_t tab[256]) {
    for (int i = 0; i < 256; i++) {
        if (tab[i] != 0)
            printf("%c : %lu\r\n", i, tab[i]);  // affiche caractère et nombre
    }
}

/*
void creerEntete(struct noeud* ptrNoeud, uint32_t tailleFichier, uint32_t tailleTexte) {
    if (ptrNoeud == NULL) return;

    // Si c’est une feuille → on affiche son code Huffman
    if (ptrNoeud->gauche == NULL && ptrNoeud->droite == NULL) {
        printf("Caractère '%c' -> code : ", ptrNoeud->c);
        afficherBinaire(ptrNoeud->code, ptrNoeud->tailleCode);
        printf(" (taille : %lu bits)\r\n", ptrNoeud->tailleCode);
        return;
    }

    // Sinon, on parcourt récursivement la branche gauche et droite
    creerEntete(ptrNoeud->gauche, tailleFichier, tailleTexte);
    creerEntete(ptrNoeud->droite, tailleFichier, tailleTexte);
}
*/
