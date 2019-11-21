#include "Convert.h"
#include "serial.h"
#include <stdio.h>

char convert_char(char c){
    /*
    Converts individual characters to correct LCD value
    */
    if(c==32||c==160){
        return SPACE;
    }
    else if(c>=48 && c<48+10){
        return c+OFFSET;
    }
    else if(c>=65 && c<65+26){
        return c+OFFSET;
    }
    else if(c>=97 && c<97+26){
        return c;
    }
    else{
        char text[43]={0};
        sprintf(text, "ValueError: character %c not in alphabet\n\r", c);
        write_usb_serial_blocking(text, 43);
        return -1;
    }
}

char* convert_str(char string[]){
    /*
    function that converts string into the values needed
    to write them to the LCD. Since arrays are always passed
    by reference output is stored in original array
    */
    int x;
    //char buff[16] = {0};
    for(x=0; x<17; x++){
        if(string[x]==0)
        break;
        string[x] = convert_char(string[x]);
    }
    return string;
}
