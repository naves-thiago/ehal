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
	void *p0;

	p0 = port_init (0);

	hd44780_init ();
	hd44780_write (buff);

	while (1){
	}
}
