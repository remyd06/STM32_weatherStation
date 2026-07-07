#ifndef GLOBALS_H
#define GLOBALS_H

# include <string.h>
# include <stdio.h>
# include "FreeRTOS.h"
# include "queue.h"
# include "iwdg_task.h"

#define	MSG_SIZE	64

extern QueueHandle_t	xQueueUart;
extern QueueHandle_t	xQueueOled;

extern volatile uint8_t	BME280_task_alive;
extern volatile uint8_t	TEMT6000_task_alive;
extern volatile uint8_t	SSD1306_task_alive;
extern volatile uint8_t	UART_task_alive;

#endif
