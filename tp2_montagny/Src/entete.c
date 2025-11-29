#include <stdio.h>
#include <stdint.h>
#include "entete.h"

// Tableau global qui contiendra l’entête binaire
uint8_t entete[512];

// Taille réelle de l’entête
uint32_t tailleEntete = 0;

/**
 * @brief Crée une entête Huffman à partir des feuilles de l’arbre.
 *
 * @param tableau              Tableau contenant les feuilles de Huffman.
 * @param index                Nombre de feuilles (caractères différents).
 * @param tailleTexteCompresse Taille totale du texte compressé (en octets).
 * @param nbrCaractereTotal    Nombre total de caractères dans le texte original.
 *
 * Cette fonction encode les informations de chaque caractère :
 *   - Code ASCII (1 octet)
 *   - Code Huffman (4 octets)
 *   - Taille du code (4 octets)
 * Et ajoute aussi des informations globales (taille, etc.) au début du tableau.
 */
void creerEntete(struct noeud* tableau[], uint32_t index, uint32_t tailleTexteCompresse, uint32_t nbrCaractereTotal)
{
    tailleEntete = 0;

    // Réserve 2 octets pour la taille finale de l’entête
    entete[0] = 0;
    entete[1] = 0;
    tailleEntete += 2;

    // Taille du texte compressé (2 octets)
    entete[tailleEntete++] = (tailleTexteCompresse >> 8) & 0xFF;
    entete[tailleEntete++] = tailleTexteCompresse & 0xFF;

    // Nombre total de caractères originaux (2 octets)
    entete[tailleEntete++] = (nbrCaractereTotal >> 8) & 0xFF;
    entete[tailleEntete++] = nbrCaractereTotal & 0xFF;

    // Informations pour chaque caractère
    for (uint32_t i = 0; i < index; i++)
    {
        struct noeud* n = tableau[i];

        // 1 octet : ASCII du caractère
        entete[tailleEntete++] = n->c;

        // 4 octets : code Huffman
        entete[tailleEntete++] = (n->code >> 24) & 0xFF;
        entete[tailleEntete++] = (n->code >> 16) & 0xFF;
        entete[tailleEntete++] = (n->code >> 8) & 0xFF;
        entete[tailleEntete++] = n->code & 0xFF;

        // 4 octets : taille du code
        entete[tailleEntete++] = (n->tailleCode >> 24) & 0xFF;
        entete[tailleEntete++] = (n->tailleCode >> 16) & 0xFF;
        entete[tailleEntete++] = (n->tailleCode >> 8) & 0xFF;
        entete[tailleEntete++] = n->tailleCode & 0xFF;
    }

    // Écrit la taille totale de l’entête dans les 2 premiers octets
    entete[0] = (tailleEntete >> 8) & 0xFF;
    entete[1] = tailleEntete & 0xFF;

    // Affichage de l’entête pour vérification
    printf("---- AFFICHAGE EN BINAIRE ----\r\n");
        for (uint32_t i = 0; i < tailleEntete; i++)
        {
            for (int j = 7; j >= 0; j--)
                printf("%d", (entete[i] >> j) & 1);
            printf(" ");
            if ((i + 1) % 8 == 0) printf("\r\n");  // retour à la ligne tous les 8 octets
        }
        printf("\r\n");
}
