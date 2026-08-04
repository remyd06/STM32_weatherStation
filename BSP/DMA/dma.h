#ifndef DMA_H
#define DMA_H

/**
 * @file    dma.h
 * @brief   DMA2 Stream0 driver moving ADC1 conversions into a RAM buffer.
 */

# include "stm32f446xx.h"

void		DMA2_Init();
uint16_t	*get_DMA2_S0();

#endif
