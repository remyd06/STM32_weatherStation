#include "stm32f446xx.h"

void	SPI1_Init()
{
	SPI1->CR1 = 0;
	SPI1->CR1 |= (1 << 2);
	SPI1->CR1 |= (0b111 << 3);
	SPI1->CR1 |= (1 << 9);
	SPI1->CR1 |= (1 << 8);
	SPI1->CR1 |= (1 << 6);
}
