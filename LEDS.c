#include <stdio.h>
#include <stdint.h>
#include "lpc17xx_gpio.h"
#include "LEDS.h"
#include "serial.h"
#include "timer.h"
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

/*
int main(void){
	setup();
	write_usb_serial_blocking("Starting count\n\r", 17);
	return 0;
}
*/
void setup_LEDS(){
	serial_init();
}

void SetLED(uint32_t bitmask){
	GPIO_SetDir(1, bitmask, 1);
	GPIO_SetValue(1, bitmask);
}

void LEDOff(uint32_t bitmask){
	GPIO_SetDir(1, bitmask, 1);
	GPIO_ClearValue(1, bitmask);
}

uint32_t GenerateBitMask(int num){
	/*exception here
	if(num<0 || num>15){
	}*/
	uint32_t bitmask = 0;
	if (num&0b1000){
		bitmask |= LED3;
	}
	if(num&0b100){
		bitmask |= LED2;
	}
	if(num&0b10){
		bitmask |= LED1;
	}
	if(num&0b1){
		bitmask |= LED0;
	}
	return bitmask;
}

void exception(int num){
	uint32_t bitmask = GenerateBitMask(num);
	LEDOff(LED0|LED1|LED2|LED3);
	SetLED(bitmask);
	while(1);
}

void finish(){
	write_usb_serial_blocking("Finished\n\r", 11);
	LEDOff(LED0|LED1|LED2|LED3);
	while(1);
}
