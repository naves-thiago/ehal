/*******************************************************************************
 * @file
 * This is a simple test, suposed to toogle leds or something like that.
 ******************************************************************************/

#include "ehal/port.h"

int main (void)
{
	void *p;

	p = port_init (0);

	port_setdir (p, ALL_PINS, 0x0F);
	while (1){
		port_write (p, ALL_PINS, ALL_PINS);
		port_write (p, ALL_PINS, 0);
	}
	return 0;
}
