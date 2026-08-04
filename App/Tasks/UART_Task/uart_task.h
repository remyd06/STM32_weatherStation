#ifndef UART_TASK_H
#define UART_TASK_H

/**
 * @file    uart_task.h
 * @brief   FreeRTOS task forwarding queued sensor strings to USART2.
 */

# include "globals.h"
# include "usart.h"
# include "iwdg_task.h"

void	UART_Task();

#endif
