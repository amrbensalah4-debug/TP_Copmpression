#include <stdint.h>
#include <stm32f446xx.h>
#include "main.h"
#include "usart.h"


void USART2_Init(void){
	/* USART2 Init */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	USART2->CR1 |= USART_CR1_UE;
	GPIOA->MODER |= ALT_MODE<<4;					// PA2
	GPIOA->MODER |= ALT_MODE<<6;					// PA3
	GPIOA->AFR[0] |= 7<<8;							// USART2
	GPIOA->AFR[0] |= 7<<12;							// USART2
	USART2->BRR  = 139;								// 115200 - APB1:16Mhz
	USART2->CR1 |= USART_CR1_TE | USART_CR1_RE;		// RX-TX
}

void USART2_TransmitChar(uint8_t data){
	USART2->DR = data;
	while( (USART2->SR & USART_SR_TXE)==0 );
}

uint8_t USART2_ReceiveChar(void){
	while( (USART2->SR & USART_SR_RXNE)==0 );
	return USART2->DR;

}

void USART1_Init(void){
    /* USART1 Init */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;        // Active GPIOA (PA9 / PA10)
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;       // Active l’horloge du périphérique USART1
    USART1->CR1 |= USART_CR1_UE;                // Active le module USART1


    GPIOA->MODER |= ALT_MODE<<18;
    GPIOA->MODER |=  ALT_MODE<<20;
    GPIOA->AFR[1] |= 7<<4;
    GPIOA->AFR[1] |= 7<<8;

    USART1->BRR  = 139;                         // 115200 bauds (si horloge 16 MHz)
    USART1->CR1 |= USART_CR1_TE | USART_CR1_RE; // Active TX et RX
}

void USART1_TransmitChar(uint8_t data){
    USART1->DR = data;                          // Écrit le caractère dans le registre
    while ((USART1->SR & USART_SR_TXE) == 0);   // Attend que la transmission soit terminée
}

uint8_t USART1_ReceiveChar(void){
    while ((USART1->SR & USART_SR_RXNE) == 0);  // Attend la réception d’un caractère
    return USART1->DR;                          // Retourne le caractère reçu
}

void USART1_TransmitInt(uint32_t data) {
    for (int i = 0; i < 4; i++) {
        uint8_t byte = (data >> (8 * (3 - i))) & 0xFF;
        USART1_TransmitChar(byte);
    }
}

uint32_t USART1_ReceiveInt(void) {
    uint32_t value = 0;
    for (int i = 0; i < 4; i++) {
        value = (value << 8) | USART1_ReceiveChar();
    }
    return value;
}

