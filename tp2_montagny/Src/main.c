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



//Test totot tzatatz gfd
int main(void)
{
    FPU_Init();
    GPIO_Init();
    USART2_Init();
    SYSTICK_Init();

    uint8_t texte[] = "aaaabbbccd";
    uint32_t tab[256];
    uint8_t texteCompresse[256] = {0};

    occurrence(texte, tab);
    //afficheOccurence(texte,tab);

    struct noeud* arbre[256];

    uint32_t taille = creerFeuille(arbre, tab);
    //afficherTabArbreHuffman(arbre, taille);

    //printf("\r\n Arbre triée \r\n");
    //afficherArbreTrier(arbre, taille);


	printf("\r\n Test creation arbre Huffman \r\n");
	struct noeud* racine = creerArbreHuffman(arbre, taille);
	printf("Racine : '%c' -> %lu occurrences\r\n",
	       racine->c, racine->occurrence);

	//parcourirArbre(racine);
    //free_malloc(racine);

    creerCode(racine,0,0);

    compresserTexte(racine,texte,texteCompresse);


    while (1) {
        SYSTICK_Delay(100);
        GPIOA->ODR ^= (1<<5);
        //printf("Hello \r\n");
    }
}


