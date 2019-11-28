#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "lpc17xx_dac.h"
#include "lpc17xx_pinsel.h"
#include "I2C.h"
#include "serial.h"
#include "keypad.h"
#include "timer.h"
#include "ADC.h"
#include "DAC.h"

#define PI 3.14159265

char message[] = "i got here\n\r"; //12
char none[] = "\r\r\r\r\r\r\r\r\r\r\r\r"; //12
//write_usb_serial_blocking(message, 12);

int test;
int main(){
    serial_init();
    TIMER_EnableSysTick();
    DAC_Setup();
    char buf[64];
    memset(buf,0,64);

    generate_sin_wave(40, 3);
    return 0;
}

void generate_sin_wave(int freq, double amplitude){
    if(amplitude>3){
        char buf[] = "Amplitude cannot be greater than 3V\n\r";
        write_usb_serial_blocking(buf, sizeof(buf)/sizeof(buf[0]));
        return;
    }

    amplitude = (amplitude/3)*512;
    double value;
    double conv = PI/180;
    float x=0.0;
    double max=0;
    uint32_t output;
    char buf[64];
    memset(buf, 0 , 64);

    while(1){
        value = sin(x*conv);

        if(value>max)
            max=value;

        output = (uint32_t) ((value*amplitude) + (amplitude-1));
        //sprintf(buf, "output: %f\n\r", value);
        //write_usb_serial_blocking(buf, 14);
        DAC_UpdateValue(LPC_DAC, output);

        x+=freq/80.0;
        if(x>=360)
            x=0;
        }
}

void DAC_Setup(){
    PINSEL_CFG_Type PinCfg;
     PinCfg.Funcnum = 2;
     PinCfg.OpenDrain = 0;
     PinCfg.Pinmode = 0;
     PinCfg.Pinnum = 26;
     PinCfg.Portnum = 0;
     PINSEL_ConfigPin(&PinCfg);

     DAC_Init(LPC_DAC);
}
