/*
ds1307 lib sample

copyright (c) Davide Gironi, 2013

Released under GPLv3.
Please refer to LICENSE file for licensing information.
*/

#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "uart/uart.h"
#define UART_BAUD_RATE 2400

#include "ds1307/ds1307.h"

int main(void) {
	//init uart
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );

	//init ds1307
	ds1307_init();

	sei();

	uart_puts("startup...");

	uint8_t year = 0;
	uint8_t month = 0;
	uint8_t day = 0;
	uint8_t hour = 0;
	uint8_t minute = 0;
	uint8_t second = 0;

	//check set date
	ds1307_setdate(12, 12, 31, 23, 59, 35);


	for(;;) {
		//get date
		ds1307_getdate(&year, &month, &day, &hour, &minute, &second);

		char buf[50];
		sprintf(buf, "%d/%d/%d %d:%d:%d", year, month, day, hour, minute, second);
		uart_puts(buf);	uart_puts("\r\n");

		_delay_ms(1000);
	}

}
