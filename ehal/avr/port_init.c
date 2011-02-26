#include <stdio.h>
#include <avr/io.h>
#include "port.h"
#include "port_internal.h"

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
#else
#error MCU not defined in ehal/avr/port_init.c
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
