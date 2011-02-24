#include "pin.h"
#include "port.h"

void pin_setout (struct pin_t p)
{
	port_setdir (p.port, 1<<p.pin, 0);
}
