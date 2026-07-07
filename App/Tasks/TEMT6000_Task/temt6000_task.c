#include "temt6000_task.h"

void	TEMT6000_Task()
{
	char	buf[MSG_SIZE];

	vTaskDelay(pdMS_TO_TICKS(750));
	for (;;)
	{
		snprintf(buf, sizeof(buf), "L:%d\r\n", *get_DMA2_S0());
		xQueueSend(xQueueUart, buf, portMAX_DELAY);
		xQueueSend(xQueueOled, buf, portMAX_DELAY);

		TEMT6000_task_alive = 1;

		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}
