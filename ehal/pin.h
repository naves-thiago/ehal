/** @file 
 * @defgroup pin pin
 * @{
 * @example pinex.c */

#ifndef __PIN_H_
#define __PIN_H_

#include "types.h"
#include "pin_specific.h"
#include "port.h"

#define PIN_ISOUT	0	/**< pin_getdir */
#define PIN_ISIN	1	/**< pin_getdir */
#define PIN_ISLOW	0	/**< pin_getval */
#define PIN_ISHIGH	1	/**< pin_getval */

/** @return pin_t, where pin is a enum en_pin_number.
 * @note This function can return invalid pins, to make sure validate it
 * before using. */
struct pin_t pin_init (u08 port, u08 pin);

/** @return 1 ok, 0 for error. */
u08 pin_isvalid (struct pin_t p);

/** PIN must be output, or you'll get an undefined behaviour */
void pin_sethigh (struct pin_t p);

/** PIN must be output, or you'll get an undefined behaviour */
void pin_setlow (struct pin_t p);

/** PIN must be output, or you'll get an undefined behaviour */
void pin_setval (struct pin_t p, u08 v);

/** PIN must be input, or you'll get an undefined behaviour
 * @return PIN_HIGH for high, PIN_LOW for low */
u08 pin_getval (struct pin_t p);


/** set it to input. */
void pin_setin (struct pin_t p);

/** set it to output. */
void pin_setout (struct pin_t p);

/** set it to in if (v) or out if not. */
void pin_setdir (struct pin_t p, u08 v);

/** @return 1 for in, 0 for out. */
u08 pin_getdir (struct pin_t p);


/* :TODO: These names are terrible... */
void pin_setpullupon (struct pin_t p);
void pin_setpullupoff (struct pin_t p);
void pin_setpullup (struct pin_t p, u08 v);
u08 pin_getpullup (struct pin_t p);

void pin_setpulldnon (struct pin_t p);
void pin_setpulldnoff (struct pin_t p);
void pin_setpulldn (struct pin_t p, u08 v);
u08 pin_getpullup (struct pin_t p);

#endif /* __PIN_H_ */
/** @} */ /* defgroup pin */
