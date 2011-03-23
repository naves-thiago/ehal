#include <io.h>
#include "port.h"
#include "port_implementation.h"

void port_write (void *_p, port_t mask, port_t val)
{
	struct port_mem_block *p = _p;
	port_mask (p->out, mask, val);
}
