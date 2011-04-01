#include "port.h"
#include "port_internal.h"

void port_write (void *_p, port_t mask, port_t val )
{
	struct port_mem_block *p = _p;
	port_mask (p->write, mask, val);
}

void port_setpullup(void *_p, port_t mask, port_t up)
	__attribute__ ((alias("port_write")));

