#define LED0 0x00040000
#define LED1 0x00100000
#define LED2 0x00200000
#define LED3 0x00800000

const uint32_t ALLLEDS = LED0|LED1|LED2|LED3;

void setup();

void SetLEDS(uint32_t bitmap);

uint32_t GenerateBitMask(int num);
