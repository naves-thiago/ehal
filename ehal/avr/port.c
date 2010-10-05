#include "types.h"
#include "port_specific.h"
#include "config.h"

#define PORT_BIND_WITH_INDEX(BLOCK_START)\
	(struct port_mem_block *)&PIN ## BLOCK_START

/* Mapping of Port with port_ functions index.
 * The letters must be upper case. */
struct port_mem_block {
	volatile u08 read;
	volatile u08 dir;
	volatile u08 write;
};

#if defined (__AVR_ATtiny25__)	\
	|| (__AVR_ATtiny45__)	\
	|| (__AVR_ATtiny85__)
struct port_mem_block *port_mem_block[] = {
	PORT_BIND_WITH_INDEX (B),
};

#elif defined (__AVR_ATmega8__)	\
	|| defined (__AVR_ATmega48__)	\
	|| defined (__AVR_ATmega88__)	\
	|| defined (__AVR_ATmega168__)
struct port_mem_block *port_mem_block[] = {
	PORT_BIND_WITH_INDEX (B),
	PORT_BIND_WITH_INDEX (C),
	PORT_BIND_WITH_INDEX (D),
};
#elif	defined (__AVR_ATmega168P__)
struct port_mem_block *port_mem_block[] = {
	PORT_BIND_WITH_INDEX (B),
	PORT_BIND_WITH_INDEX (C),
	PORT_BIND_WITH_INDEX (D),
};

#elif defined (__AVR_ATmega16__)	\
	|| defined (__AVR_ATmega32__)
struct port_mem_block *port_mem_block[] = {
	PORT_BIND_WITH_INDEX (A),
	PORT_BIND_WITH_INDEX (B),
	PORT_BIND_WITH_INDEX (C),
	PORT_BIND_WITH_INDEX (D),
};

#elif defined (__AVR_ATmega164P__)
struct port_mem_block *port_mem_block[] = {
	PORT_BIND_WITH_INDEX (A),
	PORT_BIND_WITH_INDEX (B),
	PORT_BIND_WITH_INDEX (C),
	PORT_BIND_WITH_INDEX (D),
};

#elif defined (__AVR_ATmega128__)
struct port_mem_block *port_mem_block[] = {
	PORT_BIND_WITH_INDEX (A),
	PORT_BIND_WITH_INDEX (B),
	PORT_BIND_WITH_INDEX (C),
	PORT_BIND_WITH_INDEX (D),
	PORT_BIND_WITH_INDEX (E),
	PORT_BIND_WITH_INDEX (F),
	PORT_BIND_WITH_INDEX (G),
};

#else
#error MCU not defined in ehal/avr/port.c
#endif

#define port_mask(p, m, v) do { p = ((p) & ~(m)) | ((v) & (m)); } while(0)
void port_write (u08 p, port_t mask, port_t val )
{
	port_mask (port_mem_block[p]->write, mask, val);
}

port_t port_read (u08 p)
{
	return port_mem_block[p]->read;
}

void port_set_pullup(u08 p, port_t mask, port_t up)
	__attribute__ ((alias("port_write")));

void port_set_dir (u08 p, port_t mask, port_t dir)
{
	port_mask (port_mem_block[p]->dir, mask, ~dir);
}

port_t port_get_dir (u08 p)
{
	return port_mem_block[p]->dir;
}

u08 port_validate (u08 p)
{
	return p < PORT_NUM;
}
