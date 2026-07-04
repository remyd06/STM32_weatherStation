#include "i2c.h"

void	I2C1_Init()
{
	I2C1->CR1 &= ~(0b1 << 0);	// Shut off the peripheral for modifying
	I2C1->CR2 &= ~(0b111111 << 0);
	I2C1->CR2 |= (0b101010 << 0);	// 42MHz -> is the APB1 Peripheral clock needed by CR2
	I2C1->CCR &= ~(0b111111111111 << 0);
	I2C1->CCR |= (0b11010010 << 0);		// 100KHz -> SM mode: Clock control register
	I2C1->TRISE &= ~(0b111111 << 0);
	I2C1->TRISE |= (0b101011 << 0);		//43 -> (PCLK1_MHz × Trise_max_ns / 1000) + 1: State waiter tolerance
	I2C1->CR1 |= (0b1 << 0);	// Power on the peripheral
}

uint8_t	I2C_WriteCommand(I2C_TypeDef *I2Cx, uint8_t periph_addr, uint8_t cmd)
{
	I2Cx->CR1 |= (1 << 8);						// Start
	while (!(I2Cx->SR1 & (1 << 0)));			// Wait the start

	I2Cx->DR = (periph_addr << 1);				// Send the adress and keep free the bit R/W 0
	while (!(I2Cx->SR1 & (1 << 1)))				// wait the response
	{
		if (I2Cx->SR1 & (1 << 10))				// If AF bit (failure) is set, return
			return (1);							// !!! FOR LOGS !!!
	}
	(void)I2Cx->SR2;							// Clear flags

	while (!(I2Cx->SR1 & (1 << 7)));			// Wait DR is empty
	I2Cx->DR = 0x00;							// 0x00 indicate to the peripheral next instruction is a command

	while (!(I2Cx->SR1 & (1 << 7)));			// Wait DR is empty
	I2Cx->DR = cmd;

	while (!(I2Cx->SR1 & (1 << 2)));			// Wait BTF flag, to know if the command is all transmitted

	I2Cx->CR1 |= (1 << 9);						// Stop

	return (0);									// !!! FOR LOGS !!!
}

uint8_t I2C_SendData(I2C_TypeDef *I2Cx, uint8_t periph_addr, uint8_t *data, uint16_t len)
{
	I2Cx->CR1 |= (1 << 8);						// Start
	while (!(I2Cx->SR1 & (1 << 0)));			// Wait the start

	I2Cx->DR = (periph_addr << 1);				// Send the adress and keep free the bit R/W 0
	while (!(I2Cx->SR1 & (1 << 1)))				// wait the response
	{
		if (I2Cx->SR1 & (1 << 10))				// If AF bit (failure) is set, return
			return (1);							// !!! FOR LOGS !!!
	}
	(void)I2Cx->SR2;							// Clear flags

	while (!(I2Cx->SR1 & (1 << 7)));			// Wait DR is empty
	I2Cx->DR = 0x40;							// control byte : ce qui suit est de la DATA (pas une commande)

	for (uint16_t i = 0; i < len; i++)
	{
		while (!(I2Cx->SR1 & (1 << 7)));		// Wait DR is empty
		I2Cx->DR = data[i];
	}

	while (!(I2Cx->SR1 & (1 << 2)));			// Wait BTF flag, to know if the command is all transmitted

	I2Cx->CR1 |= (1 << 9);						// Stop

	return (0);									// !!! FOR LOGS !!!
}

