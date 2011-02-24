#include "pin.h"
#include "port.h"

void pin_setlow (struct pin_t p)
{
	port_write (p.port, 1<<p.pin, 0);
}
