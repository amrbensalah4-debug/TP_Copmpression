#ifndef USART_H_
#define USART_H_


void USART2_Init(void);
void USART2_TransmitChar(uint8_t data);
uint8_t USART2_ReceiveChar(void);
void USART1_Init(void);
void USART1_TransmitChar(uint8_t data);
uint8_t USART1_ReceiveChar(void);
void USART1_TransmitInt(uint32_t data);
uint32_t USART1_ReceiveInt(void);

#endif
