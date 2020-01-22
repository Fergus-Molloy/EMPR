# EMPR
---

## Chip Details

- Chip: LPC176X

### Specification
- ARM Cortex-M3 core
- Harvard architecture
- 100MHz clock speed
- 64KB RAM
- 512KB flash memory
- Nested interrupt controller

### IO
- Ethernet with DMA
- 2xCAN bus controllers
- 3xI2C controllers
- SPI controller
- USB
- 4xUART (serial controllers)
- Digital IO (GPIO)
- Analogue IO (DAC and ADC)
- PWM signal generator
- Timers, real-time clock, wake-up interrupt controller
- Low power modes, brown out detector
---
## mBed Board
- To print via USB using serial protocol use UART0
  
### Useful Diagrams
- mBed pin mappings
![mBed pin mappings](https://i.imgur.com/uz1Z0J4.png)
- Chip pin mappings

![Chip pin mappings](https://i.imgur.com/gdGrJn7.png)

### LED Mappings
|LED|Chip pin|Port|mBedPin|Pin notation|Hex Value|
|:---:|:---:|:---:|:---:|:---:|:---:|
|0|32|1|18|P1.18|0x0004 0000|
|1|34|1|20|P1.20|0x0010 0000|
|2|35|1|21|P1.21|0x0020 0000|
|3|37|1|23|P1.23|0x0080 0000|

---
## Systick Timer
- Ticks every 10ms
- dedicated exception generator, with interrupts handled by `void Systick_Handler()`
- can be ticked internally or by an external clock (internal is most simple)
