#include "delay.h"

void delay_ms(uint32_t time){
	int i,j;
	for(i=0;i<time;i++){
		for(j=0;j<16000;j++){}
	}
}

void delay_us(uint32_t time){
	int i,j;
	for(i=0;i<time;i++){
		for(j=0;j<16;j++){}
	}
}
