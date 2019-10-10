#include "lpc17xx_gpio.h"
#include "LEDS.h"
#include "lpc17xx_systick.h"
//#include "serial/serial.h"

int main(void){
	setup()
	return 0;
}

void setup(){
	SYSTICK_InternalInit(100);
	SYSTICK_IntCmd(ENABLE);
	SYSTICK_Cmd(ENABLE);
}

void SetLED(uint32_t bitmap){
	GPIO_SetDir(1, bitmap, 1);
	GPIO_SetValue(1, bitmap);
}

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
