/** @file
 * @defgroup port port
 * @{
 * @example portpinex.c
 */
#ifndef __PORT_H_
#define __PORT_H_

#include "types.h"
#include "port_specific.h"

/** @brief for a mast with all pins from a port. */
#define ALL_PINS	((port_t)-1)

/* Port Interface. */
/** @brief write @a val from port @a p foreach bit from @a mask that is 1 */
void	port_write	(u08 p, port_t mask, port_t val);
port_t	port_read	(u08 p);

void	port_set_pullup	(u08 p, port_t mask, port_t val);
void	port_get_pullup	(u08 p, port_t mask, port_t val);
void	port_set_dir	(u08 p, port_t mask, port_t dir);
port_t	port_get_dir	(u08 p);

u08	port_is_valid	(u08 p);

#endif
