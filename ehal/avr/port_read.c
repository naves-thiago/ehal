#include "port.h"

#define port_mask(p, m, v) do { p = ((p) & ~(m)) | ((v) & (m)); } while(0)

port_t port_read (void *_p)
{
	struct port_mem_block *p = _p;
	return p->read;
}

port_t port_getpullup (void *_p)
	__attribute__ ((alias("port_read")));
