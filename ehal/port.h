#ifndef __PORT_H_
#define __PORT_H_

#include "types.h"
#include "port_specific.h"

#define ALL_PINS	((port_t)-1)

/* Port Interface. */
void	port_write	(u08 p, port_t mask, port_t val);
port_t	port_read	(u08 p);

void	port_set_pullup	(u08 p, port_t mask, port_t val);
void	port_get_pullup	(u08 p, port_t mask, port_t val);
void	port_set_dir	(u08 p, port_t mask, port_t dir);
port_t	port_get_dir	(u08 p);

u08	port_validate	(u08 p);

#endif
