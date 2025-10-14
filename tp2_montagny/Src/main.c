#include <stdint.h>
#include <stm32f446xx.h>
#include <stdio.h>
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

    uint8_t texte[] = "Une banane";
    uint32_t tab[256];

    occurrence(texte, tab);

    printf("---- Test fonction occurrence ----\r\n");
    for (int c = 0; c < 256; c++) {
        if (tab[c] != 0) {
            printf("'%c' : %lu\r\n", c, tab[c]);
        }
    }

    while (1) {
        SYSTICK_Delay(1000);
        //GPIOA->ODR ^= (1<<5);
        //printf("Hello \r\n");
    }
}
