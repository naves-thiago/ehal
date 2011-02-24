#include "pin.h"
#include "port.h"

/* value */
void pin_sethigh (struct pin_t p)
{
	port_write (p.port, 1<<p.pin, 1<<p.pin);
}
