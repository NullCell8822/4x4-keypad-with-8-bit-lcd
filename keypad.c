#include "keypad.h"
#include "delay.h"

#define K_ROW GPIOE
#define K_COL GPIOC

void keypad_init(void){
	//initialize ports
	SYSCTL->RCGCGPIO |= (1U<<2)|(1U<<4);
	
	//row initialization
	K_ROW->DIR |= 0x0F;
	K_ROW->DEN |= 0x0F;
	K_ROW->ODR |= 0x0F;
	K_ROW->PUR |= 0x0F;
	
	//column initialization
	K_COL->DIR &= ~0xF0;
	K_COL->DEN = 0xF0;
	K_COL->PUR = 0xF0;
	
}
char get_keypad(void){
	const char k_map[4][4]={
		{'1','2','3','A'},
		{'4','5','6','B'},
		{'7','8','9','C'},
		{'*','0','#','D'}
	};
	
	int row,col;
	
	for(;;){	
		row =0;
		K_ROW->DATA = 0x0E;
		delay_us(10);
		col = K_COL->DATA&0xF0;
		if(col!=0xF0)break;
		
		row =1;
		K_ROW->DATA = 0x0D;
		delay_us(10);
		col = K_COL->DATA&0xF0;
		if(col!=0xF0)break;
		
		row =2;
		K_ROW->DATA = 0x0B;
		delay_us(10);
		col = K_COL->DATA&0xF0;
		if(col!=0xF0)break;
		
		row =3;
		K_ROW->DATA = 0x07;
		delay_us(10);
		col = K_COL->DATA&0xF0;
		if(col!=0xF0)break;				
		
		if((K_COL->DATA&0xF0)==0xF0)return 0;
		
		return 0;
	}
	
	if(col==0xE0)return k_map[row][0];
	if(col==0xD0)return k_map[row][1];
	if(col==0xB0)return k_map[row][2];
	if(col==0x70)return k_map[row][3];
	
	return 0;
}
