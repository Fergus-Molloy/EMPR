#include <stdio.h>
#include "lpc17xx_i2c.h"
#include "lpc17xx_pinsel.h"
#include "serial.h"
#include "I2C.h"

char message[] = "i got here\n\r";

int size(char string[]){
  return (int) (sizeof(string) / sizeof(char));
}

int main(void){
  serial_init();
  setup_I2C();
  int count = 0, i = 0, j = 0, result = 0;
  int addrs[5];
  for(i=0; i<=127; i++){
    result = transmit(1, i);
    if(result){
      count++;
      addrs[j] = i;
      j++;
    }
  }

  char string[34] = "0";
  sprintf(string, "%d devices connected to I2C bus\n\r", count);
  write_usb_serial_blocking(string, 34);
  for(i=0; i<5; i++){
    char string[12] = "0";
    sprintf(string, "Addr %d: %x\n\r", i, addrs[i]);
    write_usb_serial_blocking(string, 12);    

  }

  return 0;
}


void setup_I2C(){
  PINSEL_CFG_Type PinCfg;

  PinCfg.OpenDrain = 0;
  PinCfg.Pinmode = 0;
  PinCfg.Funcnum = 3;
  PinCfg.Pinnum = 0;
  PinCfg.Portnum = 0;
  PINSEL_ConfigPin(&PinCfg);
  PinCfg.Pinnum = 1;
  PINSEL_ConfigPin(&PinCfg);

  I2C_Init(LPC_I2C1, 100000);
  I2C_Cmd(LPC_I2C1, ENABLE);
}

int transmit(int data, uint8_t addr){
  I2C_M_SETUP_Type transferMCfg;
  transferMCfg.sl_addr7bit = addr;
  transferMCfg.tx_data = data;
  transferMCfg.tx_length = sizeof(data);
  transferMCfg.rx_data = NULL;
  transferMCfg.rx_length = 0;
  transferMCfg.retransmissions_max = 3;
  return I2C_MasterTransferData(LPC_I2C1, &transferMCfg, I2C_TRANSFER_POLLING);
}
