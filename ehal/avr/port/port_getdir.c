#include "port.h"
#include "port_internal.h"

port_t port_getdir (void *_p)
{
	struct port_mem_block *p = _p;
	return ~p->dir;
}
