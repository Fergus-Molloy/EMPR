#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "I2C.h"
#include "serial.h"
#include "keypad.h"
#include "timer.h"


/*
int main(){
    serial_init();
    setup_I2C(3,0,0,1);
    LCD_setup();
    LCD_clear();
    setup_keypad();
    TIMER_EnableSysTick();

    mini_project2();

    return 0;
}*/

void mini_project2(){
    stage_one();
    delay(1000);
    stage_two();
    delay(1000);
    LCD_clear();
    poll();
}


void setup_keypad(){
    char result;
    char buf[] = {0xff};
    result = transmit(buf, KEYPAD_ADDR, 2);
}

void poll(){
    char result[4];
    char cols[4] = {0x7F, 0xBF, 0xDF, 0xEF};
    char buf[64];
    char last[4];
    memset(buf,0,sizeof(buf));

    char addr_ln1 = LN1_BASE_ADDR;
    char addr_ln2 = LN2_BASE_ADDR;
    while(1) {
        int i;
        for(i=0; i<=4; i++){
            transmit(&cols[i], KEYPAD_ADDR, 1);
            recieve(KEYPAD_ADDR, &result[i]);
        }
        for (i=0; i<4; i++) {
            char *key = decode_keypad(result[i]);
            if(*key != 0 && *key!=last[i]){
                sprintf(buf, "%c\n\r", *key);
                write_usb_serial_blocking(buf, 3);
                if(key == "C"){
                    LCD_clear();
                    addr_ln1 = LN1_BASE_ADDR;
                    addr_ln2 = LN2_BASE_ADDR;
                }
                else{
                    if(addr_ln1 >= LN1_BASE_ADDR+16){
                        LCD_write(addr_ln2, *key);
                        addr_ln2++;
                    }
                    else{
                        LCD_write(addr_ln1, *key);
                        addr_ln1++;
                    }
                }
            }
            last[i] = *key;
        }
    }
}


char* decode_keypad(char key){
    char *result;
    switch (key & 0xF) {
        case 0x7:
        switch (key) {
            case 0x77:
                result = "1";
            break;
            case 0xB7:
                result = "2";
            break;
            case 0xD7:
                result = "3";
            break;
            case 0xE7:
                result = "F";
            break;
            default:
                result = 0;
        }
        break;
        case 0xB:
        switch (key) {
            case 0x7B:
                result = "4";
            break;
            case 0xBB:
                result = "5";
            break;
            case 0xDB:
                result = "6";
            break;
            case 0xEB:
                result = "E";
            break;
            default:
                result = 0;
        }
        break;
        case 0xD:
        switch (key) {
            case 0x7D:
                result = "7";
            break;
            case 0xBD:
                result = "8";
            break;
            case 0xDD:
                result = "9";
            break;
            case 0xED:
                result = "D";
            break;
            default:
                result = 0;
        }
        break;
        case 0xE:
        switch (key) {
            case 0x7E:
                result = "A";
            break;
            case 0xBE:
                result = "0";
            break;
            case 0xDE:
                result = "B";
            break;
            case 0xEE:
                result = "C";
            break;
            default:
                result = 0;
        }
        break;
        default:
            result = 0;
    }
    return result;
}
