#ifndef SSD1306_H
#define SSD1306_H

/**
 * @file    ssd1306_task.h
 * @brief   FreeRTOS task rendering sensor readings on the SSD1306 OLED.
 */

# include "globals.h"
# include "ssd1306.h"
# include "iwdg_task.h"

void	SSD1306_Task();

#endif
