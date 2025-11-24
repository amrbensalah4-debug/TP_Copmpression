#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "compression.h"


/* ===========================================================
 *              FONCTIONS DE COMPTAGE DES OCCURRENCES
 * ===========================================================*/

void occurrence(uint8_t *chaine, uint32_t tab[256]) {
    for (int i = 0; i < 256; i++) {
        tab[i] = 0; // initialisation à 0
    }

    int i = 0;
    while (chaine[i] != '\0') {
        uint8_t caractere = chaine[i];
        tab[caractere]++; // incrémente le compteur du caractère
        i++;
    }
}

void afficheOccurence(uint8_t *chaine, uint32_t tab[256]) {
    for (int i = 0; i < 256; i++) {
        if (tab[i] != 0) {
            printf("%c : %lu\r\n", i, tab[i]);
        }
    }
}

/* ===========================================================
 *              CONSTRUCTION DE L’ARBRE DE HUFFMAN
 * ===========================================================*/

uint32_t creerFeuille(struct noeud* arbre[256], uint32_t tab[256]) {
    int index = 0;
    for (int i = 0; i < 256; i++) {
        if (tab[i] > 0) {
            // Allocation mémoire d’une feuille
            struct noeud* feuille = malloc(sizeof(struct noeud));
            feuille->c = i;
            feuille->occurrence = tab[i];
            feuille->tailleCode = 0;
            feuille->droite = NULL;
            feuille->gauche = NULL;

            arbre[index] = feuille;
            index++;
        }
    }
    return index;
}

void afficherTabArbreHuffman(struct noeud* arbre[256], uint32_t taille) {
    for (uint32_t i = 0; i < taille; i++) {
        printf("Feuille %lu : '%c' -> %lu occurrences\r\n",
               i, arbre[i]->c, arbre[i]->occurrence);
    }
}

/* ===========================================================
 *              TRI DES FEUILLES
 * ===========================================================*/

void triArbre(struct noeud* arbre[256], uint32_t taille) {
    int min;
    for (uint32_t i = 0; i < taille - 1; i++) {
        min = i;
        for (int j = i + 1; j < taille; j++) {
            if (arbre[j]->occurrence < arbre[min]->occurrence) {
                min = j;
            }
        }
        if (min != i) {
            struct noeud* temp = arbre[i];
            arbre[i] = arbre[min];
            arbre[min] = temp;
        }
    }
}

void afficherArbreTrier(struct noeud* arbre[256], uint32_t taille) {
    triArbre(arbre, taille);
    for (uint32_t i = 0; i < taille; i++) {
        printf("Feuille %lu : '%c' -> %lu occurrences\r\n",
               i, arbre[i]->c, arbre[i]->occurrence);
    }
}

/* ===========================================================
 *              CREATION DE L’ARBRE DE HUFFMAN
 * ===========================================================*/

struct noeud* creerArbreHuffman(struct noeud* arbre[256], uint32_t taille) {
    while (taille > 1) {
        triArbre(arbre, taille);

        struct noeud* n1 = arbre[0];
        struct noeud* n2 = arbre[1];

        // Création d’un nouveau nœud interne
        struct noeud* nouveau = malloc(sizeof(struct noeud));
        nouveau->c = '!'; // marqueur nœud interne
        nouveau->occurrence = n1->occurrence + n2->occurrence;
        nouveau->code = 0;
        nouveau->tailleCode = 0;
        nouveau->gauche = n1;
        nouveau->droite = n2;

        // Remplace le premier par le nouveau nœud
        arbre[0] = nouveau;

        // Décale le reste pour supprimer le deuxième
        for (uint32_t i = 1; i < taille - 1; i++) {
            arbre[i] = arbre[i + 1];
        }

        taille--;
    }
    return arbre[0]; // racine finale
}

/* ===========================================================
 *              PARCOURS DE L’ARBRE
 * ===========================================================*/

void parcourirArbre(struct noeud* ptrNoeud) {
    if (ptrNoeud->droite == NULL && ptrNoeud->gauche == NULL) {
        printf("Je suis la feuille '%c' -> %lu occurrences\r\n",
               ptrNoeud->c, ptrNoeud->occurrence);
    } else {
        printf("Je suis le nœud '!' -> %lu occurrences\r\n", ptrNoeud->occurrence);
        parcourirArbre(ptrNoeud->droite);
        parcourirArbre(ptrNoeud->gauche);
    }
}

void free_malloc(struct noeud* racine) {
    free(racine->droite);
    free(racine->gauche);
}

/* ===========================================================
 *              CREATION DES CODES HUFFMAN
 * ===========================================================*/

void afficherBinaire(uint32_t code, uint32_t taille) {
    for (int i = taille - 1; i >= 0; i--) {
        printf("%ld", (code >> i) & 1);
    }
}

void creerCode(struct noeud* ptrNoeud, uint32_t code, uint32_t taille) {
    if (ptrNoeud->droite == NULL && ptrNoeud->gauche == NULL) {
        ptrNoeud->tailleCode = taille;
        ptrNoeud->code = code;
        printf("%c\t code : ", ptrNoeud->c);
        afficherBinaire(ptrNoeud->code, ptrNoeud->tailleCode);
        printf("\t taille : %lu\r\n", ptrNoeud->tailleCode);
    } else {
        creerCode(ptrNoeud->droite, code << 1, taille + 1);
        creerCode(ptrNoeud->gauche, (code << 1) + 1, taille + 1);
    }
}

/* ===========================================================
 *              RECHERCHE D’UN CARACTÈRE DANS L’ARBRE
 * ===========================================================*/

struct noeud* getAdress(struct noeud* ptrNoeud, uint8_t caractere) {
    if (ptrNoeud == NULL)
        return NULL;

    if (ptrNoeud->gauche == NULL && ptrNoeud->droite == NULL) {
        if (ptrNoeud->c == caractere)
            return ptrNoeud;
        else
            return NULL;
    }

    struct noeud* gauche = getAdress(ptrNoeud->gauche, caractere);
    if (gauche != NULL)
        return gauche;

    return getAdress(ptrNoeud->droite, caractere);
}

/* ===========================================================
 *              COMPRESSION DU TEXTE
 * ===========================================================*/

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

/* ===========================================================
 *              CREATION DE L’ENTÊTE HUFFMAN
 * ===========================================================*/

void creerEntete(struct noeud* ptrNoeud, uint32_t tailleFichier, uint32_t tailleTexte) {
    if (ptrNoeud == NULL) return;

    if (ptrNoeud->gauche == NULL && ptrNoeud->droite == NULL) {
        printf("Caractère '%c' -> code : ", ptrNoeud->c);
        afficherBinaire(ptrNoeud->code, ptrNoeud->tailleCode);
        printf(" (taille : %lu bits)\r\n", ptrNoeud->tailleCode);
        return;
    }

    creerEntete(ptrNoeud->gauche, tailleFichier, tailleTexte);
    creerEntete(ptrNoeud->droite, tailleFichier, tailleTexte);
}
