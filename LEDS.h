#define LED0 1<<18
#define LED1 1<<20
#define LED2 1<<21
#define LED3 1<<23

const uint32_t ALLLEDS = LED0|LED1|LED2|LED3;

void setup();

void SetLEDS(uint32_t bitmap);

void LEDOff(uint32_t bitmask);

uint32_t GenerateBitMask(int num);
