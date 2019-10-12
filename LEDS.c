#include <stdio.h>
#include <stdint.h>
//#include "lpc17xx_gpio.h"
#include "LEDS.h"
//#include "lpc17xx_systick.h"
//#include "/serial/serial.h"

int main(void){
	//setup()
	for(int x=0; x<16; x++){
		uint32_t bitmask = GenerateBitMask(x);
		printf("bitmask: %x\n", bitmask);
	}
	return 0;
}
/*
void setup(){
	SYSTICK_InternalInit(100);
	SYSTICK_IntCmd(ENABLE);
	SYSTICK_Cmd(ENABLE);
}

void SetLED(uint32_t bitmap){
	GPIO_SetDir(1, bitmap, 1);
	GPIO_SetValue(1, bitmap);
}
*/
uint32_t GenerateBitMask(int num){
	/*exception here
	if(num<0 || num>15){
	}*/
	uint32_t bitmask = 0;
	if((num-8)>=0){
		bitmask |= LED3;
		num -= 8;
	}
	if((num-4)>=0){
		bitmask |= LED2;
		num -=4;
	}
	if((num-2)>=0){
		bitmask |= LED1;
		num -= 2;
	}
	if((num-1)>=0){
		bitmask |= LED0;
		num -= 1;
	}
	return bitmask;
}
/*
//Interrupts--------------------
void SysTick_Handler(){
	static int count=0;
	static int flag=0;
	if(count==10){
		count = 0;
		if(flag){
			flag = 0;
			SetLED(ALLLEDS);
		}
		else{
			flag = 1;
			SetLED(0); // 0 turns all outputs off
		}
	}
}
*/