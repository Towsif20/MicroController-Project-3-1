/*
 * PIR.c
 *
 * Created: 8/24/2019 9:54:43 PM
 * Author : Towsif
 */ 

#define F_CPU 1000000UL

#define D4 eS_PORTC4
#define D5 eS_PORTC5
#define D6 eS_PORTC6
#define D7 eS_PORTC7
#define RS eS_PORTC0
#define EN eS_PORTC2

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "lcd.h"

volatile uint32_t n;

ISR(TIMER1_OVF_vect)
{
	n++;
}

    int main()
    {
		MCUCSR = (1<<JTD);
		MCUCSR = (1<<JTD);
		DDRC = 0xFF;
		
		uint32_t elapsedTime;
		
		TCCR1A = 0b00000000;
		TCCR1B = 0b00000001;
		TIMSK = 0b00000100;
		
		n = 0;
		
		TCNT1 = 0;
		
		sei();
    
	 //configuring PortC pin 0 as input
    //PORTC=0b11000000; 
	DDRA=0x00;
    DDRB=0xFF; // configuring PortB as output
	DDRD = 0xFF;
    PORTB=0x00; // buzzer/LED off
	
	
	int pir1 = 0;
	int pir2 = 0;
	int authorised = 0;
	int count = 14;
	Lcd4_Init();
	int maxCount = 15;
	
	Lcd4_Clear();
	
	Lcd4_Set_Cursor(1,1);
	Lcd4_Write_String("14");
	
    while(1)
    {
		elapsedTime = (n*65536 + (uint32_t) TCNT1) / 1000000;
		
		if(elapsedTime >= 15 && !((pir1 == 0) && (pir2 == 0)) )
		{
			PORTB = PORTB = 0b00001000;
			pir1 = pir2 = authorised = 0;
			Lcd4_Set_Cursor(2,1);
			Lcd4_Write_String("time is ");
			
			_delay_ms(1000);
			Lcd4_Set_Cursor(2,1);
			Lcd4_Write_String("  radioactive   ");
			_delay_ms(1000);
			Lcd4_Set_Cursor(2,1);
			Lcd4_Write_String("              ");
			n = 0;
			TCNT1 = 0;
			
		}
		
		if (count < maxCount)
		{
			if(PINA & (1<<3))
			{
				
				pir1 = pir2 = 0;
				authorised = 0;
				PORTB = 0b00001000;
				Lcd4_Set_Cursor(2, 1);
				Lcd4_Write_String("Ratuler gari :)        ");
				_delay_ms(1000);
				Lcd4_Set_Cursor(2, 1);
				Lcd4_Write_String("                ");
				n = 0;
				
				TCNT1 = 0;
				
			}
			
			if(PINA & (1<<2))
			{
				
				authorised = 1;
				Lcd4_Set_Cursor(2, 1);
				Lcd4_Write_String("aho vatija aho  ");
				
				n = 0;
				
				TCNT1 = 0;
				
				
			}
		}
		
		else
		{
			Lcd4_Set_Cursor(2, 1);
			Lcd4_Write_String("aar dhukbe na       ");
		}
		
     if((PINA&(1<<1)))            // check for sensor pin PC.0 using bit
      {
		  //pir1 = 1;
		  
		  //_delay_ms(1000);
		  if(pir2 == 1)
		  {
			  pir1 = pir2 = 0;
			  if(count > 0)
			  {
				  count--;
				  //PORTB = 0b00000110;
				  char str[3];
				  
				  str[2] = '\0';
				  
				  str[1] = (char) (count % 10 + 48);
				  
				  str[0] = (char) ((count%100)/10 + 48);
				  
				  //str[4] = '\0';
				  Lcd4_Clear();
				  Lcd4_Set_Cursor(1,1);
				  Lcd4_Write_String(str);
				  Lcd4_Set_Cursor(2, 1);
				  Lcd4_Write_String("");
				  PORTB = 0b00001010;
				  n = 0;
				  
				  TCNT1 = 0;
				  _delay_ms(3000);
				//  Lcd4_Clear();
				  //_delay_ms(500);
				   //PORTB=0x00; 
			  }
			 
		  }
		  
		  else
		  {
			  if (authorised)
			  {
				  n = 0;
				  TCNT1 = 0;
				  PORTB=0b00000100;
				  pir1 = 1;
			  }
		  }
       //PORTB=0x01;           // buzzer /LED on
	   //PORTB = 0b00000010;
       
       //PORTB=0x00;
	   
	   
      }
	 
	 if(PINA&(1<<0))
	{
		n = 0;
		TCNT1 = 0;
		
		pir2 = 1;
		if(count > 0)	PORTB = 0b00000100;
		//_delay_ms(1000);
		if(pir1 == 1)
			{
				count++;
				pir1 = pir2 = 0;
				authorised = 0;
				
				char str[3];
				
				str[2] = '\0';
				
				str[1] = (char) (count % 10 + 48);
				
				str[0] = (char) ((count%100)/10 + 48);
				
				//str[4] = '\0';
				Lcd4_Clear();
				Lcd4_Set_Cursor(1,1);
				Lcd4_Write_String(str);
				Lcd4_Set_Cursor(2, 1);
				Lcd4_Write_String("");
				PORTB = 0b00001001;
				n = 0;
				
				TCNT1 = 0;
				_delay_ms(3000);
				Lcd4_Set_Cursor(2,1);
				Lcd4_Write_String("        ");
				//Lcd4_Clear();
				//_delay_ms(500);
				// PORTB=0x00; 
			}
		
		//_delay_ms(1000);
	}
      //else
      //{
		 PORTB=0x00;  // buzzer/LED off
		  //_delay_ms(500);
	  //}
	  
	  
	  
    }           
    return 0;
    }

