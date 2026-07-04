#include "gpio.h"

/**
 * @brief Initialize all GPIO pins for the project peripherals.
 *
 * Peripherals configured:
 * - SPI1 (BME280): PA5 (CLK), PA6 (MISO), PA7 (MOSI), PC4 (CS)
 * - USART2: PA2 (TX)
 * - ADC (TEMT6000): PB1 (Analog input)
 */
void	GPIO_Init()
{
	//PA5: SPI/BME280 SCL pin (Clock)
	GPIOA->MODER &= ~(0x3 << 10);	// Mode register[1:0]: 10 = Alternate function
	GPIOA->MODER |= (0x2 << 10);
	GPIOA->AFR[0] &= ~ (0xF << 20);	// Alternate function register[3:0]: [0 = low, 1 = high], AFRL5 for pin5
	GPIOA->AFR[0] |=  (0x5 << 20);
	GPIOA->OTYPER &= ~(1 << 5);		// Port output type register: 0 = open push-pull (reset state)
	GPIOA->OSPEEDR &= ~(3 << 10);	// Port output speed register[1:0]: 10 = fast speed
	GPIOA->OSPEEDR |= (3 << 10);
	GPIOA->PUPDR &= ~(3 << 10);		// Port pull-up/pull-down register[1:0]: 00 = no pull

	//PA6: SPI/BME280 SDO pin (AF SPI1_MISO, receiver from slave)
	GPIOA->MODER &= ~(0x3 << 12);
	GPIOA->MODER |= (0x2 << 12);
	GPIOA->AFR[0] &= ~ (0xF << 24);
	GPIOA->AFR[0] |=  (0x5 << 24);
	GPIOA->OTYPER &= ~(1 << 6);
	GPIOA->OSPEEDR &= ~(3 << 12);
	GPIOA->OSPEEDR |= (3 << 12);
	GPIOA->PUPDR &= ~(3 << 12);
	GPIOA->PUPDR |= (1 << 12);

	//PA7: SPI/BME280 SDA pin (AF SPI1_MOSI, transmitter to slave)
	GPIOA->MODER &= ~(0x3 << 14);
	GPIOA->MODER |= (0x2 << 14);
	GPIOA->AFR[0] &= ~ (0xF << 28);
	GPIOA->AFR[0] |=  (0x5 << 28);
	GPIOA->OTYPER &= ~(1 << 7);
	GPIOA->OSPEEDR &= ~(3 << 14);
	GPIOA->OSPEEDR |= (3 << 14);
	GPIOA->PUPDR &= ~(3 << 14);

	//PC4: SPI/BME280 CSB pin (CS LOW or CS HIGH)
	GPIOC->BSRR = (1 << 4);
	GPIOC->MODER &= ~(0x3 << 8);
	GPIOC->MODER |= (0x1 << 8);
	GPIOC->OTYPER &= ~(1 << 4);
	GPIOC->OSPEEDR &= ~(3 << 8);
	GPIOC->OSPEEDR |= (2 << 8);
	GPIOC->PUPDR &= ~(3 << 8);
	GPIOC->PUPDR |= (1 << 8);

	//PA2: USART TX (Transmitter to PC)
	GPIOA->MODER &= ~(0x3 << 4);
	GPIOA->MODER |= (0x2 << 4);
	GPIOA->AFR[0] &= ~ (0xF << 8);
	GPIOA->AFR[0] |=  (0x7 << 8);
	GPIOA->OTYPER &= ~(1 << 2);
	GPIOA->OSPEEDR &= ~(3 << 4);
	GPIOA->OSPEEDR |= (2 << 4);
	GPIOA->PUPDR &= ~(3 << 4);
	GPIOA->PUPDR |= (1 << 4);

	//PB1: ADC/TEMT6000 S pin (Analog receiver)
	GPIOB->MODER &= ~(0x3 << 2);
	GPIOB->MODER |= (0x3 << 2);
	GPIOB->PUPDR &= ~(0x3 << 2);

	//PB6: I2C1/SSD1306 SCL pin (Clock)
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

	//PB7: I2C1/SSD1306 SDA Pin (Bidirectional serial data)
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
