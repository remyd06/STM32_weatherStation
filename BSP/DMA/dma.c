/**
 * @file    dma.c
 * @brief   DMA2 Stream0 driver moving ADC1 conversions into a RAM buffer.
 */

#include "dma.h"

static uint16_t buf[16];

/**
 * @brief Configure DMA2 Stream0 (ADC1 request) to transfer half-words from
 *        ADC1->DR into buf[], circular mode, then enable the stream.
 * @note  Must be called after ADC1_Init() and before ADC1_Start().
 */
void	DMA2_Init()
{
	DMA2_Stream0->CR &= ~(1 << 0);
	while (DMA2_Stream0->CR & (1 << 0)); 		/* wait for EN to clear before reconfiguring */
	DMA2_Stream0->PAR = (uint32_t)&ADC1->DR;	/* PAR: source = ADC1 data register */
	DMA2_Stream0->M0AR = (uint32_t)&buf;		/* M0AR: destination = buf[] */
	DMA2_Stream0->NDTR = 16;					/* NDTR: 16 transfers per circular pass */
	DMA2_Stream0->CR = 0;
	DMA2_Stream0->CR |= (0x1 << 13);			/* MSIZE: 16-bit memory data size */
	DMA2_Stream0->CR |= (0x1 << 11);			/* PSIZE: 16-bit peripheral data size */
	DMA2_Stream0->CR |= (1 << 8);				/* CIRC: circular mode */
	DMA2_Stream0->CR |= (1 << 0);				/* EN: stream enable */
}

/**
 * @brief Access the DMA2 Stream0 destination buffer.
 * @return Pointer to the 16-entry buffer written by DMA2_Init().
 */
uint16_t	*get_DMA2_S0()
{
	return (buf);
}
