#include "temt6000_task.h"

void	TEMT6000_Task()
{
	char		buf[MSG_SIZE];

//	if (get_DMA2_S0() > 0)
//	{
//		snprintf(buf, sizeof(buf), "!LOGS!TEMT6000 detected.\r\n");
//		xQueueSend(xQueueUart, buf, portMAX_DELAY);
//	}
//	else
//	{
//		snprintf(buf, sizeof(buf), "!LOGS!TEMT6000 not detected.\r\n");
//		xQueueSend(xQueueUart, buf, portMAX_DELAY);
//	}

	vTaskDelay(pdMS_TO_TICKS(750));
	for (;;)
	{
		snprintf(buf, sizeof(buf), "L:%d\r\n", *get_DMA2_S0());
		xQueueSend(xQueueOled, buf, portMAX_DELAY);

		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}
