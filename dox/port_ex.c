#include "ehal/port.h"

int main (void)
{
	int i;

	void *p = port_init (0);
	port_setdir (p, ALL_PINS, 1);			/* bit 0 is input */
	port_setpullup (p, ALL_PINS, 1);		/* bit 0 is pulled up */
	
	while (port_read (p) & 1);			/* wait a push button. */

	for (i=0; i<NUM_PORTS; i++){
		void *p = port_init (i);		/* Reinitialized */
		int j;

		port_setdir (p, ALL_PINS, 0);		/* All output */
		for (j=0; j<sizeof (port_t); j++)
			port_write (p, ALL_PINS, 1<<j);	/* Enable 1 at a time */
		port_write (p, ALL_PINS, 1<<j);	/* All low */
	}
}
