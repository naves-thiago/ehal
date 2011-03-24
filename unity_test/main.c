#include "ehal/port.h"
#include "ehal/uart.h"
#include "ehal/cpu.h"
#include <avr/interrupt.h>
#include "hd44780.h"

void hd44780_write (char *str)
{
	while (*str){
		hd44780_write_buff_char (*str);
		str++;
	}
	hd44780_write_buff ();
}

int main (void)
{
	char buff[] = "eHal!";
	unsigned char c;
	void *p0;
	void *u0;

	cpu_init ();
	p0 = port_init (0);
	u0 = uart_init (0);
	cpu_gie ();

	hd44780_init ();
	hd44780_write (buff);

	uart_write (u0, buff, sizeof (buff)-1);
	while (1){
		uart_read (u0, &c, 1);
		hd44780_write_buff_char (c);
		if (c == '\r') hd44780_write_buff ();
	}
}
