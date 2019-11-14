#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "I2C.h"
#include "serial.h"
#include "keypad.h"

char message[] = "i got here\n\r"; //12

int main(){
  serial_init();
  setup_I2C(3,0,0,1);
  LCD_setup();
  LCD_clear();
  setup_keypad();
  poll();
  return 0;
}


void setup_keypad(){
  char result;
  char yes[] = {0xff};
  result = transmit(yes, KEYPAD_ADDR, 2);
}

void poll(){
  uint8_t result[4]={0};
  while(1) {
    char cols[4] = {0x7F, 0xBF, 0xDF, 0xEF};
    char buf[64];
    memset(buf,0,sizeof(buf));
    int i;
    for(i=0; i<=4; i++){
      transmit(&cols[i], KEYPAD_ADDR, 1);
      recieve(KEYPAD_ADDR, &result[i]);
    }

    for (i =0; i<4; i++) {
      switch (result[i] & 0xf) {
        case 0x7:
        sprintf(buf, "row1: %x\n\r", result[i]);
        write_usb_serial_blocking(buf, sizeof(buf));
        break;
        case 0xb:
        sprintf(buf, "row2: %x\n\r", result[i]);
        write_usb_serial_blocking(buf, sizeof(buf));
        break;
        case 0xd:
        sprintf(buf, "row3: %x\n\r", result[i]);
        write_usb_serial_blocking(buf, sizeof(buf));
        break;
        case 0xe:
        sprintf(buf, "row4: %x\n\r", result[i]);
        write_usb_serial_blocking(buf, sizeof(buf));
        break;
      }
    }
  }
}
