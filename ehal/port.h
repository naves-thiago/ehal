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

/** @{ */
/* Port Interface. */
/** @brief write @a val from port @a id foreach bit from @a mask that is 1
 * @arg id - port id.
 * @arg mask - masks the bits that will be changed.
 * @arg val - the new values for the masked bits. */
void	port_write	(u08 id, port_t mask, port_t val);
/** @brief read the port value, all its pins.
 * @note The port must be an input or you'll get an undefined behaviour. */
port_t	port_read	(u08 id);
/** @} */

/** @brief set pullup, the arguments work like the port_write function. */
void	port_set_pullup	(u08 id, port_t mask, port_t val);
/** @brief read the current position of the pullups. */
port_t	port_get_pullup	(u08 id);
/** Change the port direction, 1 for In, 0 for Out, the arguments are the
 * same as the @see port_write function. */
void	port_set_dir	(u08 id, port_t mask, port_t dir);
port_t	port_get_dir	(u08 id);

/** @brief For runtime validation of a given port. return 1 if valid. */
u08	port_is_valid	(u08 id);

#endif /* __PORT_H_ */

/** @} */ /* @defgroup port */
