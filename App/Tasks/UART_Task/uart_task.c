/**
 * @file    uart_task.c
 * @brief   FreeRTOS task forwarding queued sensor strings to USART2.
 */

#include "uart_task.h"

/**
 * @brief Task entry point: blocks on xQueueUart, then transmits whatever
 *        string BME280_Task/TEMT6000_Task posted, unmodified, over USART2.
 */
void	UART_Task()
{
	char	buf[MSG_SIZE];

	for (;;)
	{
		xQueueReceive(xQueueUart, buf, portMAX_DELAY);

		USART_Transmit(USART2, (uint8_t *)buf, strlen(buf));

		UART_task_alive = 1;
	}
}
