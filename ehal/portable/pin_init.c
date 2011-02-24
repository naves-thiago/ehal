#include "pin.h"

struct pin_t pin_init (int port, int pin)
{
	struct pin_t p;
	p.port = port_init (port);
	p.pin = pin;
	return p;
}
