#include "pin.h"

struct pin_t pin_init (u08 port, u08 pin)
{
	struct pin_t p;
	p.port = port;
	p.pin = pin;
	return p;
}

u08 pin_isvalid (struct pin_t p)
{
	if (!port_is_valid(p.port)) return 0;
	if (p.pin >= PIN_SIZE) return 0;
	return 1;
}


/* value */
void pin_set_high (struct pin_t p)
{
	port_write (p.port, 1<<p.pin, 1<<p.pin);
}

void pin_set_low (struct pin_t p)
{
	port_write (p.port, 1<<p.pin, 0);
}

void pin_set_val (struct pin_t p, u08 v)
{
	if (v) port_write (p.port, 1<<p.pin, 1<<p.pin);
	else port_write (p.port, 1<<p.pin, 0);
}

u08 pin_get_val (struct pin_t p)
{
	return (port_read (p.port) & p.pin) ? PIN_IS_HIGH : PIN_IS_LOW;
}

/* dir */
void pin_set_in (struct pin_t p)
{
	port_set_dir (p.port, 1<<p.pin, 1<<p.pin);
}

void pin_set_out (struct pin_t p)
{
	port_set_dir (p.port, 1<<p.pin, 0);
}

void pin_set_dir (struct pin_t p, u08 v)
{
	if (v) port_set_dir (p.port, 1<<p.pin, 1<<p.pin);
	else port_set_dir (p.port, 1<<p.pin, 0);
}

u08 pin_get_dir (struct pin_t p);

/* pullup */
void pin_set_pullup (struct pin_t p);
void pin_set_pullupoff (struct pin_t p);
void pin_set_pullup_val (struct pin_t p, u08 v);
u08 pin_get_pullup (struct pin_t p);


