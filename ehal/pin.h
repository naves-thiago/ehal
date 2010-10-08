/** @file 
 * @defgroup pin pin
 * FIXME: Broken example tag
 * @{
 * @example pin_example.c */
#ifndef __PIN_H_
#define __PIN_H_

#include "types.h"
#include "pin_specific.h"
#include "port.h"

/** @brief macro for making the (1 << pin_number), will become P0, P1... */
#define ENUM_EPIN(_p) P ## _p = (1 << _p)
/*
enum en_pin_number {
	ENUM_EPIN(0),  ENUM_EPIN(1),  ENUM_EPIN(2),  ENUM_EPIN(3),
	ENUM_EPIN(4), ENUM_EPIN(5),  ENUM_EPIN(6), ENUM_EPIN(7),
	ENUM_EPIN(8),  ENUM_EPIN(9), ENUM_EPIN(10), ENUM_EPIN(11),
	ENUM_EPIN(12), ENUM_EPIN(13), ENUM_EPIN(14), ENUM_EPIN(15),
	ENUM_EPIN(16), ENUM_EPIN(17), ENUM_EPIN(18), ENUM_EPIN(19),
	ENUM_EPIN(20), ENUM_EPIN(21), ENUM_EPIN(22), ENUM_EPIN(23),
	ENUM_EPIN(24), ENUM_EPIN(25), ENUM_EPIN(26), ENUM_EPIN(27),
	ENUM_EPIN(28), ENUM_EPIN(29), ENUM_EPIN(30), ENUM_EPIN(31),
};
*/

#define PIN_OUT		0	
/** output */
#define PIN_IN		1	/*! input */
#define PIN_LOW		0
#define PIN_HIGH	1

/** @return pin_t, where pin is a enum en_pin_number.
 * @note This function can return invalid pins, to make sure validate it
 * before using. */
struct pin_t pin_init (u08 port, u08 pin);

/** @return 1 ok, 0 for error. */
u08 pin_is_valid (struct pin_t p);

/** @name value
 * @{ */
/** PIN must be output, or you'll get an undefined behaviour */
void pin_high (struct pin_t p);

/** PIN must be output, or you'll get an undefined behaviour */
void pin_low (struct pin_t p);

/** PIN must be output, or you'll get an undefined behaviour */
void pin_set (struct pin_t p, u08 v);

/** PIN must be input, or you'll get an undefined behaviour
 * @return PIN_HIGH for high, PIN_LOW for low */
u08 pin_get (struct pin_t p);
/** @} */

/** @name direction
 * @{ */
/** set it to input. */
void pin_in (struct pin_t p);

/** set it to output. */
void pin_out (struct pin_t p);

/** set it to in if (v) or out if not. */
void pin_set_dir (struct pin_t p, u08 v);

/** @return 1 for in, 0 for out. */
u08 pin_get_dir (struct pin_t p);
/** @} */

/** @name pullup
 * @{ */
void pin_pullup (struct pin_t p);
void pin_nopullup (struct pin_t p);
void pin_setpullup (struct pin_t p, u08 v);
u08 pin_getpullup (struct pin_t p);
/** @} */

#endif /* __PIN_H_ */
/** @} */ /* defgroup pin */
