#include "iwdg.h"

void	IWDG_Init()
{
	IWDG->KR = 0x5555;				// Unlock PR & RLR register
	while (IWDG->SR & 1);			// Wait the hardware to set the prescaller if an update of the reload value is not ongoing
	IWDG->PR = 0b100;				// Set prescaller by 64
	while (IWDG->SR & (1 << 1));	// Wait the hardware to set the counter reload value if an update of the reload value is not ongoing
	IWDG->RLR = 0xFFF;				// Set the reload value by 4095 (+1)
	IWDG->KR = 0xCCCC;				// Start the Watchdog (Watchdog reload time = 4096x64/32000 (32000 = 32KHz LSI frequency))
}
