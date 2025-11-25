#include <stdint.h>
#include <stm32f446xx.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "timer.h"
#include "util.h"
#include "occurence.h"
#include "arbre.h"
#include "code.h"



int main(void)
{

    FPU_Init();
    GPIO_Init();
    USART2_Init();
    USART1_Init();
    SYSTICK_Init();


    uint8_t texte[] = "aaaabbbccd";   // Texte à compresser
    uint32_t tab[256];                // Tableau d’occurrences
    struct noeud* arbre[256];         // Tableau de pointeurs vers les nœuds
    uint8_t texteCompresse[256] = {0}; // tableau de texte compressé

    /* =====  compression Huffman ===== */

    // Compter les occurrences
    occurrence(texte, tab);

    // Créer les feuilles
    uint32_t nbFeuilles = creerFeuille(arbre, tab);

    // Trier les feuilles selon les occurrences
    triArbre(arbre, nbFeuilles);

    //  Construire l’arbre de Huffman

    struct noeud* racine = creerArbreHuffman(arbre, nbFeuilles);

    //  Générer les codes Huffman
    creerCode(racine, 0, 0);

    //  Compresser le texte
    compresserTexte(racine, texte, texteCompresse);

/*
    uint32_t tailleTexte = strlen((char*)texte);
    uint32_t tailleFichier = 3; // j'ai 3 octets pour l'instant

    printf("\r\n---- Entête Huffman ----\r\n");
    printf("Taille fichier compressé : %lu octets\r\n", tailleFichier);
    printf("Taille texte original : %lu octets\r\n", tailleTexte);

    // Afficher les codes Huffman de chaque caractère
    creerEntete(racine, tailleFichier, tailleTexte);
*/
    while (1) {
        // SYSTICK_Delay(100);
        // GPIOA->ODR ^= (1<<5);
        // printf("Hello \r\n");
    }
}
