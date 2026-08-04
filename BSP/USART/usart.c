/**
 * @file    usart.c
 * @brief   USART2 driver used as the UART link to the PC-side data pipeline.
 */

#include "usart.h"

/**
 * @brief Configure USART2 at ~115200 baud (BRR=364 for APB1=42MHz), 8N1,
 *        transmitter only.
 * @note  Must be called after RCC_Init() and GPIO_Init().
 */
void	USART2_Init()
{
	USART2->BRR = 364;
	USART2->CR1 = 0;
	USART2->CR1 |= (1 << 3);	/* TE: transmitter enable */
	USART2->CR1 |= (1 << 13);	/* UE: USART enable */
}

/**
 * @brief Blocking transmit of a buffer, one byte at a time.
 * @param USARTx USART peripheral instance.
 * @param data   Buffer to send.
 * @param size   Number of bytes to send.
 */
void	USART_Transmit(USART_TypeDef *USARTx, uint8_t *data, uint16_t size)
{
    for (uint16_t i = 0; i < size; i++)
    {
        while (!(USARTx->SR & (1 << 7)));	/* wait TXE: transmit buffer empty */
        USARTx->DR = data[i];
    }
}
