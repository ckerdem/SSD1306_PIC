/* 
 * File:   oled.h
 * Author: Celal
 *
 * Created on August 7, 2026, 3:17 PM
 */

#ifndef OLED_H
#define	OLED_H



void SSD1306_Command(uint8_t cmd);
void SSD1306_Data(uint8_t data);
void SSD1306_DataBuffer(uint8_t *buffer, uint16_t length);
void SSD1306_SetCursor(uint8_t page,uint8_t column);
void SSD1306_Clear(void);
void SSD1306_DisplayOn(void);
void SSD1306_DisplayOff(void);
void SSD1306_AllPixelsOn(void);
void SSD1306_NormalDisplay(void);
void SSD1306_InvertOn(void);
void SSD1306_InvertOff(void);
void SSD1306_Init(void);
void SSD1306_WriteString(const char* str, uint8_t page, uint8_t column, uint8_t size);

#endif	/* OLED_H */

