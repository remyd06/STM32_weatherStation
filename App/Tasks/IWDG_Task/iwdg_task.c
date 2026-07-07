#include "iwdg_task.h"

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
			IWDG->KR = 0xAAAA;
			BME280_task_alive = 0;
			TEMT6000_task_alive = 0;
			SSD1306_task_alive = 0;
			UART_task_alive = 0;
		}

		vTaskDelay(pdMS_TO_TICKS(100));
	}
}
