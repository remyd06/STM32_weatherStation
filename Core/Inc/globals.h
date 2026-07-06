#ifndef GLOBALS_H
#define GLOBALS_H

# include <string.h>
# include <stdio.h>
# include "FreeRTOS.h"
# include "queue.h"

#define	MSG_SIZE	64

extern QueueHandle_t	xQueueUart;
extern QueueHandle_t	xQueueOled;

#endif
