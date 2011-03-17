#include "port.h"

#define port_mask(p, m, v) do { p = ((p) & ~(m)) | ((v) & (m)); } while(0)

void port_setdir (void *_p, port_t mask, port_t dir)
{
	struct port_mem_block *p = _p;
  p->mask = ~mask;
  p->dir = ~dir;
//	port_mask (p->dir, mask, ~dir);
}
