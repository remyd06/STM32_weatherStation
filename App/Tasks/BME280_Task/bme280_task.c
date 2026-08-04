/**
 * @file    bme280_task.c
 * @brief   FreeRTOS task periodically reading the BME280 and publishing
 *          formatted T/P/H strings to the UART and OLED queues.
 */

#include "bme280_task.h"

/**
 * @brief Task entry point: configures the BME280 once, then loops forever
 *        reading and formatting temperature, pressure and humidity at 1Hz.
 * @note  Signals BME280_task_alive after each successful cycle, polled by
 *        IWDG_Task.
 */
void	BME280_Task()
{
	uint8_t			data[8];
	char			buf[MSG_SIZE];

	int32_t			int_part;
	int32_t			dec_part;

	BME280_calib_t	calib;
	BME280_data_t	data_struct;

	BME280_GetTRIM(&calib);
	BME280_SetMODE(0b11, 0b001, 0b001, 0b001);    /* normal mode, x1 oversampling on P/T/H */

	for (;;)
	{
		BME280_GetDATA(data);
		BME280_ConvertDATA(data, &calib, &data_struct);

		int_part = data_struct.temp / 100;        /* temp is DegC x100 */
		dec_part = data_struct.temp % 100;
		snprintf(buf, sizeof(buf), "T:%ld.%ld\r\n", int_part, dec_part);
		xQueueSend(xQueueUart, buf, portMAX_DELAY);
		xQueueSend(xQueueOled, buf, portMAX_DELAY);

		int_part = (data_struct.pres / 256) /100; /* pres is Pa as Q24.8: /256 -> Pa, /100 -> hPa */
		snprintf(buf, sizeof(buf), "P:%ld\r\n", int_part);
		xQueueSend(xQueueUart, buf, portMAX_DELAY);
		xQueueSend(xQueueOled, buf, portMAX_DELAY);

		int_part = data_struct.hum / 1000;        /* hum is %RH as Q22.10 */
		dec_part = (data_struct.hum % 1000) / 10;
		snprintf(buf, sizeof(buf), "H:%ld.%ld\r\n", int_part, dec_part);
		xQueueSend(xQueueUart, buf, portMAX_DELAY);
		xQueueSend(xQueueOled, buf, portMAX_DELAY);

		BME280_task_alive = 1;

		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}
