#include "lcd.h"
#include "delay.h"


void lcd_Init(void){
	//initialize ports
	//enable clock of ports B and D
	SYSCTL->RCGCGPIO |= (1U<<1)|(1U<<0); //0b 0000 1010
	
	//set port B and D as output
	GPIOB->DIR |= 0xFF;
	GPIOA->DIR |= 0xE0;
	
	//set as digital pin
	GPIOB->DEN |= 0xFF;
	GPIOA->DEN |= 0xE0;
	
	//initialize lcd 
	lcd_Cmd(0x38);
	lcd_Cmd(0x0E);
	lcd_Cmd(0x06);
	
	//clear screen lcd_Clr()
	lcd_Clr();
}

void lcd_Clr(){
	//send command to clear screen
	lcd_Cmd(0x01);
}

void lcd_Cmd(uint8_t cmd){
	//set enable pin to 0, r/w to 0 and rs to 0
	GPIOA->DATA = 0; 
	
	//send command 
	GPIOB->DATA = cmd;
	
	//set enable bit to 1
	GPIOA->DATA |= 0x20;
	
	//delay
	delay_ms(1);
	
	//set enable bit to 0
	GPIOA->DATA = 0;
}

void lcd_Data(uint8_t data){
	//set enable pin to 0, r/w to 0 and rs to 1
	GPIOA->DATA = 0x40;
	
	//send command 
	GPIOB->DATA = data;
	
	//set enable bit to 1
	GPIOA->DATA = 0x60;
	
	//delay
	delay_ms(1);
	
	//set enable bit to 0
	GPIOA->DATA = 0x40;
}

void lcd_setCursor(uint8_t a, uint8_t b){
	uint8_t addr;
	switch(a){
		case 1:
			addr = 0x80 + (b-1);
		  lcd_Cmd(addr);
			break;
		
		case 2:
			addr = 0xC0 + (b-1);
		  lcd_Cmd(addr);
			break;
		default:
			lcd_Cmd(0x80);
	}
}

void printc(char a){
	//send data to the lcd using lcd_data()
	lcd_Data(a);
}

void printf(char *s){
	while(*s){
	printc(*s);
	s++;
	}
}
