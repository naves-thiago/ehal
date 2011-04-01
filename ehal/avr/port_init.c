#include <stdio.h>
#include <avr/io.h>
#include "port.h"
#include "port_internal.h"

#define ARRAY_SIZE(x) (sizeof (x)/sizeof(*x))
#define BIND_INDEX_WITH_PORT(BLOCK_START)\
	(struct port_mem_block *)&PIN ## BLOCK_START

static struct port_mem_block *port_mem_block[] = {
#if defined (attiny25)	\
	|| (attiny45)	\
	|| (attiny85)
	BIND_INDEX_WITH_PORT (B),
#elif defined (atmega8)	\
	|| defined (atmega48)	\
	|| defined (atmega88)	\
	|| defined (atmega168)	\
	|| defined (atmega328)
	BIND_INDEX_WITH_PORT (B),
	BIND_INDEX_WITH_PORT (C),
	BIND_INDEX_WITH_PORT (D),
#elif	defined (atmega168p)
	BIND_INDEX_WITH_PORT (B),
	BIND_INDEX_WITH_PORT (C),
	BIND_INDEX_WITH_PORT (D),
#elif defined (atmega16)	\
	|| defined (atmega32)
	BIND_INDEX_WITH_PORT (A),
	BIND_INDEX_WITH_PORT (B),
	BIND_INDEX_WITH_PORT (C),
	BIND_INDEX_WITH_PORT (D),
#elif defined (atmega164p)
	BIND_INDEX_WITH_PORT (A),
	BIND_INDEX_WITH_PORT (B),
	BIND_INDEX_WITH_PORT (C),
	BIND_INDEX_WITH_PORT (D),
#elif defined (atmega128)
	BIND_INDEX_WITH_PORT (A),
	BIND_INDEX_WITH_PORT (B),
	BIND_INDEX_WITH_PORT (C),
	BIND_INDEX_WITH_PORT (D),
	BIND_INDEX_WITH_PORT (E),
	BIND_INDEX_WITH_PORT (F),
	BIND_INDEX_WITH_PORT (G),
#endif
};

void *port_init (unsigned int id)
{
	void *p;
	if (id >= ARRAY_SIZE (port_mem_block)) return NULL;
	p = port_mem_block[id];

	port_setdir (p, ALL_PINS, ALL_PINS);
	port_setpullup (p, ALL_PINS, 0);
	return p;
}
