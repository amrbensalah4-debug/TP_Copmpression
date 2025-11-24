#include <stdint.h>
#include <stm32f446xx.h>
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "timer.h"
#include "util.h"
#include "compression.h"

/* ===========================================================
 *                  PROGRAMME PRINCIPAL
 * ===========================================================*/

int main(void)
{
    /* ===== 1. Initialisations matérielles ===== */
    FPU_Init();          // Active le coprocesseur flottant
    GPIO_Init();         // Configure les broches GPIO
    USART2_Init();       // Initialise l’UART2 (liaison série PC)
    USART1_Init();       // Initialise l’UART1 (pour tests ou transfert)
    SYSTICK_Init();      // Initialise le timer SysTick

    /* ===== 2. Données d’entrée ===== */
    uint8_t texte[] = "aaaabbbccd";   // Texte à compresser
    uint32_t tab[256];                // Tableau d’occurrences
    struct noeud* arbre[256];         // Tableau de pointeurs vers les nœuds
    uint8_t texteCompresse[256] = {0}; // Zone mémoire du texte compressé

    /* ===== 3. Étapes de compression Huffman ===== */

    // Étape 1 : Compter les occurrences
    occurrence(texte, tab);

    // Étape 2 : Créer les feuilles
    uint32_t nbFeuilles = creerFeuille(arbre, tab);

    // Étape 3 : Trier les feuilles selon les occurrences
    triArbre(arbre, nbFeuilles);

    // Étape 4 : Construire l’arbre de Huffman
    struct noeud* racine = creerArbreHuffman(arbre, nbFeuilles);

    // Étape 5 : Générer les codes Huffman
    creerCode(racine, 0, 0);

    // Étape 6 : Compresser le texte
    compresserTexte(racine, texte, texteCompresse);

    /* ===== 4. Informations sur la compression ===== */
    uint32_t tailleTexte = strlen((char*)texte);
    uint32_t tailleFichier = 3; // Valeur fictive, à calculer plus tard

    printf("\r\n---- Entête Huffman ----\r\n");
    printf("Taille fichier compressé : %lu octets\r\n", tailleFichier);
    printf("Taille texte original : %lu octets\r\n", tailleTexte);

    // Afficher les codes Huffman de chaque caractère
    creerEntete(racine, tailleFichier, tailleTexte);

    /* ===== 5. Boucle principale ===== */
    while (1) {
        // Exemple : clignotement de LED ou debug
        // SYSTICK_Delay(100);
        // GPIOA->ODR ^= (1<<5);
        // printf("Hello \r\n");
    }
}
