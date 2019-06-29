#ifndef __LCD_H__
#define __LCD_H__

#include "TM4C123.h"                    // Device header

void lcd_Init(void);
void lcd_Clr(void);
void lcd_Cmd(uint8_t cmd);
void lcd_Data(uint8_t data);
void lcd_setCursor(uint8_t a, uint8_t b);
void printc(char a);
void printf(char *s);

#endif 
