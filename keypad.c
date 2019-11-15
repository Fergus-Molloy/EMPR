#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "I2C.h"
#include "serial.h"
#include "keypad.h"
#include "timer.h"

char message[] = "i got here\n\r"; //12
//write_usb_serial_blocking(message, 12);
int main(){
  serial_init();
  setup_I2C(3,0,0,1);
  LCD_setup();
  LCD_clear();
  setup_keypad();
  TIMER_EnableSysTick();
  poll();
  return 0;
}


void setup_keypad(){
  char result;
  char yes[] = {0xff};
  result = transmit(yes, KEYPAD_ADDR, 2);
}

void poll(){
  char result[4];
  char cols[4] = {0x7F, 0xBF, 0xDF, 0xEF};
  char buf[64];
  char last[4];
  memset(buf,0,sizeof(buf));
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
          result = "A";
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
          result = "B";
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
          result = "C";
        break;
        default:
          result = 0;
      }
    break;
    case 0xE:
      switch (key) {
        case 0x7E:
          result = "*";
        break;
        case 0xBE:
          result = "0";
        break;
        case 0xDE:
          result = "#";
        break;
        case 0xEE:
          result = "D";
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
