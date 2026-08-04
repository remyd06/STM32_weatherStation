/**
 * @file    i2c.c
 * @brief   I2C1 master driver (SSD1306 communication).
 */

#include "i2c.h"

/**
 * @brief Configure I2C1 in Standard Mode at 100kHz, APB1=42MHz.
 * @note  Must be called after RCC_Init() and GPIO_Init().
 */
void	I2C1_Init()
{
	I2C1->CR1 &= ~(0b1 << 0);       /* PE: disable peripheral before reconfiguring */

	I2C1->CR2 &= ~(0b111111 << 0);
	I2C1->CR2 |= (0b101010 << 0);   /* FREQ[5:0] = 42: APB1 peripheral clock in MHz */

	I2C1->CCR &= ~(0b111111111111 << 0);
	I2C1->CCR |= (0b11010010 << 0); /* CCR = 210: Sm mode, 100kHz at 42MHz APB1 */

	I2C1->TRISE &= ~(0b111111 << 0);
	I2C1->TRISE |= (0b101011 << 0); /* TRISE = 43: (42MHz x 1000ns / 1000) + 1 */

	I2C1->CR1 |= (0b1 << 0);        /* PE: enable peripheral */
}

/**
 * @brief Blocking write of a single command byte to an SSD1306-style
 *        peripheral (0x00 control byte, then the command).
 * @param I2Cx       I2C peripheral instance.
 * @param periph_addr 7-bit slave address (not pre-shifted).
 * @param cmd        Command byte to send.
 * @return           0 on success, 1 if the slave NACKed the address.
 */
uint8_t	I2C_WriteCommand(I2C_TypeDef *I2Cx, uint8_t periph_addr, uint8_t cmd)
{
	I2Cx->CR1 |= (1 << 8);           /* START */
	while (!(I2Cx->SR1 & (1 << 0))); /* wait SB: start condition generated */

	I2Cx->DR = (periph_addr << 1);   /* address + write (R/W = 0) */
	while (!(I2Cx->SR1 & (1 << 1)))  /* wait ADDR: address acknowledged */
	{
		if (I2Cx->SR1 & (1 << 10))   /* AF: acknowledge failure */
			return (1);              /* !!! FOR LOGS !!! */
	}
	(void)I2Cx->SR2;                 /* clear ADDR by reading SR1 then SR2 */

	while (!(I2Cx->SR1 & (1 << 7))); /* wait TXE: DR empty */
	I2Cx->DR = 0x00;                 /* control byte: next byte is a command */

	while (!(I2Cx->SR1 & (1 << 7))); /* wait TXE: DR empty */
	I2Cx->DR = cmd;

	while (!(I2Cx->SR1 & (1 << 2))); /* wait BTF: byte transfer finished */

	I2Cx->CR1 |= (1 << 9);           /* STOP */

	return (0);                      /* !!! FOR LOGS !!! */
}

/**
 * @brief Blocking write of a data buffer to an SSD1306-style peripheral
 *        (0x40 control byte, then the buffer).
 * @param I2Cx       I2C peripheral instance.
 * @param periph_addr 7-bit slave address (not pre-shifted).
 * @param data       Buffer to send.
 * @param len        Number of bytes in the buffer.
 * @return           0 on success, 1 if the slave NACKed the address.
 */
uint8_t I2C_SendData(I2C_TypeDef *I2Cx, uint8_t periph_addr, uint8_t *data, uint16_t len)
{
	I2Cx->CR1 |= (1 << 8);               /* START */
	while (!(I2Cx->SR1 & (1 << 0)));     /* wait SB: start condition generated */

	I2Cx->DR = (periph_addr << 1);       /* address + write (R/W = 0) */
	while (!(I2Cx->SR1 & (1 << 1)))      /* wait ADDR: address acknowledged */
	{
		if (I2Cx->SR1 & (1 << 10))       /* AF: acknowledge failure */
			return (1);                  /* !!! FOR LOGS !!! */
	}
	(void)I2Cx->SR2;                     /* clear ADDR by reading SR1 then SR2 */

	while (!(I2Cx->SR1 & (1 << 7)));     /* wait TXE: DR empty */
	I2Cx->DR = 0x40;                     /* control byte: next bytes are data */

	for (uint16_t i = 0; i < len; i++)
	{
		while (!(I2Cx->SR1 & (1 << 7))); /* wait TXE: DR empty */
		I2Cx->DR = data[i];
	}

	while (!(I2Cx->SR1 & (1 << 2)));     /* wait BTF: byte transfer finished */

	I2Cx->CR1 |= (1 << 9);               /* STOP */

	return (0);                          /* !!! FOR LOGS !!! */
}
