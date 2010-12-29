#include "pin.h"
#include "port.h"

struct pin_t pin_init (u08 port, u08 pin)
{
	struct pin_t p;
	p.port = port;
	p.pin = pin;
	return p;
}

u08 pin_isvalid (struct pin_t p)
{
	if (!port_isvalid(p.port)) return 0;
	if (p.pin >= PIN_SIZE) return 0;
	return 1;
}


/* value */
void pin_sethigh (struct pin_t p)
{
	port_write (p.port, 1<<p.pin, 1<<p.pin);
}

void pin_setlow (struct pin_t p)
{
	port_write (p.port, 1<<p.pin, 0);
}

void pin_setval (struct pin_t p, u08 v)
{
	if (v) port_write (p.port, 1<<p.pin, 1<<p.pin);
	else port_write (p.port, 1<<p.pin, 0);
}

u08 pin_getval (struct pin_t p)
{
	return (port_read (p.port) & p.pin) ? PIN_ISHIGH : PIN_ISLOW;
}

/* dir */
void pin_setin (struct pin_t p)
{
	port_setdir (p.port, 1<<p.pin, 1<<p.pin);
}

void pin_setout (struct pin_t p)
{
	port_setdir (p.port, 1<<p.pin, 0);
}

void pin_setdir (struct pin_t p, u08 v)
{
	if (v) port_setdir (p.port, 1<<p.pin, 1<<p.pin);
	else port_setdir (p.port, 1<<p.pin, 0);
}

u08 pin_getdir (struct pin_t p);

/* pullup */
void pin_setpullupon (struct pin_t p);
void pin_setpullupoff (struct pin_t p);
void pin_setpullup (struct pin_t p, u08 v);
u08 pin_getpullup (struct pin_t p);


