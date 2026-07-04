#include "adc.h"

void	ADC_Prescaller_Init()
{
	ADC->CCR &= ~(0x3 << 16);
	ADC->CCR |= (1 << 16);
}

void	ADC1_Init()
{
	ADC1->CR1 = 0;
	ADC1->SMPR2 &= ~(0x7 << 27);
	ADC1->SMPR2 |= (0x7 << 27);
	ADC1->SQR1 = 0;
	ADC1->SQR3 = 9;
	ADC1->CR2 = 0;
	ADC1->CR2 |= (1 << 1);
	ADC1->CR2 |= (1 << 8);
	ADC1->CR2 |= (1 << 9);
}

void	ADC1_Start()
{
    ADC1->CR2 |= (1 << 0);
    for (volatile int i = 0; i < 1000; i++);
    ADC1->CR2 |= (1 << 30);
}
