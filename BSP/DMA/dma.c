#include "dma.h"

static uint16_t buf[16];

void	DMA_Init()
{
	// DMA2, Stream 0
	DMA2_Stream0->CR &= ~(1 << 0);
	while (DMA2_Stream0->CR & (1 << 0)); // attendre si transfert en cours pour desactiver
	DMA2_Stream0->PAR = (uint32_t)&ADC1->DR;
	DMA2_Stream0->M0AR = (uint32_t)&buf;
	DMA2_Stream0->NDTR = 16;
	DMA2_Stream0->CR = 0;
	DMA2_Stream0->CR |= (0x1 << 13);
	DMA2_Stream0->CR |= (0x1 << 11);
	DMA2_Stream0->CR |= (1 << 8);
	DMA2_Stream0->CR |= (1 << 0);
}

uint16_t	*get_DMA2_S0()
{
	return (buf);
}
