#ifndef KEYPAD_D
#define KEYPAD_D
#define KEYPAD_ADDR 33
#define col0 0x7f
#define col1 0x2f
#define col2 0x4f
#define col3 0x8f

void setup_keypad();

void poll();

char* decode_keypad(char key);

/*
bf
df
ef
bf

*/

#endif
