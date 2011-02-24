#include "port.h"
#include "port_specific.h"

#define BIND_INDEX_WITH_PORT(BLOCK_START)\
	(struct port_mem_block *)&P ## BLOCK_START ##IN

#if defined (ehal_msp430x2012)
struct  port_mem_block *port_mem_block[] = {
	BIND_INDEX_WITH_PORT(1),
	BIND_INDEX_WITH_PORT(2),
	
};
/* #elif defined (...) */
#endif

void *port_init (unsigned int id)
{
	struct port_mem_block *p;
	if (id < sizeof (port_mem_block)/sizeof (*port_mem_block))
		p = port_mem_block[id];
	else
		return (void *)0;
	p->sel = 0x00;
	port_setdir (p, 0xFF, 0xFF);
	return p;
}
