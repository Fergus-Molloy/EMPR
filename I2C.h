#ifndef I2C_D
#define I2C_D
#define SERIAL_ADDR 59 //I2C address 59
#define SPACE 160
void setup_I2C(int func, int port, int pin0, int pin1);

int transmit(char data[], uint8_t addr, int size);

int size(char string[]);

#endif
