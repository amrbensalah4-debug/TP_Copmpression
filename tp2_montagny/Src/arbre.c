#include <stdio.h>
#include <stdlib.h>
#include "arbre.h"


/**
  Crée les feuilles de l’arbre de Huffman à partir du tableau d’occurrences.

  Paramètres :
   - arbre : tableau de pointeurs vers les nœuds
   - tab : tableau d’entiers contenant le nombre d’occurrences de chaque caractère

  Retour :
   - Le nombre total de feuilles créées (nbFeuilles)
 */

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

            arbre[index] = feuille;  // on stocke l’adresse dans le tableau
            index++;
        }
    }
    return index;
}

/*
  Affiche toutes les feuilles (caractères et occurrences)

  Paramètres :
    - arbre : tableau de pointeurs vers les nœuds
    - taille : nombre de feuilles à afficher
 */

void afficherTabArbreHuffman(struct noeud* arbre[256], uint32_t taille) {
    for (uint32_t i = 0; i < taille; i++)
        printf("Feuille %lu : '%c' -> %lu occurrences\r\n", i, arbre[i]->c, arbre[i]->occurrence);
}


/*
  Trie les feuilles de l’arbre par ordre croissant d’occurrence.

  Paramètres :
   - arbre : tableau de pointeurs vers les nœuds
   - taille : nombre total de feuilles
 */

void triArbre(struct noeud* arbre[256], uint32_t taille) {
    for (uint32_t i = 0; i < taille - 1; i++) {
        uint32_t min = i;
        for (uint32_t j = i + 1; j < taille; j++) {
            if (arbre[j]->occurrence < arbre[min]->occurrence)
                min = j;
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
    for (uint32_t i = 0; i < taille; i++)
        printf("Feuille %lu : '%c' -> %lu occurrences\r\n", i, arbre[i]->c, arbre[i]->occurrence);
}


/**
  Construit l’arbre de Huffman à partir des feuilles.

  Paramètres :
    - arbre : tableau de pointeurs vers les nœuds
    - taille : nombre initial de feuilles

  Retour :
    - Pointeur vers la racine de l’arbre final
 */

struct noeud* creerArbreHuffman(struct noeud* arbre[256], uint32_t taille) {
    while (taille > 1) {
        triArbre(arbre, taille);
        struct noeud* n1 = arbre[0];
        struct noeud* n2 = arbre[1];

        // Création d’un nouveau nœud interne
        struct noeud* nouveau = malloc(sizeof(struct noeud));
        nouveau->c = '!';
        nouveau->occurrence = n1->occurrence + n2->occurrence;
        nouveau->code = 0;
        nouveau->tailleCode = 0;
        nouveau->gauche = n1;
        nouveau->droite = n2;

        // Remplace le premier par le nouveau nœud
        arbre[0] = nouveau;

        // Décale le reste pour supprimer le deuxième
        for (uint32_t i = 1; i < taille - 1; i++)
            arbre[i] = arbre[i + 1];
        taille--;
    }
    return arbre[0]; // racine finale
}

/*
  Parcourt récursivement l’arbre de Huffman et affiche chaque nœud.

  Paramètre :
    - ptrNoeud : pointeur vers le nœud courant de l’arbre
 */
void parcourirArbre(struct noeud* ptrNoeud) {
    if (!ptrNoeud->gauche && !ptrNoeud->droite)
        printf("Feuille '%c' -> %lu occurrences\r\n", ptrNoeud->c, ptrNoeud->occurrence);
    else {
        printf("! -> %lu occurrences\r\n", ptrNoeud->occurrence);
        parcourirArbre(ptrNoeud->gauche);
        parcourirArbre(ptrNoeud->droite);
    }
}


/*
  Libère la mémoire allouée pour les nœuds enfants de la racine.

  Paramètre :
    - racine : pointeur vers la racine de l’arbre
 */

void free_malloc(struct noeud* racine) {
    free(racine->gauche);
    free(racine->droite);
}
