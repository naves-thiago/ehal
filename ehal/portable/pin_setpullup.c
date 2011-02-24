#include "pin.h"
#include "port.h"

void pin_setpullup (struct pin_t p)
{
	port_setpullup (p.port, 1<<p.pin, 1<<p.pin);
}
