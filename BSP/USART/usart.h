#ifndef USART_H
#define USART_H

/**
 * @file    usart.h
 * @brief   USART2 driver used as the UART link to the PC-side data pipeline.
 */

# include <stdint.h>
# include "stm32f446xx.h"

void	USART2_Init();
void	USART_Transmit(USART_TypeDef *USARTx, uint8_t *data, uint16_t size);

#endif
