#include <lpc21xx.h>
#include "setup.h"

volatile unsigned char rxflag;
unsigned char rxbyte,i=0,sw;
unsigned char buffer[33];

void UART0_ISR(void) __irq {
		rxbyte = UART0_Rx();
		if (rxbyte == '\r'){
			buffer[i]='\0';
			rxflag=1;	
			i=0; }
		else {
        buffer[i] = rxbyte;
        i++;
        if (i >= 32) {
            buffer[32] = '\0';
            rxflag = 1;
            i = 0;
        }
    }
    VICVectAddr = 0;
}

void EINT0_ISR(void) __irq {
		LCD_command(0x01);
    LCD_command(0x00);
    EXTINT = 0x01; 
    VICVectAddr = 0;
}

int main(){
		LCD_INIT();
		UART0_Init();
		UART0_ISR_Config();
		EINT_Init();
		while (1){
			if (rxflag==1){
				LCD_command(0x01);
				delay_ms(2);
				LCD_PRINTSTR(buffer);
				rxflag=0;
				LCD_command(0x80);
			} 
		}
	}

	void UART0_ISR_Config(void) {
    
    VICIntSelect = 0; 
    VICVectAddr0 = (unsigned long) UART0_ISR;
    VICVectCntl0 = (1 << 5) | 6; 
		U0IER = (1<<0);
    VICIntEnable = (1 << 6); 
    
}

void EINT_Init(void) { 
    PINSEL1 |= (1 << 0);
    
    VICIntSelect = 0; 
    VICVectAddr1 = (unsigned long) EINT0_ISR;
    VICVectCntl1 = (1 << 5) | 14; 
    VICIntEnable = (1 << 14); 
    
    EXTMODE = 0x03;  
    EXTPOLAR = 0x00;
}
