#include "uart_task.h"

void	UART_Task()
{
	char	buf[MSG_SIZE];

	for (;;)
	{
		xQueueReceive(xQueueUart, buf, portMAX_DELAY);

		USART_Transmit(USART2, (uint8_t *)buf, strlen(buf));
	}
}
