#include "globals.h"
#include "main.h"

QueueHandle_t	xQueueUart;
QueueHandle_t	xQueueOled;

volatile uint8_t BME280_task_alive = 0;
volatile uint8_t TEMT6000_task_alive = 0;
volatile uint8_t SSD1306_task_alive = 0;
volatile uint8_t UART_task_alive = 0;
