/** @file 
 * @defgroup pin pin
 * @{
 * @example pinex.c */

#ifndef EHAL_PIN
#define EHAL_PIN

#include "tinytypes.h"
#include "pin_specific.h"

#define PIN_ISOUT	0	/**< pin_getdir */
#define PIN_ISIN	1	/**< pin_getdir */
#define PIN_ISLOW	0	/**< pin_getval */
#define PIN_ISHIGH	1	/**< pin_getval */

/** @return pin_t, where pin is a enum en_pin_number.
 * @note This function can return invalid pins, to make sure validate it
 * before using. */
void *pin_init (u08 port, u08 pin);

/** @return 1 ok, 0 for error. */
u08 pin_isvalid (void *p);

/** PIN must be output, or you'll get an undefined behaviour */
void pin_sethigh (void *p);

/** PIN must be output, or you'll get an undefined behaviour */
void pin_setlow (void *p);

/** PIN must be output, or you'll get an undefined behaviour */
void pin_setval (void *p, u08 v);

/** true if pin is high */
u08 pin_ishigh (void *p);

/** true if pin is low */
u08 pin_islow (void *p);

/** set it to input. */
void pin_setin (void *p);

/** set it to output. */
void pin_setout (void *p);

/** set it to in if (v) or out if not. */
void pin_setdir (void *p, u08 v);

/** @return 1 for in, 0 for out. */
u08 pin_getdir (void *p);


/* :TODO: These names are terrible... */
void pin_setpullup (void *p);
void pin_clrpullup (void *p);
u08 pin_getpullup (void *p);

void pin_setpulldn (void *p);
void pin_clrpulldn (void *p);
u08 pin_getpullup (void *p);

#endif /* __PIN_H_ */
/** @} */ /* defgroup pin */
