#ifndef I2C_D
#define I2C_D
#define LCD_ADDR 59 //I2C address 59
#define LN1_BASE_ADDR 0x80
#define LN2_BASE_ADDR (LN1_BASE_ADDR+40)

void setup_I2C(int func, int port, int pin0, int pin1);

void LCD_setup();

void LCD_write(char addr, char letter);

void LCD_clear();

void stage_one();

void stage_two();

void stage_three();

int transmit(char data[], uint8_t addr, int size);

int receive(uint8_t addr, char *rx_data);

#endif
