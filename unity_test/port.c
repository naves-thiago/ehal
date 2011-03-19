/*******************************************************************************
 * @file
 * This is partial port test.
 ******************************************************************************/

#include "ehal/port.h"
#define LONG_TIME 10000000

void error (void)
{
	/* TODO: signal an error to the tester. */
	exit (1);
}

int main (void)
{
	unsigned int i;
	port_t v;
	void *p;

	p = port_init (0);

	/* Mirror the 0,1,2,3 bits into 4,5,6,7. */
	i = LONG_TIME;
	port_setdir (p, ALL_PINS, 0x0F);
	while (i--){
		v = port_read (p) & 0x0F;
		port_write (p, ALL_PINS, v<<4);
	}

	/* Mirror the 0,1,2,3 bits into 4,5,6,7. With pullup enabled */
	i = LONG_TIME;
	port_setdir (p, ALL_PINS, 0x0F);
	port_setpullup (p, ALL_PINS, 0x0F);
	while (i--){
		v = port_read (p) & 0x0F;
		port_write (p, ALL_PINS, v<<4);
	}

	/* Toggle the port forever. */
	port_setdir (p, ALL_PINS, 0);
	while (1){
		port_write (p, ALL_PINS, ALL_PINS);
		port_write (p, ALL_PINS, 0);
	}
	return 0;
}
