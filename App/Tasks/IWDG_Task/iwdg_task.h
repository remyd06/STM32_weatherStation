#ifndef IWDG_TASK_H
#define IWDG_TASK_H

/**
 * @file    iwdg_task.h
 * @brief   Software watchdog layer: monitors the other FreeRTOS tasks'
 *          liveness flags and only kicks the hardware IWDG when all of
 *          them have reported alive within TASK_TIMEOUT_MS.
 */

# include "globals.h"
# include "iwdg.h"

/** @brief Maximum silence, in ms, tolerated from a task before it is logged as timed out. */
# define TASK_TIMEOUT_MS 2000

void	IWDG_Task();

#endif
