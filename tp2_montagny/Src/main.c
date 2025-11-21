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



int main(void)
{
    FPU_Init();
    GPIO_Init();
    USART2_Init();
    SYSTICK_Init();

//    uint8_t texte[] = "aaaabbbccd";
//        uint32_t tab[256];
//        struct noeud* arbre[256];
//
//        // 1️⃣ Compter les occurrences
//        occurrence(texte, tab);
//
//        // 2️⃣ Créer les feuilles
//        uint32_t nbFeuilles = creerFeuille(arbre, tab);
//
//        // 3️⃣ Trier par occurrences
//        triArbre(arbre, nbFeuilles);
//
//        // 4️⃣ Créer l’arbre Huffman
//        struct noeud* racine = creerArbreHuffman(arbre, nbFeuilles);
//
//        // 5️⃣ Créer les codes Huffman
//        creerCode(racine, 0, 0);
//
//        // 6️⃣ Tester creerEntete
//        uint32_t tailleTexte = strlen((char*)texte);
//        uint32_t tailleFichier = 3; // valeur fictive pour l’instant
//
//        printf("\r\n---- Entête Huffman ----\r\n");
//        printf("Taille fichier compressé : %lu octets\r\n", tailleFichier);
//        printf("Taille texte original : %lu octets\r\n", tailleTexte);
//
//        creerEntete(racine, tailleFichier, tailleTexte);

    char msg[] = "Test UART2 boucle OK\r\n";


    while (1) {
        //SYSTICK_Delay(100);
        //GPIOA->ODR ^= (1<<5);
        //printf("Hello \r\n");
    	for (int i = 0; msg[i] != '\0'; i++) {
    	            USART2_TransmitChar(msg[i]);
    	        }

    	        // Lecture immédiate sur RX2 (car TX2 et RX2 sont reliés)
    	        if (USART2_ReceiveChar() != 0) {
    	            uint8_t c = USART2_ReceiveChar();
    	            USART2_TransmitChar(c); // renvoie ce qu’il lit
    	        }

    	        SYSTICK_Delay(1000);
    }
}
