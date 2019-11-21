#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "lpc17xx_adc.h"
#include "I2C.h"
#include "serial.h"
#include "keypad.h"
#include "timer.h"
#include "ADC.h"



char message[] = "i got here\n\r"; //12
//write_usb_serial_blocking(message, 12);


int main(){
    serial_init();
    char buf[64];
    memset(buf, 0, 64);
    uint32_t rate = 100E+3;

    ADC_ChannelCmd(LPC_ADC, 0, ENABLE);
    ADC_Init(LPC_ADC, rate);
    ADC_StartCmd(LPC_ADC, ADC_START_NOW);

    uint32_t data = ADC_ChannelGetData(LPC_ADC, 0);
    sprintf(buf, "%f\n\r", data);
    write_usb_serial_blocking(buf, 16);

    return 0;
}
