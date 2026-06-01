#ifndef USART_H
#define USART_H

# include <stdint.h>
# include "stm32f446xx.h"

void	USART_Init();
void	USART_Transmit(USART_TypeDef *USARTx, uint8_t *data, uint16_t size);

#endif
