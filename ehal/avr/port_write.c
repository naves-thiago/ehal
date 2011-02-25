#include "port.h"

#define port_mask(p, m, v) do { p = ((p) & ~(m)) | ((v) & (m)); } while(0)

void port_write (void *_p, port_t mask, port_t val )
{
	struct port_mem_block *p = _p;
	port_mask (p->write, mask, val);
}

void port_setpullup(void *_p, port_t mask, port_t up)
	__attribute__ ((alias("port_write")));
