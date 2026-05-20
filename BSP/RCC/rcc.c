#include "rcc.h"
#include "stm32f446xx.h"

void	RCC_Init()
{
	//GPIO
	RCC->AHB1ENR |= (1 << 0);	//GPIOA
	RCC->AHB1ENR |= (1 << 3);	//GPIOC

	//PERIPHERALS
	RCC->APB2LPENR |= (1 << 12); //SPI1
}

