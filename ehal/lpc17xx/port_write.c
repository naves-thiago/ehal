#include "port.h"

#define port_mask(p, m, v) do { p = ((p) & ~(m)) | ((v) & (m)); } while(0)

#define PULLUP 0
#define TRISTATE 0xAAAAAAAA
#define PULLDOWN 0xFFFFFFFF

static __IO uint32_t * pinmode[] = {
  &(LPC_PINCON->PINMODE0),
  &(LPC_PINCON->PINMODE1),
  &(LPC_PINCON->PINMODE2),
  &(LPC_PINCON->PINMODE3),
  &(LPC_PINCON->PINMODE4),
  &(LPC_PINCON->PINMODE5)
};

void port_write (void *_p, port_t mask, port_t val )
{
	struct port_mem_block *p = _p;
  p->mask = ~mask;
  p->data = val;
//	port_mask (p->data, mask, val);
}


void port_setpullup(void *port, port_t mask, port_t val)
{
  int id = port_get_id(port) * 2; // Register ID
  uint32_t l, h;                  // Low, Hi bit Pairs
  int i;                          // Loop
  l = *pinmode[id];
  h = *pinmode[id+1];

  // Lower 16 bits
  for (i=0; i<16; i++)
  {
    if (mask & 1<<i)
    {
      if (val & 1<<i) // Set Pull UP ( code 0b00 )
        port_mask( l, 3<<(i*2), PULLUP );
      else // Set Tri-state ( code 0b10 )
        port_mask( l, 3<<(i*2), TRISTATE );
    }
  }

  // Upper 16 bits
  val = val >> 16;
  mask = mask >> 16;
  for (i=0; i<16; i++)
  {
    if (mask & 1<<i)
    {
      if (val & 1<<i) // Set Pull UP
        port_mask( h, 3<<(i*2), PULLUP );
      else // Set Tri-state
        port_mask( h, 3<<(i*2), TRISTATE );
    }
  }

  *pinmode[id] = l;
  *pinmode[id+1] = h;
}

void port_setpulldown(void *port, port_t mask, port_t val)
{
  int id = port_get_id(port) * 2; // Register ID
  uint32_t l, h;                  // Low, Hi bit Pairs
  int i;                          // Loop
  l = *pinmode[id];
  h = *pinmode[id+1];

  // Lower 16 bits
  for (i=0; i<16; i++)
  {
    if (mask & 1<<i)
    {
      if (val & 1<<i) // Set Pull DOWN ( code 0b11 )
        port_mask( l, 3<<(i*2), PULLDOWN );
      else // Set Tri-state ( code 0b10 )
        port_mask( l, 3<<(i*2), TRISTATE );
    }
  }

  // Upper 16 bits
  val = val >> 16;
  mask = mask >> 16;
  for (i=0; i<16; i++)
  {
    if (mask & 1<<i)
    {
      if (val & 1<<i) // Set Pull DOWN
        port_mask( h, 3<<(i*2), PULLDOWN );
      else // Set Tri-state
        port_mask( h, 3<<(i*2), TRISTATE );
    }
  }

  *pinmode[id] = l;
  *pinmode[id+1] = h;
}

void port_settristate(void *port, port_t mask, port_t val)
{
  int id = port_get_id(port) * 2; // Register ID
  uint32_t l, h;                // Low, Hi bit Pairs
  int i;                        // Loop
  l = *pinmode[id];
  h = *pinmode[id+1];

  mask &= val;

  // Lower 16 bits
  for (i=0; i<16; i++)
    if (mask & 1<<i)
      port_mask( l, 3<<(i*2), TRISTATE );

  // Upper 16 bits
  mask = mask >> 16;
  for (i=0; i<16; i++)
    if (mask & 1<<i)
      port_mask( h, 3<<(i*2), PULLUP );

  *pinmode[id] = l;
  *pinmode[id+1] = h;
}

