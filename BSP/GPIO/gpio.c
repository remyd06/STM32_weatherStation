#include "gpio.h"

void	GPIO_Init()
{
	//PA5
	GPIOA->MODER &= ~(0x3 << 10);
	GPIOA->MODER |= (0x2 << 10);
	GPIOA->AFR[0] &= ~ (0xF << 20);
	GPIOA->AFR[0] |=  (0x5 << 20);
	GPIOA->OTYPER &= ~(1 << 5);
	GPIOA->OSPEEDR &= ~(3 << 10);
	GPIOA->OSPEEDR |= (3 << 10);
	GPIOA->PUPDR &= ~(3 << 10);

	//PA6
	GPIOA->MODER &= ~(0x3 << 12);
	GPIOA->MODER |= (0x2 << 12);
	GPIOA->AFR[0] &= ~ (0xF << 24);
	GPIOA->AFR[0] |=  (0x5 << 24);
	GPIOA->OTYPER &= ~(1 << 6);
	GPIOA->OSPEEDR &= ~(3 << 12);
	GPIOA->OSPEEDR |= (3 << 12);
	GPIOA->PUPDR &= ~(3 << 12);
	GPIOA->PUPDR |= (1 << 12);

	//PA7
	GPIOA->MODER &= ~(0x3 << 14);
	GPIOA->MODER |= (0x2 << 14);
	GPIOA->AFR[0] &= ~ (0xF << 28);
	GPIOA->AFR[0] |=  (0x5 << 28);
	GPIOA->OTYPER &= ~(1 << 7);
	GPIOA->OSPEEDR &= ~(3 << 14);
	GPIOA->OSPEEDR |= (3 << 14);
	GPIOA->PUPDR &= ~(3 << 14);

	//PC4
	GPIOC->BSRR = (1 << 4);
	GPIOC->MODER &= ~(0x3 << 8);
	GPIOC->MODER |= (0x1 << 8);
	GPIOC->OTYPER &= ~(1 << 4);
	GPIOC->OSPEEDR &= ~(3 << 8);
	GPIOC->OSPEEDR |= (2 << 8);
	GPIOC->PUPDR &= ~(3 << 8);
	GPIOC->PUPDR |= (1 << 8);

	//PA2
	GPIOA->MODER &= ~(0x3 << 4);
	GPIOA->MODER |= (0x2 << 4);
	GPIOA->AFR[0] &= ~ (0xF << 8);
	GPIOA->AFR[0] |=  (0x7 << 8);
	GPIOA->OTYPER &= ~(1 << 2);
	GPIOA->OSPEEDR &= ~(3 << 4);
	GPIOA->OSPEEDR |= (2 << 4);
	GPIOA->PUPDR &= ~(3 << 4);
	GPIOA->PUPDR |= (1 << 4);
}

void	CS_SPI1_BME280_LOW()
{
	GPIOC->BSRR = (1 << 20);
}

void	CS_SPI1_BME280_HIGH()
{
	GPIOC->BSRR = (1 << 4);
}
