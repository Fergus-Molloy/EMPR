#include "lpc17xx_systick.h"
#include "timer.h"
#include "serial.h"

static int time=0;

void TIMER_EnableSysTick(){
    SYSTICK_IntCmd(ENABLE);
    SYSTICK_InternalInit(10);
    SYSTICK_Cmd(ENABLE);
}

void delay(int time_ms){
    static int now;
    now = time;
    while((time-now)<=time_ms);
}

//Interrupts--------------------
void SysTick_Handler(){
    time+=10;
}
