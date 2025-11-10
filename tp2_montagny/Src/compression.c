#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "compression.h"


void occurrence(uint8_t *chaine, uint32_t tab[256]){
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

void afficheOccurence(uint8_t *chaine, uint32_t tab[256]){
	for(int i = 0 ;  i < 256 ; i++){
		if(tab[i] != 0){
			printf("%c : %lu\r\n", i, tab[i]);
		}
	}
}


uint32_t creerFeuille(struct noeud* arbre[256], uint32_t tab[256]){
	int index = 0;
	for(int i = 0 ; i < 256 ; i++){
		if (tab[i] > 0) {               // si la case tab [i] contient un caractère
			struct noeud* feuille = malloc(sizeof(struct noeud)); // reserver un bloc de mémoire pour contenir une structure de type struct noeud
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

void afficherArbreTrier(struct noeud* arbre[256] , uint32_t taille){
	triArbre(arbre, taille);
	for (uint32_t i = 0; i < taille; i++) {
	    printf("Feuille %lu : '%c' -> %lu occurrences\r\n",
	          i, arbre[i]->c, arbre[i]->occurrence);
	}
}


struct noeud* creerArbreHuffman(struct noeud* arbre[256], uint32_t taille){
    while (taille > 1) { // Tant qu’il reste plus d’un nœud dans le tableau
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

        taille--; // on diminue la taille
    }

    return arbre[0]; // racine
}


void parcourirArbre(struct noeud* ptrNoeud){
    if (ptrNoeud->droite == NULL && ptrNoeud->gauche == NULL) {
        printf("Je suis la feuille '%c' -> %lu occurrences\r\n", ptrNoeud->c, ptrNoeud->occurrence);
    } else {
        printf("Je suis le nœud '!' -> %lu occurrences\r\n", ptrNoeud->occurrence);
        parcourirArbre(ptrNoeud->droite); // on va à droite
        parcourirArbre(ptrNoeud->gauche); // on va à gauche
    }
}


void free_malloc(struct noeud* racine){
	free(racine->droite);
	free(racine->gauche);
}


void afficherBinaire(uint32_t code, uint32_t taille)
{
    for (int i = taille - 1; i >= 0; i--) {
        printf("%ld", (code >> i) & 1);  // Affiche chaque bit du code
    }
}

void creerCode(struct noeud* ptrNoeud, uint32_t code, uint32_t taille){
	if(ptrNoeud->droite == NULL && ptrNoeud->gauche == NULL) {
		ptrNoeud->tailleCode = taille;
		ptrNoeud->code = code;
		printf("%c\t code : ", ptrNoeud->c);
	    afficherBinaire(ptrNoeud->code, ptrNoeud->tailleCode);
		printf("\t taille : %lu\r\n", ptrNoeud->tailleCode);
	}
	else{
		creerCode(ptrNoeud->droite, code<<1, taille+1);
		creerCode(ptrNoeud->gauche, (code<<1)+1, taille+1);
	}
}


struct noeud* getAdress(struct noeud* ptrNoeud, uint8_t caractere)
{
    if (ptrNoeud == NULL)
        return NULL;

    // Si on est sur une feuille
    if (ptrNoeud->gauche == NULL && ptrNoeud->droite == NULL) {
        if (ptrNoeud->c == caractere)
            return ptrNoeud;  // trouvé !
        else
            return NULL;
    }

    // Chercher dans la branche gauche
    struct noeud* gauche = getAdress(ptrNoeud->gauche, caractere);
    if (gauche != NULL)
        return gauche;

    // Sinon, chercher dans la branche droite
    return getAdress(ptrNoeud->droite, caractere);
}


void compresserTexte(struct noeud* racine, uint8_t* texte, uint8_t* texteCompresse)
{
    uint32_t bitIndex = 0; // position du bit qu’on va écrire

    for (uint32_t i = 0; texte[i] != '\0'; i++) {
        // Cherche le nœud correspondant au caractère
        struct noeud* n = getAdress(racine, texte[i]);
        //if (n == NULL) continue; // sécurité

        // Parcourt tous les bits du code du caractère
        for (int j = n->tailleCode - 1; j >= 0; j--) {
            uint8_t bit = (n->code >> j) & 1; // extrait le bit courant

            // Calcule où écrire ce bit
            uint32_t byteIndex = bitIndex / 8; // quel octet
            uint8_t bitPos = 7 - (bitIndex % 8); // position dans cet octet

            if (bit == 1)
                texteCompresse[byteIndex] |= (1 << bitPos); // met le bit à 1
            else
                texteCompresse[byteIndex] &= ~(1 << bitPos); // met le bit à 0

            bitIndex++;
        }
    }

    printf("\r\nTexte compressé terminé (%lu bits)\r\n", bitIndex);

    // --- AFFICHAGE DU RESULTAT EN BINAIRE ---
    printf("\r\nTexte compressé (%lu bits) : ", bitIndex);

    for (uint32_t i = 0; i < bitIndex; i++) {
        uint32_t byteIndex = i / 8;
        uint8_t bitPos = 7 - (i % 8);
        printf("%d", (texteCompresse[byteIndex] >> bitPos) & 1);
    }

    printf("\r\n");
}



