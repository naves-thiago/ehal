#include "pin.h"
#include "port.h"

/* TODO: This only tests for a valid port */
bool pin_isvalid (struct pin_t p)
{
	if (!p.port) return 0;
	return 1;
}
