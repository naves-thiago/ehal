#include <avr/io.h>
#include <avr/interrupt.h>
#include "ehal/port.h"
#include "ehal/pin.h"
#include "ehal/uart.h"
#include "hd44780.h"

u08 rx[0x0F];

int main(void)
{
	uart_init (0);
	uart_init (1);
	uart_set_baud (0, B9600, F_CPU);
	uart_set_baud (1, B9600, F_CPU);
	sei();

	uart_recv (0, rx, 0x01);

	while (1){
		if (uart_rxdone (0)){
			uart_recv (0, rx, 0x0F);
			uart_send (1, rx, 0x0F);
		}
	}
	return 0;
}
