#include "rcc.h"

void	RCC_Init()
{
	//GPIO
	RCC->AHB1ENR |= (1 << 0);	//GPIOA
	RCC->AHB1ENR |= (1 << 1);	//GPIOB
	RCC->AHB1ENR |= (1 << 2);	//GPIOC

	//PERIPHERALS
	RCC->APB1ENR |= (1 << 17);	//USART2
	RCC->APB2ENR |= (1 << 12);	//SPI1
	RCC->AHB1ENR |= (1 << 22);	//DMA2
	RCC->APB2ENR |= (1 << 8); 	//ADC1
	RCC->APB1ENR |= (1 << 21);	//I2C1
}

