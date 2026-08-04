#ifndef GLOBALS_H
#define GLOBALS_H

/**
 * @file    globals.h
 * @brief   Shared queue handles and inter-task status flags.
 */

# include "rcc.h"
# include "gpio.h"
# include "usart.h"
# include "spi.h"
# include "i2c.h"
# include "adc.h"
# include "dma.h"
# include "iwdg.h"
# include "bme280.h"
# include "ssd1306.h"
# include <string.h>
# include <stdio.h>
# include "FreeRTOS.h"
# include "queue.h"
# include "bme280_task.h"
# include "temt6000_task.h"
# include "ssd1306_task.h"
# include "uart_task.h"
# include "iwdg_task.h"

/** @brief Size, in bytes, of a message exchanged through the FreeRTOS queues below. */
#define	MSG_SIZE	64

extern QueueHandle_t	xQueueUart;	/**< Sensor messages routed to UART_Task. */
extern QueueHandle_t	xQueueOled;	/**< Sensor messages routed to SSD1306_Task. */

/**
 * @brief Per-task heartbeat flags, set by each task and polled by IWDG_Task
 *        before the hardware watchdog is kicked.
 */
extern volatile uint8_t	BME280_task_alive;
extern volatile uint8_t	TEMT6000_task_alive;
extern volatile uint8_t	SSD1306_task_alive;
extern volatile uint8_t	UART_task_alive;

#endif
