/**
 * @file    gpio.c
 * @brief   Pin configuration for the SPI/BME280, I2C/SSD1306, USART and
 *          ADC/TEMT6000 interfaces.
 */

#include "gpio.h"

/**
 * @brief Configure every GPIO pin used by the application
 *        (mode, alternate function, output type/speed,
 *        pull-up/down).
 *
 * @note Must be called after RCC_Init(), once, at startup.
 *
 * Register reference (applies to every pin below):
 *   - MODER   [1:0] : 00 = input,
 *                     01 = output,
 *                     10 = alternate function,
 *                     11 = analog
 *
 *   - AFR     [3:0] : alternate function number
 *                     (AFRL for pins 0-7,
 *                      AFRH for pins 8-15)
 *
 *   - OTYPER  [0]   : 0 = push-pull,
 *                     1 = open-drain
 *
 *   - OSPEEDR [1:0] : output speed,
 *                     00 = low ... 11 = very high
 *
 *   - PUPDR   [1:0] : 00 = none,
 *                     01 = pull-up,
 *                     10 = pull-down
 */
void	GPIO_Init()
{
	/* PA5: SPI1/BME280 SCK (clock), alternate function 5, no pull */
	GPIOA->MODER &= ~(0b11 << 10);
	GPIOA->MODER |= (0b10 << 10);
	GPIOA->AFR[0] &= ~ (0b1111 << 20);
	GPIOA->AFR[0] |=  (0b0101 << 20);
	GPIOA->OTYPER &= ~(1 << 5);
	GPIOA->OSPEEDR &= ~(3 << 10);
	GPIOA->OSPEEDR |= (3 << 10);
	GPIOA->PUPDR &= ~(3 << 10);

	/* PA6: SPI1_MISO/BME280 SDO (slave to master), pull-up */
	GPIOA->MODER &= ~(0b11 << 12);
	GPIOA->MODER |= (0b10 << 12);
	GPIOA->AFR[0] &= ~ (0b1111 << 24);
	GPIOA->AFR[0] |=  (0b0101 << 24);
	GPIOA->OTYPER &= ~(1 << 6);
	GPIOA->OSPEEDR &= ~(3 << 12);
	GPIOA->OSPEEDR |= (3 << 12);
	GPIOA->PUPDR &= ~(3 << 12);
	GPIOA->PUPDR |= (1 << 12);

	/* PA7: SPI1_MOSI/BME280 SDA (master to slave), no pull */
	GPIOA->MODER &= ~(0b11 << 14);
	GPIOA->MODER |= (0b10 << 14);
	GPIOA->AFR[0] &= ~ (0b1111 << 28);
	GPIOA->AFR[0] |=  (0b0101 << 28);
	GPIOA->OTYPER &= ~(1 << 7);
	GPIOA->OSPEEDR &= ~(3 << 14);
	GPIOA->OSPEEDR |= (3 << 14);
	GPIOA->PUPDR &= ~(3 << 14);

	/* PC4: BME280 CSB, general-purpose output, idle HIGH (chip not selected) */
	GPIOC->BSRR = (1 << 4);
	GPIOC->MODER &= ~(0b11 << 8);
	GPIOC->MODER |= (0b01 << 8);
	GPIOC->OTYPER &= ~(1 << 4);
	GPIOC->OSPEEDR &= ~(3 << 8);
	GPIOC->OSPEEDR |= (2 << 8);
	GPIOC->PUPDR &= ~(3 << 8);
	GPIOC->PUPDR |= (1 << 8);

	/* PA2: USART2_TX, alternate function 7, pull-up */
	GPIOA->MODER &= ~(0b11 << 4);
	GPIOA->MODER |= (0b10 << 4);
	GPIOA->AFR[0] &= ~ (0b1111 << 8);
	GPIOA->AFR[0] |=  (0b0111 << 8);
	GPIOA->OTYPER &= ~(1 << 2);
	GPIOA->OSPEEDR &= ~(3 << 4);
	GPIOA->OSPEEDR |= (2 << 4);
	GPIOA->PUPDR &= ~(3 << 4);
	GPIOA->PUPDR |= (1 << 4);

	/* PB1: ADC1 input, TEMT6000 analog output, no pull */
	GPIOB->MODER &= ~(0b11 << 2);
	GPIOB->MODER |= (0b11 << 2);
	GPIOB->PUPDR &= ~(0b11 << 2);

	/* PB6: I2C1_SCL/SSD1306 clock, alternate function 4, open-drain, pull-up */
	GPIOB->MODER &= ~(0b11 << 12);
	GPIOB->MODER |= (0b10 << 12);
	GPIOB->AFR[0] &= ~(0b1111 << 24);
	GPIOB->AFR[0] |= (0b0100 << 24);
	GPIOB->OTYPER &= ~(0b1 << 6);
	GPIOB->OTYPER |= (0b1 << 6);
	GPIOB->PUPDR &= ~(0b11 << 12);
	GPIOB->PUPDR |= (0b01 << 12);
	GPIOB->OSPEEDR &= ~(0b11 << 12);
	GPIOB->OSPEEDR |= (0b11 << 12);

	/* PB7: I2C1_SDA/SSD1306 data, alternate function 4, open-drain, pull-up */
	GPIOB->MODER &= ~(0b11 << 14);
	GPIOB->MODER |= (0b10 << 14);
	GPIOB->AFR[0] &= ~(0b1111 << 28);
	GPIOB->AFR[0] |= (0b0100 << 28);
	GPIOB->OTYPER &= ~(0b1 << 7);
	GPIOB->OTYPER |= (0b1 << 7);
	GPIOB->PUPDR &= ~(0b11 << 14);
	GPIOB->PUPDR |= (0b01 << 14);
	GPIOB->OSPEEDR &= ~(0b11 << 14);
	GPIOB->OSPEEDR |= (0b11 << 14);
}
