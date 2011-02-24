#include "pin.h"
#include "port.h"

/* dir */
void pin_setin (struct pin_t p)
{
	port_setdir (p.port, 1<<p.pin, 1<<p.pin);
}
