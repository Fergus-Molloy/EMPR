#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "lpc17xx_adc.h"
#include "lpc17xx_pinsel.h"
#include "I2C.h"
#include "serial.h"
#include "keypad.h"
#include "timer.h"
#include "ADC.h"


/*
int main(){
    serial_init();
    TIMER_EnableSysTick();
    setup_ADC(100E+3); // rate = 100kHz

    uint32_t adc_value;
    char buf[64];
    memset(buf, 0, 64);

    while(1){
        ADC_StartCmd(LPC_ADC,ADC_START_NOW);
        //Wait conversion complete
        while (!(ADC_ChannelGetStatus(LPC_ADC, ADC_CHANNEL, ADC_DATA_DONE)));
        adc_value = ADC_ChannelGetData(LPC_ADC, ADC_CHANNEL);

        if(adc_value || !adc_value){
            sprintf(buf, "Data: %d\n\r", adc_value);
            write_usb_serial_blocking(buf, 10);
        }
    }
    return 0;
}
*/
void setup_ADC(uint32_t rate){
    PINSEL_CFG_Type PinCfg;

    PinCfg.OpenDrain = 0;
    PinCfg.Pinmode = 0;
    PinCfg.Funcnum = 2;
    PinCfg.Pinnum = 24; // ADO 0
    PinCfg.Portnum = 0;
    PINSEL_ConfigPin(&PinCfg);

    ADC_Init(LPC_ADC, rate);
    ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL, ENABLE);
    ADC_StartCmd(LPC_ADC, ADC_START_NOW);
}
