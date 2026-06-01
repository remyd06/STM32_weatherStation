#ifndef GPIO_H
#define GPIO_H

# include <stdint.h>
# include "stm32f446xx.h"

void	GPIO_Init();
void	CS_SPI1_BME280_LOW();
void	CS_SPI1_BME280_HIGH();

#endif
