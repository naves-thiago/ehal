/** @file
 * @defgroup port port
 * @{
 * @example portpinex.c */
#ifndef EHAL_PORT_H
#define EHAL_PORT_H

#include "tinytypes.h"
#include "port_specific.h"

#ifdef EHAL_GLOBAL
#include "ehal_global.h"
#endif

/** Mask with all pins. */
#define ALL_PINS	((port_t)-1)

void *port_init (unsigned int id);

int port_get_id (void *port);

void port_write (void *port, port_t mask, port_t val);
port_t port_read (void *port);

void port_setdir (void *port, port_t mask, port_t val);
port_t port_getdir (void *port);

void port_setpullup (void *port, port_t mask, port_t val);
port_t port_getpullup (void *port);

void port_setpulldown (void *port, port_t mask, port_t val);
port_t port_getpulldown (void *port);

void port_settristate(void *port, port_t mask, port_t val);

#endif /* EHAL_PORT_H */

/** @} */ /* @defgroup port */
