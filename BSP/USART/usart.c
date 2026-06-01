#include "stm32f446xx.h"

void	USART_Init()
{
	USART2->BRR = 364;
	USART2->CR1 = 0;
	USART2->CR1 |= (1 << 3);
	USART2->CR1 |= (1 << 13);
}

void	USART_Transmit(USART_TypeDef *USARTx, uint8_t *data, uint16_t size)
{
    for (uint16_t i = 0; i < size; i++)
    {
        while (!(USARTx->SR & (1 << 7)));
        	USARTx->DR = data[i];
    }
}
