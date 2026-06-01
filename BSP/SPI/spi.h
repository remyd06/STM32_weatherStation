#ifndef SPI_H
#define SPI_H

# include <stdint.h>
# include "stm32f446xx.h"
# include "gpio.h"

void	SPI1_Init();
void	SPI_Transmit(SPI_TypeDef *SPIx, uint8_t *data);
uint8_t	SPI_Receive(SPI_TypeDef *SPIx);

#endif
