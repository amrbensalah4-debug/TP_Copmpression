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


struct noeud* creerArbreHuffman(struct noeud* arbre[256], uint32_t taille)
{
    while (taille > 1) {
        triArbre(arbre, taille);

        struct noeud* n1 = arbre[0];
        struct noeud* n2 = arbre[1];

        struct noeud* nouveau = malloc(sizeof(struct noeud));
        nouveau->c = '!';  // marqueur d’un nœud interne
        nouveau->occurrence = n1->occurrence + n2->occurrence;
        nouveau->code = 0;
        nouveau->tailleCode = 0;
        nouveau->gauche = n1;
        nouveau->droite = n2;

        // on remplace le premier par le nouveau noeud
        arbre[0] = nouveau;

        // on décale le reste vers la gauche pour supprimer le 2e
        for (uint32_t i = 1; i < taille - 1; i++) {
            arbre[i] = arbre[i + 1];
        }

        taille--; // on a fusionné 2 noeuds -> 1 seul remplace
    }

    return arbre[0]; // racine
}


