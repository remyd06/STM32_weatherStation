/**
 * @file    iwdg_task.c
 * @brief   Software watchdog layer: monitors the other FreeRTOS tasks'
 *          liveness flags and only kicks the hardware IWDG when all of
 *          them have reported alive within TASK_TIMEOUT_MS.
 */

#include "iwdg_task.h"

/**
 * @brief Task entry point: every 100ms, checks each sensor/display/UART task
 *        for a timeout, logs a warning over UART if one is stuck, and kicks
 *        the IWDG once all four tasks have checked in during the current
 *        window (then clears the flags for the next window).
 * @note  Detects task freeze/starvation only, not invalid sensor data; the
 *        latter needs separate range checks or stuck-value detection.
 * @note  Runs at the highest task priority so a peripheral task blocked on
 *        I2C/SPI cannot starve the watchdog check.
 */
void	IWDG_Task()
{
	volatile uint32_t	last_time_seen_bme280 = xTaskGetTickCount();
	volatile uint32_t	last_time_seen_temt6000 = xTaskGetTickCount();
	volatile uint32_t	last_time_seen_ssd1306 = xTaskGetTickCount();
	volatile uint32_t	last_time_seen_uart = xTaskGetTickCount();

	for (;;)
	{
		if ((xTaskGetTickCount() - last_time_seen_bme280) > TASK_TIMEOUT_MS)
			xQueueSend(xQueueUart, "LOG WARNING: BME280 task timeout\r\n", portMAX_DELAY);
		else if (BME280_task_alive)
			last_time_seen_bme280 = xTaskGetTickCount();

		if ((xTaskGetTickCount() - last_time_seen_temt6000) > TASK_TIMEOUT_MS)
			xQueueSend(xQueueUart, "LOG WARNING: TEMT6000 task timeout\r\n", portMAX_DELAY);
		else if (TEMT6000_task_alive)
			last_time_seen_temt6000 = xTaskGetTickCount();

		if ((xTaskGetTickCount() - last_time_seen_ssd1306) > TASK_TIMEOUT_MS)
			xQueueSend(xQueueUart, "LOG WARNING: SSD1306 task timeout\r\n", portMAX_DELAY);
		else if (SSD1306_task_alive)
			last_time_seen_ssd1306 = xTaskGetTickCount();

		if ((xTaskGetTickCount() - last_time_seen_uart) > TASK_TIMEOUT_MS)
			xQueueSend(xQueueUart, "LOG WARNING: UART task timeout\r\n", portMAX_DELAY);
		else if (UART_task_alive)
			last_time_seen_uart = xTaskGetTickCount();

		if (BME280_task_alive && TEMT6000_task_alive && SSD1306_task_alive && UART_task_alive)
		{
			IWDG->KR = 0xAAAA; /* refresh: reload the IWDG counter */
			BME280_task_alive = 0;
			TEMT6000_task_alive = 0;
			SSD1306_task_alive = 0;
			UART_task_alive = 0;
		}

		vTaskDelay(pdMS_TO_TICKS(100));
	}
}
