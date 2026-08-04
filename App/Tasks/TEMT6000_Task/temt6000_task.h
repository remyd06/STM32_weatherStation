#ifndef TEMT6000_H
#define TEMT6000_h

/**
 * @file    temt6000_task.h
 * @brief   FreeRTOS task publishing the TEMT6000 ambient light reading.
 */

# include "globals.h"
# include "dma.h"
# include "iwdg_task.h"

void	TEMT6000_Task();

#endif
