#include <lpc21xx.h>
#include "setup.h"

void UART0_Init(void) {
    PINSEL0 = 0x00000005;
    U0LCR = 0x83;
    U0DLL = 97;
    U0DLM = 0;
    U0LCR = 0x03;
}

unsigned char UART0_Rx(void) {
    while ((U0LSR & 0x01)==0); 
    return U0RBR;            
}
