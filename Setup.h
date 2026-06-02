#ifndef setup
#define setup

void delay_ms(unsigned int);
void LCD_INIT(void);
void LCD_command(unsigned char);
void LCD_data(unsigned char);
void LCD_PRINTSTR(unsigned char*);
void Timer_Random(void);
void EINT_Init(void);
void UART0_Init(void);
unsigned char UART0_Rx(void);
void UART0_ISR_Config(void);

#endif
