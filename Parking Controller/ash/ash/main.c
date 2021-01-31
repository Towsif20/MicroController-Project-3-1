/*
 * GccApplication9.c
 *
 * Created: 7/29/2019 6:59:06 PM
 * Author : md ashraful islam
 */ 
#define F_CPU 1000000UL

#define D4 eS_PORTA4
#define D5 eS_PORTA5
#define D6 eS_PORTA6
#define D7 eS_PORTA7
#define RS eS_PORTA0
#define EN eS_PORTA2

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcd.h" 
#include "UART.h"



int main(void)
{
	DDRA = 0xFF;
	DDRB = 1;
	DDRC = 0xFF;
	
	PORTB=0;
	
	UART_init(9600);
	
	Lcd4_Init();
	Lcd4_Clear();
	
	stdout = fdevopen(UART_send, NULL);
	stdin = fdevopen(NULL, UART_receive);
	
	Lcd4_Set_Cursor(1,0);
	Lcd4_Write_String("  Punch a Card");
	
	char ch;
	char arr[5];
	
	int data[3];
	
	while(1)
	{
		
		//Lcd4_Write_String("While");
		scanf("%c",&ch);
		if((int) ch==2){
			Lcd4_Clear();
			int i = 0;
			Lcd4_Set_Cursor(1,0);
			PORTB=1;
			while(1){
				scanf("%c",&ch);
				if((int)ch==3)
					break;
				data[i] = (int) ch;
				i++;	
				
			}
		
		}
		
		itoa((int)data[2],arr,10);
		Lcd4_Write_String(arr);
		Lcd4_Write_Char(' ');
		
		if(data[2] == 57 || data[2] == 70)
		{
			PORTC = 0b00000001;
			_delay_ms(1000);
		}
		else
		{
			PORTC = 0b00000010;
			_delay_ms(1000);
		}
		PORTB=0;
		//_delay_ms(2000);
		Lcd4_Clear();
		PORTC=0;
		//_delay_ms(5000);
	}
}
