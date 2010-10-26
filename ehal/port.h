/** @file
 * @defgroup port port
 * @{
 * @example portpinex.c
 */
#ifndef __PORT_H_
#define __PORT_H_

#include "types.h"
#include "port_specific.h"

/** Mask with all pins. */
#define ALL_PINS	((port_t)-1)

/** Put the port in a know state.
 * Input, no pullup, no pulldown, no interrupt.
 * @arg id - port id.
 * @note check if it is valid before using any other function with
 * @port_isvalid.
 */
void	port_init	(u08 id);

/** Runtime validation of a port @a id. return 1 for a valid port.
 * @arg id - port id.
 */
u08	port_isvalid	(u08 id);

/** Set (HIGH/LOW)
 * @arg id - port id.
 * @arg mask - masks the bits that will be changed.
 * @arg val - the new values for the masked bits. */
void	port_write	(u08 id, port_t mask, port_t val);

/** Read the port value, all its pins.
 * @note The pins read must be in input state otherwise the behaviour is
 * undefined. */
port_t	port_read	(u08 id);


/** Set pullup, the arguments work like the port_write function.
 * @arg id - port id.
 * @arg mask - masks the bits that will be changed.
 * @arg val - the new values for the masked bits. */
void	port_setpullup	(u08 id, port_t mask, port_t val);

/** Read the current the pullups.
 * @arg id - port id.
 */
port_t	port_getpullup	(u08 id);

/** Set pull down, the arguments work like the port_write function.
 * @arg id - port id.
 * @arg mask - masks the bits that will be changed.
 * @arg val - the new values for the masked bits. */
void	port_setpulldn	(u08 id, port_t mask, port_t val);

/** Read the current position of the pullups. */
port_t	port_getpulldn	(u08 id);

/** Change the port direction (IN/OUT).
 * @arg id - port id.
 * @arg mask - masks the bits that will be changed.
 * @arg val - the new values for the masked bits. 1 - in, 0 - out. */
void	port_setdir	(u08 id, port_t mask, port_t val);

/** Get the port direction.
 * @arg id - port id. */
port_t	port_getdir	(u08 id);

#endif /* __PORT_H_ */

/** @} */ /* @defgroup port */
