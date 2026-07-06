#include "ssd1306_task.h"

#include "ssd1306_task.h"

void SSD1306_Task()
{
	char buf[MSG_SIZE];

	ssd1306_Init();
	ssd1306_Fill(Black);
	ssd1306_UpdateScreen();

	char title[] = "- METEO STATION -";
	uint8_t x_title = (128 - (strlen(title) * 7)) / 2;

	for (;;)
	{
		ssd1306_SetCursor(x_title, 0);
		ssd1306_WriteString(title, Font_7x10, White);

		xQueueReceive(xQueueOled, buf, portMAX_DELAY);

		if (!strncmp(buf, "T", 1))
		{
			ssd1306_FillRectangle(0, 17, 63, 26, Black);
			ssd1306_SetCursor(0, 17);
			ssd1306_WriteString(buf, Font_7x10, White);
		}
		else if (!strncmp(buf, "P", 1))
		{
			ssd1306_FillRectangle(64, 17, 127, 26, Black);
			ssd1306_SetCursor(64, 17);
			ssd1306_WriteString(buf, Font_7x10, White);
		}
		else if (!strncmp(buf, "H", 1))
		{
			ssd1306_FillRectangle(0, 34, 61, 43, Black);
			ssd1306_SetCursor(0, 34);
			ssd1306_WriteString(buf, Font_7x10, White);
		}
		else if (!strncmp(buf, "L", 1))
		{
			ssd1306_FillRectangle(62, 34, 127, 43, Black);
			ssd1306_SetCursor(64, 34);
			ssd1306_WriteString(buf, Font_7x10, White);
		}

		ssd1306_UpdateScreen();
	}
}
