/**
 * @file    iwdg.c
 * @brief   Hardware independent watchdog (IWDG) driver.
 */

#include "iwdg.h"

/**
 * @brief Arm the IWDG with a ~8.19s timeout (prescaler /64, reload 4095,
 *        LSI = 32kHz).
 * @note  Once started, the IWDG cannot be stopped except by a reset.
 */
void	IWDG_Init()
{
	IWDG->KR = 0x5555;           /* unlock PR & RLR registers for writing */
	while (IWDG->SR & 1);        /* wait until the prescaler update is not pending */
	IWDG->PR = 0b100;            /* prescaler /64 */
	while (IWDG->SR & (1 << 1)); /* wait until the reload value update is not pending */
	IWDG->RLR = 0xFFF;           /* reload value: 4095 (+1) */
	IWDG->KR = 0xCCCC;           /* start the watchdog: reload time = 4096 x 64 / 32000 */
}
