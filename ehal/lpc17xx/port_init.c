#include <stdio.h>
#include "LPC17xx.h"

#define ARRAY_SIZE(x) (sizeof (x)/sizeof (*x))
static void * port_mem_block[] = {
  LPC_GPIO0,
  LPC_GPIO1,
  LPC_GPIO2
};

void *port_init (unsigned int id)
{
  if (id >= ARRAY_SIZE (port_mem_block)) return NULL;
  return port_mem_block[id];
}

int port_get_id (void *port)
{
  int i, sz;
  sz = ARRAY_SIZE(port_mem_block);
  for (i=0; i < sz; i++)
    if (port_mem_block[i] == port)
      return i;

  return -1; // Not found
}

