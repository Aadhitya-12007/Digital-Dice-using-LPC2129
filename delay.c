#include <lpc21xx.h>
#include "setup.h"

void delay_ms(unsigned int i){
	T0PR=15000-1;	
	T0TCR=0x01;
	while (T0TC < i);
	T0TCR=0X03;
	T0TCR=0X00;
}
