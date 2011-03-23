#include <io.h>
#include "port.h"
#include "port_implementation.h"

void port_setdir (void *_p, port_t mask, port_t dir)
{
	struct port_mem_block *p = _p;
	port_mask (p->dir, mask, ~dir);
}
