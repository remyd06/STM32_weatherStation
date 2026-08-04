/**
 * @file    spi.c
 * @brief   SPI1 master driver (BME280 communication).
 */

#include "spi.h"

/**
 * @brief Configure SPI1 as master, software NSS, fPCLK/256, mode 0 (CPOL=0, CPHA=0).
 * @note  Must be called after RCC_Init() and GPIO_Init().
 */
void	SPI1_Init()
{
	SPI1->CR1 = 0;
	SPI1->CR1 |= (1 << 2);		/* MSTR: master mode */
	SPI1->CR1 |= (0b111 << 3);	/* BR[2:0]: fPCLK/256 */
	SPI1->CR1 |= (1 << 9);		/* SSM: software slave management */
	SPI1->CR1 |= (1 << 8);		/* SSI: internal slave select held high */
	SPI1->CR1 |= (1 << 6);		/* SPE: peripheral enable */
}

/**
 * @brief Blocking transmit of a single byte.
 * @param SPIx SPI peripheral instance.
 * @param data Pointer to the byte to send.
 */
void	SPI_Transmit(SPI_TypeDef *SPIx, uint8_t *data)
{
	while (!(SPIx->SR & (1 << 1)));	/* wait TXE: transmit buffer empty */
	SPIx->DR = *data;
	while (SPIx->SR & (1 << 7));		/* wait BSY clear: transfer complete */
}

/**
 * @brief Blocking receive of a single byte.
 * @param SPIx SPI peripheral instance.
 * @return     Byte read from the peripheral's data register.
 */
uint8_t	SPI_Receive(SPI_TypeDef *SPIx)
{
	uint8_t	data;

	while (!(SPIx->SR & (1 << 0)));	/* wait RXNE: receive buffer not empty */
	data = SPIx->DR;
	while (SPIx->SR & (1 << 7));		/* wait BSY clear: transfer complete */
	return (data);
}
