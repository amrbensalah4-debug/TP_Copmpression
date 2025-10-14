#include <stdlib.h>
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
