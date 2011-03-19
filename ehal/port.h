/*******************************************************************************
 * @file
 * @defgroup port port
 * @{
 * @example TODO:replace_me_with_a_port_example.c
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

/*******************************************************************************
 * Get a port pointer from an index and puts the port in the default eHAL state.
 * That is: no pullup, no pulldown and as input.
 * @param id - The number of the port to work with.
 * @return - The port pointer to be passed to the other functions or NULL.
 * @note All ports start at index 0 and go up to NUM_PORTS.
 * ****************************************************************************/
void *port_init (unsigned int id);

/*******************************************************************************
 * Sets the (val & mask) bits, and clears the ((~val) & mask) bits. That is:
 * Change the bits masked as 1 and ignore the ones masked at 0.
 * @param port - port handler got form port_init.
 * @param mask - the bits to change.
 * @param val - the new value of the masked bits
 ******************************************************************************/
void port_write (void *port, port_t mask, port_t val);

/*******************************************************************************
 * Read the value of port. This function doesn't know about pins operating with
 * secundary functions, make sure you mask its return to the apropriate bits
 * @param port - port handler got form port_init.
 * @return - the bits that the por read.
 * @note, Be carefoul to only take into acount the bits that are input, this is
 * not done automaticaly.
 ******************************************************************************/
port_t port_read (void *port);

/*******************************************************************************
 * Set the direction of port. val is 1 for Input and 0 for Output. The mask
 * works the same as in port_write. 
 * @param port - port handler got form port_init.
 * @param mask - the bits to change.
 * @param val - the new value of the masked bits
 ******************************************************************************/
void port_setdir (void *port, port_t mask, port_t val);

/*******************************************************************************
 * Get the pins direction. 
 * @param port - port handler got form port_init.
 ******************************************************************************/
port_t port_getdir (void *port);

/*******************************************************************************
 * Turn on the pullup on the port. Mask works the same as port_write. 
 * @param port - port handler got form port_init.
 * @param mask - the bits to change.
 * @param val - the new value of the masked bits
 ******************************************************************************/
void port_setpullup (void *port, port_t mask, port_t val);

/*******************************************************************************
 * Get the pullup. 
 * @param port - port handler got form port_init.
 ******************************************************************************/
port_t port_getpullup (void *port);

/*******************************************************************************
 * Turn on the pulldown on the port. Mask works the same as port_write. 
 * @param port - port handler got form port_init.
 * @param mask - the bits to change.
 * @param val - the new value of the masked bits
 ******************************************************************************/
void port_setpulldown (void *port, port_t mask, port_t val);

/*******************************************************************************
 * Get the pulldown. 
 * @param port - port handler got form port_init.
 ******************************************************************************/
port_t port_getpulldown (void *port);

#endif /* EHAL_PORT_H */

/** @} */ /* @defgroup port */
