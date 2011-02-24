/** @file
 * @defgroup port port
 * @{
 * @example portpinex.c */
#ifndef EHAL_PORT
#define EHAL_PORT

#include "tinytypes.h"
#include "port_specific.h"

#ifdef EHAL_GLOBAL
#include "ehal_global.h"
#endif

/** Mask with all pins. */
#define ALL_PINS	((port_t)-1)

void *port_init (int id);

void port_write (void *port, port_t mask, port_t val);
port_t port_read (void *port);

void port_setpullup (void *port, port_t mask, port_t val);
void port_setdir (void *port, port_t mask, port_t val);
port_t port_getdir (void *port);

#endif /* __PORT_H_ */

/** @} */ /* @defgroup port */
