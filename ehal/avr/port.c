#include <stdio.h>
#include <avr/io.h>
#include "port.h"

#define BIND_INDEX_WITH_PORT(BLOCK_START)\
	(struct port_mem_block *)&PIN ## BLOCK_START

/* Mapping of Port with port_ functions index.
 * The letters must be upper case. */
struct port_mem_block {
	volatile uint8_t read;	/* PINx */
	volatile uint8_t dir;	/* DDRx */
	volatile uint8_t write;	/* PORTx */
};

#if defined (__AVR_ATtiny25__)	\
	|| (__AVR_ATtiny45__)	\
	|| (__AVR_ATtiny85__)
struct port_mem_block *port_mem_block[] = {
	BIND_INDEX_WITH_PORT (B),
};
#elif defined (__AVR_ATmega8__)	\
	|| defined (__AVR_ATmega48__)	\
	|| defined (__AVR_ATmega88__)	\
	|| defined (__AVR_ATmega168__)
struct port_mem_block *port_mem_block[] = {
	BIND_INDEX_WITH_PORT (B),
	BIND_INDEX_WITH_PORT (C),
	BIND_INDEX_WITH_PORT (D),
};
#elif	defined (__AVR_ATmega168P__)
struct port_mem_block *port_mem_block[] = {
	BIND_INDEX_WITH_PORT (B),
	BIND_INDEX_WITH_PORT (C),
	BIND_INDEX_WITH_PORT (D),
};

#elif defined (__AVR_ATmega16__)	\
	|| defined (__AVR_ATmega32__)
struct port_mem_block *port_mem_block[] = {
	BIND_INDEX_WITH_PORT (A),
	BIND_INDEX_WITH_PORT (B),
	BIND_INDEX_WITH_PORT (C),
	BIND_INDEX_WITH_PORT (D),
};
#elif defined (__AVR_ATmega164P__)
struct port_mem_block *port_mem_block[] = {
	BIND_INDEX_WITH_PORT (A),
	BIND_INDEX_WITH_PORT (B),
	BIND_INDEX_WITH_PORT (C),
	BIND_INDEX_WITH_PORT (D),
};
#elif defined (__AVR_ATmega128__)
struct port_mem_block *port_mem_block[] = {
	BIND_INDEX_WITH_PORT (A),
	BIND_INDEX_WITH_PORT (B),
	BIND_INDEX_WITH_PORT (C),
	BIND_INDEX_WITH_PORT (D),
	BIND_INDEX_WITH_PORT (E),
	BIND_INDEX_WITH_PORT (F),
	BIND_INDEX_WITH_PORT (G),
};
#else
#error MCU not defined in ehal/avr/port.c
#endif

#define port_mask(p, m, v) do { p = ((p) & ~(m)) | ((v) & (m)); } while(0)

void *port_get_from_id (int p)
{
	if (p < sizeof(port_mem_block)/sizeof (*port_mem_block))
		return port_mem_block[p];
	return NULL;
}

void *port_init (int id)
{
	void *p = port_get_from_id (id);
	port_setdir (p, 0xFF, 0xFF);
	return p;
}

void port_write (void *_p, port_t mask, port_t val )
{
	struct port_mem_block *p = _p;
	port_mask (p->write, mask, val);
}

port_t port_read (void *_p)
{
	struct port_mem_block *p = _p;
	return p->read;
}

void port_setdir (void *_p, port_t mask, port_t dir)
{
	struct port_mem_block *p = _p;
	port_mask (p->dir, mask, ~dir);
}

port_t port_getdir (void *_p)
{
	struct port_mem_block *p = _p;
	return p->dir;
}

void port_setpullup(void *_p, port_t mask, port_t up)
	__attribute__ ((alias("port_write")));

port_t port_getpullup (void *_p)
	__attribute__ ((alias("port_read")));
