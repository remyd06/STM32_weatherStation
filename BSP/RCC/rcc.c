/**
 * @file    rcc.c
 * @brief   Clock enable for GPIO ports and peripherals used by the station.
 */

#include "rcc.h"

/**
 * @brief Enable the AHB1/APB1/APB2 clocks required by the application
 *        (GPIOA/B/C, USART2, SPI1, DMA2, ADC1, I2C1).
 * @note  Must be called once, before any peripheral init.
 */
void	RCC_Init()
{
	/* GPIO clocks */
	RCC->AHB1ENR |= (1 << 0);	//GPIOA
	RCC->AHB1ENR |= (1 << 1);	//GPIOB
	RCC->AHB1ENR |= (1 << 2);	//GPIOC

	/* Peripheral clocks */
	RCC->APB1ENR |= (1 << 17);	//USART2
	RCC->APB2ENR |= (1 << 12);	//SPI1
	RCC->AHB1ENR |= (1 << 22);	//DMA2
	RCC->APB2ENR |= (1 << 8); 	//ADC1
	RCC->APB1ENR |= (1 << 21);	//I2C1
}
