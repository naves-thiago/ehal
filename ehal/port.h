/** @file
 * @defgroup port port
 * @{
 * @example port_ex.c
 ******************************************************************************/
#ifndef EHAL_PORT_H
#define EHAL_PORT_H

#include "tinytypes.h"
#include "port_specific.h"

#ifdef EHAL_GLOBAL
#include "ehal_global.h"
#endif

/** Mask with all pins. */
#define ALL_PINS	((port_t)-1)

#ifndef NUM_PORTS
/** Maximum number of ports for the CPU */
#define NUM_PORTS <defined in port_specific.h>
#endif

/** Get a port pointer from an index and puts the port in the default eHAL state.
 * That is: no pullup, no pulldown and as input.
 * @param id - The number of the port to work with.
 * @return The port pointer to be passed to the other functions or NULL.
 * @note index goes from 0 to @ref NUM_PORTS.
 * ****************************************************************************/
void *port_init (unsigned int id);

/** Sets the (val & mask) bits, and clears the ((~val) & mask) bits. That is:
 * Change the bits masked as 1 and ignore the ones masked at 0.
 * @param port - port handler got form @ref port_init.
 * @param mask - the bits to change.
 * @param val - the new value of the masked bits
 ******************************************************************************/
void port_write (void *port, port_t mask, port_t val);

/** Read the value of port. This function doesn't know about pins operating with
 * secundary functions nor the ones operating as output, both cases gives an
 * undefined behaviour, so be sure to mask only the input bits.
 * @param port - port handler got form @ref port_init.
 * @return the bits that the por read.
 ******************************************************************************/
port_t port_read (void *port);

/** Set the direction of port. (1 - Input, 0 - Output). The mask
 * works the same as in port_write.
 * @param port - port handler got form @ref port_init.
 * @param mask - the bits to change.
 * @param dir - the new value of the masked bits
 ******************************************************************************/
void port_setdir (void *port, port_t mask, port_t dir);

/** Get the pins direction for each bit. (1 - in, 0 - out)
 * @param port - port handler got form @ref port_init.
 ******************************************************************************/
port_t port_getdir (void *port);

/** Turn on the pullup on the port.
 * @param port - port handler got form @ref port_init.
 * @param mask - the bits to change.
 * @param val - the new value of the masked bits
 ******************************************************************************/
void port_setpullup (void *port, port_t mask, port_t val);

/** Get the pullup.
 * @param port - port handler got form @ref port_init.
 ******************************************************************************/
port_t port_getpullup (void *port);

/** Turn on the pulldown on the port.
 * @param port - port handler got form @ref port_init.
 * @param mask - the bits to change.
 * @param val - the new value of the masked bits
 ******************************************************************************/
void port_setpulldown (void *port, port_t mask, port_t val);

/** Get the pulldown.
 * @param port - port handler got form @ref port_init.
 ******************************************************************************/
port_t port_getpulldown (void *port);

#endif /* EHAL_PORT_H */

/** @} */ /* @defgroup port */
