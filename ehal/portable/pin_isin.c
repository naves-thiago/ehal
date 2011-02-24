#include "pin.h"
#include "port.h"

bool pin_isin (struct pin_t p)
{
	return (port_getdir (p.port) & (1<<p.pin));
}
