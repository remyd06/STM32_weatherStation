#include "spi.h"

void	SPI1_Init()
{
	SPI1->CR1 = 0;
	SPI1->CR1 |= (1 << 2);
	SPI1->CR1 |= (0b111 << 3);
	SPI1->CR1 |= (1 << 9);
	SPI1->CR1 |= (1 << 8);
	SPI1->CR1 |= (1 << 6);
}

void	SPI_Transmit(SPI_TypeDef *SPIx, uint8_t *data)
{
	while (!(SPIx->SR & (1 << 1)));
	SPIx->DR = *data;
	while (SPIx->SR & (1 << 7));
}

uint8_t	SPI_Receive(SPI_TypeDef *SPIx)
{
	uint8_t	data;

	while (!(SPIx->SR & (1 << 0)));
	data = SPIx->DR;
	while (SPIx->SR & (1 << 7));
	return (data);
}
