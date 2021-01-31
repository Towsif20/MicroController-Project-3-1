#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
int main(void)
{
	DDRD |= 0xFF;
	DDRA=0x00;
	PINA=0x00;
	TCCR1A |= 1<<WGM11 | 1<<COM1A1 | 1<<COM1A0;
	TCCR1B |= 1<<WGM13 | 1<<WGM12 | 1<<CS10;
	ICR1 = 19999;

	//OCR1A = ICR1 - 2000; //18000
     
	
	while (1)
	{
		if(PINA &(1<<0))
		{
			OCR1A = ICR1 - 800;
			//_delay_ms(100);
		}
		
		if(PINA &(1<<1))
		{
			
		OCR1A = ICR1 - 2200;
		//_delay_ms(100);
		}
	}
}