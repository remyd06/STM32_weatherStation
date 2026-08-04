#ifndef BME280_TASK_H
#define BME280_TASK_H

/**
 * @file    bme280_task.h
 * @brief   FreeRTOS task periodically reading the BME280 and publishing
 *          formatted T/P/H strings to the UART and OLED queues.
 */

# include "globals.h"
# include "bme280.h"
# include "iwdg_task.h"

void	BME280_Task();

#endif
