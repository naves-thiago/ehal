#include <stdio.h>
#include <avr/io.h>
#include "port.h"

#define BIND_INDEX_WITH_PORT(BLOCK_START)\
	(struct port_mem_block *)&PIN ## BLOCK_START

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

void *port_init (unsigned int id)
{
	void *p;
	if (id < sizeof(port_mem_block)/sizeof (*port_mem_block))
		p = port_mem_block[id];
	else
		return NULL;
	port_setdir (p, 0xFF, 0xFF);
	return p;
}
