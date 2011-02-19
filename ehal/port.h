/** @file
 * @defgroup port port
 * @{
 * @example portpinex.c */
#ifndef EHAL_PORT
#define EHAL_PORT

#include "tinytypes.h"
#include "port_specific.h"

/** Mask with all pins. */
#define ALL_PINS	((port_t)-1)

void *port_init (int p);
void *port_isvalid (int p);
void port_write (void *p, port_t mask, port_t val);
void port_setdir (void *p, port_t mask, port_t val);
port_t port_read (void *p);

#endif /* __PORT_H_ */

/** @} */ /* @defgroup port */
