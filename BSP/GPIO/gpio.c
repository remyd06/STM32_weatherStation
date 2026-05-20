#include "stm32f446xx.h"

void	GPIO_Init()
{
	//PA5
	GPIOA->MODER &= ~(0x3 << 10);
	GPIOA->MODER |= (0x2 << 10);
	GPIOA->AFR[0] &= ~ (0xF << 20); // 20 car pa5 * groupe de 4 bits = 20 -> 23
	GPIOA->AFR[0] |=  (0x5 << 20);

	//PA6
	GPIOA->MODER &= ~(0x3 << 12);
	GPIOA->MODER |= (0x2 << 12);
	GPIOA->AFR[0] &= ~ (0xF << 24);
	GPIOA->AFR[0] |=  (0x5 << 24);

	//PA7
	GPIOA->MODER &= ~(0x3 << 14);
	GPIOA->MODER |= (0x2 << 14);
	GPIOA->AFR[0] &= ~ (0xF << 28);
	GPIOA->AFR[0] |=  (0x5 << 28);

	//PC4
	GPIOC->MODER &= ~(0x3 << 8);
	GPIOC->MODER |= (0x1 << 8);
	GPIOC->BSRR = (1 << 4);
}
