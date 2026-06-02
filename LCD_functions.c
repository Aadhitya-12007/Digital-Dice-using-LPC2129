//Code by Aadhitya G
//Contains the 16x2 Alphanumeric LCD configuration and display functions

#include <lpc21xx.h>
#include "setup.h"

#define LCDD 0xff << 2
#define RS 1<<10
#define E 1<<11

void LCD_INIT(void){
		IODIR0 = LCDD | RS | E;
    delay_ms(20);
    LCD_command(0x38);
    LCD_command(0x0E);
    LCD_command(0x01);
    delay_ms(2);
    LCD_command(0x80);
}

void LCD_command(unsigned char cmd){
	IOCLR0 = LCDD;
	IOSET0 = cmd << 2;
	IOCLR0 = RS;
	IOSET0 = E;
	delay_ms(2);
	IOCLR0=E;
	delay_ms(2);}

	void LCD_data(unsigned char d){
	IOCLR0 = LCDD;
	IOSET0 = d << 2;
	IOSET0 = RS;
	IOSET0 = E;
	delay_ms(2);
	IOCLR0=E;
	delay_ms(2);	}
	
void LCD_PRINTSTR(unsigned char* s){
	unsigned char count = 0;
    while(*s){
        if (count == 16) {
            LCD_command(0xC0);
        }
        LCD_data(*s++);
        count++;
        if (count >= 32) {
            break; 
        }
    }
}
