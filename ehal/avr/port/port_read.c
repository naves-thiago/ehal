#include "port.h"
#include "port_internal.h"

port_t port_read (void *_p)
{
	struct port_mem_block *p = _p;
	return p->read;
}

port_t port_getpullup (void *_p)
	__attribute__ ((alias("port_read")));
