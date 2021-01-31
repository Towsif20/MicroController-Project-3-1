/*
 * UART.h
 *
 * Created: 7/29/2019 8:01:41 PM
 *  Author: md ashraful islam
 */ 


#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)     // convert to baudrate dec value

void UART_init(long USART_BAUDRATE)
{
	UCSRA = 0b00000010;  // double speed
	UCSRB = 0b00011000;  // Enable Tx and Rx, polling
	UCSRC = 0b10000110;  // Async mode, no parity, 1 stop bit, 				8 data bits
	//in double-speed mode, UBRR = clock/(8xbaud rate) - 1
	UBRRH = 0;
	UBRRL = 12; // Baud rate 9600bps, assuming 1MHz clock

}

void UART_send(char data){
	// wait until UDRE flag is set to logic 1
	while ((UCSRA & (1<<UDRE)) == 0x00);	
	UDR = data; // Write character to UDR for transmission
}

char UART_receive(void){
	// Wait until RXC flag is set to logic 1
	while ((UCSRA & (1<<RXC)) == 0x00);	
	return UDR; // Read the received character from UDR
}
