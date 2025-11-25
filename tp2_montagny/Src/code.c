#include <stdio.h>
#include "code.h"

/**
  Affiche un code binaire sur la console.

  Paramètres :
    - code : entier contenant le code binaire à afficher
    - taille : nombre de bits à afficher
 */

void afficherBinaire(uint32_t code, uint32_t taille) {
    for (int i = taille - 1; i >= 0; i--)
        printf("%ld", (code >> i) & 1);
}


/*
  Crée les codes binaires de chaque caractère dans l’arbre de Huffman.

  Paramètres :
    - ptrNoeud : pointeur vers le nœud courant de l’arbre
    - code : entier représentant le code binaire en cours de construction
    - taille : nombre de bits déjà utilisés dans le code
 */

void creerCode(struct noeud* ptrNoeud, uint32_t code, uint32_t taille) {
    if (ptrNoeud->droite == NULL && ptrNoeud->gauche == NULL) {
        ptrNoeud->tailleCode = taille;
        ptrNoeud->code = code;
        printf("%c -> ", ptrNoeud->c);
        afficherBinaire(code, taille);
        printf(" (%lu bits)\r\n", ptrNoeud->tailleCode);
    } else {
        // Branche gauche : ajoute un "1" au code
        creerCode(ptrNoeud->gauche, (code << 1) + 1, taille + 1);
        // Branche droite : ajoute un "0" au code
        creerCode(ptrNoeud->droite, code << 1, taille + 1);
    }
}


/*
  Recherche récursivement l’adresse du nœud correspondant à un caractère.

  Paramètres :
    - ptrNoeud : pointeur vers le nœud courant
    - caractere : caractère à rechercher

  Retour :
    - pointeur vers le nœud correspondant au caractère
    - NULL si non trouvé
 */

struct noeud* getAdress(struct noeud* ptrNoeud, uint8_t caractere) {
    if (ptrNoeud == NULL)
        return NULL;

    // Si c’est une feuille, on vérifie le caractère
    if (ptrNoeud->gauche == NULL && ptrNoeud->droite == NULL) {
        if (ptrNoeud->c == caractere)
            return ptrNoeud;
        else
            return NULL;
    }

    // Recherche d’abord dans la branche gauche
    struct noeud* gauche = getAdress(ptrNoeud->gauche, caractere);
    if (gauche != NULL)
        return gauche;

    // Sinon, recherche dans la branche droite
    return getAdress(ptrNoeud->droite, caractere);
}


/*
  Compresse un texte en utilisant les codes Huffman.

  Paramètres :
    - racine : pointeur vers la racine de l’arbre de Huffman
    - texte : texte à compresser
    - texteCompresse : tableau où sera stocké le résultat compressé

 * Pour chaque caractère, on récupère son code Huffman et on écrit ses bits
   dans le tableau texteCompresse.
 */

void compresserTexte(struct noeud* racine, uint8_t* texte, uint8_t* texteCompresse) {
    uint32_t bitIndex = 0; // position du bit à écrire

    for (uint32_t i = 0; texte[i] != '\0'; i++) {
        struct noeud* n = getAdress(racine, texte[i]);

        for (int j = n->tailleCode - 1; j >= 0; j--) {
            uint8_t bit = (n->code >> j) & 1;

            uint32_t byteIndex = bitIndex / 8;
            uint8_t bitPos = 7 - (bitIndex % 8);

            if (bit == 1)
                texteCompresse[byteIndex] |= (1 << bitPos);
            else
                texteCompresse[byteIndex] &= ~(1 << bitPos);

            bitIndex++;
        }
    }

    printf("\r\nTexte compressé (%lu bits) : ", bitIndex);
    for (uint32_t i = 0; i < bitIndex; i++) {
        uint32_t byteIndex = i / 8;
        uint8_t bitPos = 7 - (i % 8);
        printf("%d", (texteCompresse[byteIndex] >> bitPos) & 1);
    }
    printf("\r\n");
}
