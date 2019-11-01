#include <stdio.h>
#include <stdint.h>
#include "yes.h"

uint32_t GenerateBitMask(int num){
	/*exception here
	if(num<0 || num>15){
	}*/
	uint32_t bitmask = 0;
	if((num-8)>=0){
		bitmask |= LED3;
		num -= 8;
	}
	if((num-4)>=0){
		bitmask |= LED2;
		num -=4;
	}
	if((num-2)>=0){
		bitmask |= LED1;
		num -= 2;
	}
	if((num-1)>=0){
		bitmask |= LED0;
		num -= 1;
	}
	return bitmask;
}

int main(){
    for(int x =0; x<16;x++){
        printf("Bitmask: %x\n", GenerateBitMask(x));
    }
}