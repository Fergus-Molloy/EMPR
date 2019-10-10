#include "lpc17xx_gpio.h"
#include "LEDS.h"
#include "lpc17xx_systick.h"
//#include "serial/serial.h"
int count=0;
int flag=0;

int main(void){
	GPIO_SetDir(1, ALLLEDS, 1);
	SYSTICK_InternalInit(100);
	SYSTICK_IntCmd(ENABLE);
	SYSTICK_Cmd(ENABLE);
	return 0;
}

void SysTick_Handler(){
	//write_usb_serial_blocking("called", 7);
	if(count==10){
		count = 0;
		if(flag){
			flag = 0;
			GPIO_SetValue(1, ALLLEDS);
		}
		else{
			flag = 1;
			GPIO_SetValue(1, 0);
		}
	}
}
