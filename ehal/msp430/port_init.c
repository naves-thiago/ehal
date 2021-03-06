#include <stdio.h>
#include <io.h>
#include "port.h"
#include "port_implementation.h"

#define ARRAY_SIZE(x) (sizeof (x)/sizeof (*x))

#define BIND_INDEX_WITH_PORT(BLOCK_START)\
	(struct port_mem_block *)&P ## BLOCK_START ##IN
/* TODO: Check for msp430/msp430/include/msp430/iostructures.h */
#if defined (ehal_msp430x2012)	\
	|| defined (ehal_msp430x2013)
static struct port_mem_block *port_mem_block[] = {
	BIND_INDEX_WITH_PORT(1),
	BIND_INDEX_WITH_PORT(2),
};
#else

#error invalid MCU, check ehal/msp430/port_init.c.
#endif

void *port_init (unsigned int id)
{
	struct port_mem_block *p;
	if (id >= ARRAY_SIZE (port_mem_block)) return NULL;
	p = port_mem_block[id];
	port_setdir (p, 0xFF, 0xFF);
	return p;
}
