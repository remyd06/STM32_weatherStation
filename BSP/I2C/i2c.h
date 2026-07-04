#ifndef I2C_H
#define I2C_H

# include "stm32f446xx.h"

# define SSD1306_ADDR 0x3C

void	I2C1_Init();
uint8_t	I2C_WriteCommand(I2C_TypeDef *I2Cx, uint8_t periph_addr, uint8_t cmd);
uint8_t I2C_SendData(I2C_TypeDef *I2Cx, uint8_t periph_addr, uint8_t *data, uint16_t len);

#endif
