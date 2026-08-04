/**
 * @file    temt6000_task.c
 * @brief   FreeRTOS task publishing the TEMT6000 ambient light reading.
 */

#include "temt6000_task.h"

/**
 * @brief Task entry point: every 1s, reads the latest DMA-converted ADC1
 *        sample (TEMT6000 lux) and publishes it to the UART and OLED queues.
 * @note  No local ADC read is triggered here: ADC1 runs continuously and
 *        DMA2 keeps the buffer returned by get_DMA2_S0() up to date.
 */
void	TEMT6000_Task()
{
	char	buf[MSG_SIZE];

	for (;;)
	{
		snprintf(buf, sizeof(buf), "L:%d\r\n", *get_DMA2_S0());
		xQueueSend(xQueueUart, buf, portMAX_DELAY);
		xQueueSend(xQueueOled, buf, portMAX_DELAY);

		TEMT6000_task_alive = 1;

		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}
