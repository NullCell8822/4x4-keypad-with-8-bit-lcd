#include "TM4C123.h"                    // Device header

#include "delay.h"
#include "lcd.h"
#include "keypad.h"

int main(){
	char key,key1;
	uint8_t count=1;
	
	lcd_Init();
	keypad_init();
	
	while(1){		
		key = get_keypad();
		delay_ms(1);
		key1 = get_keypad();
		
		if((key==key1)&&(key!=0)&&(key!='*')){
			if(count>=17){
				lcd_setCursor(2,1);
				count=1;
			}
			printc(key);
			count++;
		}
		
		if(key=='*'){
			lcd_Clr();
			count=1;
		}
		
		delay_ms(150);
	}
	
}
