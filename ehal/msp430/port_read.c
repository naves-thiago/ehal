#include <io.h>
#include "port.h"
#include "port_implementation.h"

port_t port_read (void *_p)
{
	struct port_mem_block *p = _p;
	return p->in;
}
