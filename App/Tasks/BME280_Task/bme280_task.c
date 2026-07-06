#include "bme280_task.h"

void	BME280_Task()
{
	uint8_t			data[8];
	char			buf[MSG_SIZE];

	int32_t			int_part;
	int32_t			dec_part;

	BME280_calib_t	calib;
	BME280_data_t	data_struct;

	BME280_GetTRIM(&calib);
	BME280_SetMODE(0b11, 0b001, 0b001, 0b001);

	for (;;)
	{
		BME280_GetDATA(data);
		BME280_ConvertDATA(data, &calib, &data_struct);

		int_part = data_struct.temp / 100;
		dec_part = data_struct.temp % 100;
		snprintf(buf, sizeof(buf), "T:%ld.%ld\r\n", int_part, dec_part);
		xQueueSend(xQueueUart, buf, portMAX_DELAY);
		xQueueSend(xQueueOled, buf, portMAX_DELAY);

		int_part = (data_struct.pres / 256) /100;
		snprintf(buf, sizeof(buf), "P:%ld\r\n", int_part);
		xQueueSend(xQueueUart, buf, portMAX_DELAY);
		xQueueSend(xQueueOled, buf, portMAX_DELAY);

		int_part = data_struct.hum / 1000;
		dec_part = (data_struct.hum % 1000) / 10;
		snprintf(buf, sizeof(buf), "H:%ld.%ld\r\n", int_part, dec_part);
		xQueueSend(xQueueUart, buf, portMAX_DELAY);
		xQueueSend(xQueueOled, buf, portMAX_DELAY);

		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}
