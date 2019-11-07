#include <stdio.h>
#include "lpc17xx_i2c.h"
#include "lpc17xx_pinsel.h"
#include "serial.h"
#include "I2C.h"
#include "Convert.h"

int main(void){
  serial_init();
  setup_I2C(3,0,0,1);
  LCD_setup();
  LCD_clear();

  //stage_one();
  //wait();
  //stage_two();
  stage_three();
  write_usb_serial_blocking("Success\n\r", 9);

  return 0;
}

void stage_one(){
  int count=0;
  char addr[9]={0};
  char letter[1] = {1};
  int x;
  for(x=0; x<256; x++){
    int result = transmit(letter, x, 1);
    if(result)
    {
      addr[count]=x;
      count++;
    }
  }
  char text[33] = {0};
  sprintf(text, "%d deviced connected to i2c bus\n\r", count);
  write_usb_serial_blocking(text, 33);
  for(x=0; x<10; x++){
    char text[11]={0};
    sprintf(text, "addr: %d\n\r", addr[x]);
    write_usb_serial_blocking(text, 11);
  }
}

void stage_two(){
  char buf[16] = "Hello World";

  char addr = BASE_ADDR;
  int x;
  for(x=0; x<11; x++){
    LCD_write(addr, buf[x]);
    addr++;
  }
}

void LCD_setup(){
  char buf[11] = {0x00,0x34,0x0c,0x06,0x35,0x04,0x10,0x42,0x9f,0x34,0x02};
  transmit(buf, SERIAL_ADDR, 11);
}

void LCD_write(char address, char letter){
  char addr[2] = {0x00, address};
  char buf[2] = {0x40, convert_char(letter)};
  transmit(addr, SERIAL_ADDR, 2);
  transmit(buf, SERIAL_ADDR, 2);
}

void LCD_clear(){
  char x;
  for(x=0x80; x<0xB8; x++){ //B8 is the last address we can see
    LCD_write(x, SPACE);
  }
}

void setup_I2C(int func, int port, int pin0, int pin1){
  PINSEL_CFG_Type PinCfg;

  PinCfg.OpenDrain = 0;
  PinCfg.Pinmode = 0;
  PinCfg.Funcnum = func;
  PinCfg.Pinnum = pin0;
  PinCfg.Portnum = port;
  PINSEL_ConfigPin(&PinCfg);
  PinCfg.Pinnum = pin1;
  PINSEL_ConfigPin(&PinCfg);

  I2C_Init(LPC_I2C1, 100000);
  I2C_Cmd(LPC_I2C1, ENABLE);
}

int transmit(char data[], uint8_t addr, int size){
  I2C_M_SETUP_Type transferMCfg;
  transferMCfg.sl_addr7bit = addr;
  transferMCfg.tx_data = data;
  transferMCfg.tx_length = size;
  transferMCfg.rx_data = NULL;
  transferMCfg.rx_length = 0;
  transferMCfg.retransmissions_max = 3;
  return I2C_MasterTransferData(LPC_I2C1, &transferMCfg, I2C_TRANSFER_POLLING);
}
