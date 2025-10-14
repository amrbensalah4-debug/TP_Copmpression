#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "compression.h"


void occurrence(uint8_t *chaine, uint32_t tab[256])
{
    for (int i = 0; i < 256; i++)
    {
        tab[i] = 0;
    }

    int i = 0;
    while (chaine[i] != '\0')
    {
        uint8_t caractere = chaine[i];  // on lit un caractère
        tab[caractere]++;               // on augmente son compteur
        i++;                            // on passe au caractère suivant
    }
}

uint32_t creerFeuille(struct noeud* arbre[256], uint32_t tab[256]){
	int index = 0;
	for(int i = 0 ; i < 256 ; i++){
		if (tab[i] > 0) {
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


void afficherTabArbreHuffman(struct noeud* arbre[256], uint32_t taille){
	for (uint32_t i = 0; i < taille; i++){
		printf("Feuille %lu : '%c' -> %lu occurrences\r\n",
		       i, arbre[i]->c, arbre[i]->occurrence);
	}
}

void triArbre(struct noeud* arbre[256] , uint32_t taille){
	int min;
	for(uint32_t i = 0; i < taille-1; i++){
		min = i;
		for(int j = i+1; j < taille; j++){
			if(arbre[j]->occurrence < arbre[min]->occurrence){
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

