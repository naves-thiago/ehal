#include <io.h>
#include "port.h"
#include "port_implementation.h"

void port_setpullup (void *_p, port_t mask, port_t pullup)
{
	struct port_mem_block *p = _p;
	port_mask (p->ren, mask, pullup);
}
