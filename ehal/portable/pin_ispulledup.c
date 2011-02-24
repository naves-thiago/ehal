#include "pin.h"
#include "port.h"

bool pin_ispulledup (struct pin_t p)
{
	return (port_getpullup (p.port) & (1<<p.pin)) ? PIN_ISHIGH : PIN_ISLOW;
}
