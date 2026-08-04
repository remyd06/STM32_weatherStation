/**
 * @file    adc.c
 * @brief   ADC1 driver for the TEMT6000 ambient light sensor (channel 9, PB1).
 */

#include "adc.h"

/**
 * @brief Set the common ADC clock prescaler to PCLK2/4.
 * @note  Must be called before ADC1_Init().
 */
void	ADC_Prescaller_Init()
{
	ADC->CCR &= ~(0x3 << 16);	/* ADCPRE[1:0] */
	ADC->CCR |= (1 << 16);
}

/**
 * @brief Configure ADC1 for a single-channel continuous conversion on
 *        channel 9 (PB1/TEMT6000), driven by DMA.
 */
void	ADC1_Init()
{
	ADC1->CR1 = 0;
	ADC1->SMPR2 &= ~(0x7 << 27);	/* SMP9[2:0] */
	ADC1->SMPR2 |= (0x7 << 27);		/* 480 cycles sampling time */
	ADC1->SQR1 = 0;					/* L[3:0] = 0: 1 conversion in the sequence */
	ADC1->SQR3 = 9;					/* SQ1: channel 9 first (and only) conversion */
	ADC1->CR2 = 0;
	ADC1->CR2 |= (1 << 1);			/* CONT: continuous conversion mode */
	ADC1->CR2 |= (1 << 8);			/* DMA: enable DMA requests */
	ADC1->CR2 |= (1 << 9);			/* DDS: issue new DMA request after each conversion */
}

/**
 * @brief Enable ADC1 and trigger the first (software-started) conversion.
 * @note  A short delay is required between ADON and the actual start, to
 *        let the ADC stabilize per the datasheet's tSTAB.
 */
void	ADC1_Start()
{
    ADC1->CR2 |= (1 << 0);	/* ADON: power up the ADC */
    for (volatile int i = 0; i < 1000; i++); /* Wait */
    ADC1->CR2 |= (1 << 30);	/* SWSTART: start conversion */
}
