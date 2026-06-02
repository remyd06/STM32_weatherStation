#include "rcc.h"

void	RCC_Init()
{
	//GPIO
	RCC->AHB1ENR |= (1 << 0);	//GPIOA
	RCC->AHB1ENR |= (1 << 2);	//GPIOC

	//USART
	RCC->APB1ENR |= (1 << 17);	//USART2

	//PERIPHERALS
	RCC->APB2ENR |= (1 << 12); //SPI1
	RCC->AHB1ENR |= (1 << 22); //DMA2
	RCC->APB2ENR |= (1 << 8);  //ADC1

}

