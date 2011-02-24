#include "pin.h"
#include "port.h"

bool pin_islow (struct pin_t p)
{
	return (port_read (p.port) & (1<<p.pin)) ? 0 : 1;
}
