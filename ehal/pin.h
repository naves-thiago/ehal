#ifndef __PIN_H_
#define __PIN_H_

#include "types.h"
#include "pin_specific.h"
#include "port.h"

struct pin_t pin_init (u08 port, u08 pin)
{
	struct pin_t p = {port, pin};
	return p;
}

u08 pin_validate (struct pin_t p)
{
	if (!port_validate(p.port)) return 0;
	if (p.pin >= PIN_SIZE) return 0;
	return 1;
}

/* value */
void pin_high (struct pin_t p)
{
	port_write (p.port, 1<<p.pin, 1<<p.pin);
}

void pin_low (struct pin_t p)
{
	port_write (p.port, 1<<p.pin, 0);
}

void pin_setvalue (struct pin_t p, u08 v)
{
	if (v) port_write (p.port, 1<<p.pin, 1<<p.pin);
	else port_write (p.port, 1<<p.pin, 0);
}

u08 pin_get_val (struct pin_t p)
{
	return (port_read (p.port) & p.pin) ? 1 : 0;
}

/* dir */
void pin_in (struct pin_t p)
{
	port_set_dir (p.port, 1<<p.pin, 1<<p.pin);
}

void pin_out (struct pin_t p)
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
void pin_pullup (struct pin_t p);
void pin_nopullup (struct pin_t p);
void pin_setpullup (struct pin_t p, u08 v);
u08 pin_getpullup (struct pin_t p);

#endif
