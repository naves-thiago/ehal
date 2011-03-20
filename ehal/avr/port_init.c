#include <stdio.h>
#include <avr/io.h>
#include "port.h"
#include "port_internal.h"

#define ARRAY_SIZE(x) (sizeof (x)/sizeof(*x))
#define BIND_INDEX_WITH_PORT(BLOCK_START)\
	(struct port_mem_block *)&PIN ## BLOCK_START

#if defined (ehal_attiny25)	\
	|| (ehal_attiny45)	\
	|| (ehal_attiny85)
struct port_mem_block *port_mem_block[] = {
	BIND_INDEX_WITH_PORT (B),
};
#elif defined (ehal_atmega8)	\
	|| defined (ehal_atmega48)	\
	|| defined (ehal_atmega88)	\
	|| defined (ehal_atmega168)	\
	|| defined (ehal_atmega328)
struct port_mem_block *port_mem_block[] = {
	BIND_INDEX_WITH_PORT (B),
	BIND_INDEX_WITH_PORT (C),
	BIND_INDEX_WITH_PORT (D),
};
#elif	defined (ehal_atmega168p)
struct port_mem_block *port_mem_block[] = {
	BIND_INDEX_WITH_PORT (B),
	BIND_INDEX_WITH_PORT (C),
	BIND_INDEX_WITH_PORT (D),
};

#elif defined (ehal_atmega16)	\
	|| defined (ehal_atmega32)
struct port_mem_block *port_mem_block[] = {
	BIND_INDEX_WITH_PORT (A),
	BIND_INDEX_WITH_PORT (B),
	BIND_INDEX_WITH_PORT (C),
	BIND_INDEX_WITH_PORT (D),
};
#elif defined (ehal_atmega164p)
struct port_mem_block *port_mem_block[] = {
	BIND_INDEX_WITH_PORT (A),
	BIND_INDEX_WITH_PORT (B),
	BIND_INDEX_WITH_PORT (C),
	BIND_INDEX_WITH_PORT (D),
};
#elif defined (ehal_atmega128)
struct port_mem_block *port_mem_block[] = {
	BIND_INDEX_WITH_PORT (A),
	BIND_INDEX_WITH_PORT (B),
	BIND_INDEX_WITH_PORT (C),
	BIND_INDEX_WITH_PORT (D),
	BIND_INDEX_WITH_PORT (E),
	BIND_INDEX_WITH_PORT (F),
	BIND_INDEX_WITH_PORT (G),
};
#endif

void *port_init (unsigned int id)
{
	void *p;
	if (id >= ARRAY_SIZE (port_mem_block)) return NULL;
	p = port_mem_block[id];

	port_setdir (p, ALL_PINS, ALL_PINS);
	port_setpullup (p, ALL_PINS, 0);
	return p;
}
