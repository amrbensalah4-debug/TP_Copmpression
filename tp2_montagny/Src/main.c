#include <stdint.h>
#include <stm32f446xx.h>
#include <stdio.h>
#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "timer.h"
#include "util.h"
#include "compression.h"



//Test totot tzatatz gfd
int main(void)
{
    FPU_Init();
    GPIO_Init();
    USART2_Init();
    SYSTICK_Init();

    uint8_t texte[] = "aaaabbbcc, hello world !";
    uint32_t tab[256];
    struct noeud* arbre[256];
    occurrence(texte, tab);



	uint32_t taille = creerFeuille(arbre, tab);
    //afficherTabArbreHuffman(arbre, taille );


	/*
    printf("\r\n Test triArbre \r\n");
    triArbre(arbre, taille);
    for (uint32_t i = 0; i < taille; i++) {
        printf("Feuille %lu : '%c' -> %lu occurrences\r\n",
               i, arbre[i]->c, arbre[i]->occurrence);
    }
    */


    /*printf("---- Test fonction occurrence ----\r\n");
    for (int c = 0; c < 256; c++) {
        if (tab[c] != 0) {
            printf("'%c' : %lu\r\n", c, tab[c]);
        }
    }
    */


	printf("\r\n---- Test creation arbre Huffman ----\r\n");

	struct noeud* racine = creerArbreHuffman(arbre, taille);

	// Vérification de base
	printf("Racine : '%c' -> %lu occurrences\r\n",
	       racine->c, racine->occurrence);

	// Vérifie que la racine regroupe bien tous les caractères
	printf("Total attendu : %lu\r\n", (uint32_t)strlen((char*)texte));


    while (1) {
        SYSTICK_Delay(1000);
        //GPIOA->ODR ^= (1<<5);
        //printf("Hello \r\n");
    }
}


