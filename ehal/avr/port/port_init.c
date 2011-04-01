#include <stdio.h>
#include <avr/io.h>
#include "port.h"
#include "port_internal.h"

void *port_init (unsigned int id)
{
	void *p = port_getbyid (id);
	port_setdir (p, ALL_PINS, ALL_PINS);
	port_setpullup (p, ALL_PINS, 0);
	return p;
}
