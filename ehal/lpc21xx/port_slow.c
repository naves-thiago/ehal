#include "types.h"
#include "lpc210x_gnuarm.h"
#include "port_specific.h"

#define port_mask(p, v, m) do { p = ((p) & ~(m)) | ((v) & (m)); } while(0)
#define ARRAY_SIZE(x)	(sizeof(x) / sizeof(x[0]))

struct port {
	volatile u32 *pin;
	volatile u32 *set;
	volatile u32 *dir;
	volatile u32 *clear;
};

static const struct port *port[] = { &GPIO0_IOPIN
};

void port_write (u08 p, port_t mask, port_t val)
{
	*port[p]->set = mask & val;
	*port[p]->clear = mask & ~val;
}
void port_dir (u08 p, port_t mask, port_t dir)
{
	port_mask (*port[p]->dir, mask, dir);
}
void port_pullup (u08 p, port_t mask, port_t up)
{
}

port_t port_read (u08 p, port_t mask)
{
	return 0;
}
