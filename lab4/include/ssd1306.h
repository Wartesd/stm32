#ifndef SSD1306_H
#define SSD1306_H

#include <stdint.h>

void SSD1306_Init(void);
void SSD1306_SendCommand(uint8_t cmd);
void SSD1306_SendData(uint8_t data);
void SSD1306_DrawBuffer(uint8_t *buf);
void SSD1306_DrawChessboard(void);

#endif
