/** @file 
 * @defgroup pin pin
 * @{
 * @example portpin.c */

#ifndef __PIN_H_
#define __PIN_H_

#include "types.h"
#include "pin_specific.h"
#include "port.h"

/** return conditions */
enum pin_ret {			
	PIN_IS_OUT	= 0,	/**< pin_get_dir */
	PIN_IS_IN	= 1,	/**< pin_get_dir */
	PIN_IS_LOW	= 0,	/**< pin_get_val */
	PIN_IS_HIGH	= 1,	/**< pin_get_val */
};

/** @return pin_t, where pin is a enum en_pin_number.
 * @note This function can return invalid pins, to make sure validate it
 * before using. */
struct pin_t pin_init (u08 port, u08 pin);

/** @return 1 ok, 0 for error. */
u08 pin_isvalid (struct pin_t p);

/** @name value
 * @{ */
/** @brief PIN must be output, or you'll get an undefined behaviour */
void pin_set_high (struct pin_t p);

/** @brief PIN must be output, or you'll get an undefined behaviour */
void pin_set_low (struct pin_t p);

/** @brief PIN must be output, or you'll get an undefined behaviour */
void pin_set_val (struct pin_t p, u08 v);

/** @brief PIN must be input, or you'll get an undefined behaviour
 * @return PIN_HIGH for high, PIN_LOW for low */
u08 pin_get_val (struct pin_t p);
/** @} */

/** @name direction
 * @{ */
/** @brief set it to input. */
void pin_set_in (struct pin_t p);

/** @brief set it to output. */
void pin_set_out (struct pin_t p);

/** @brief set it to in if (v) or out if not. */
void pin_set_dir (struct pin_t p, u08 v);

/** @return 1 for in, 0 for out. */
u08 pin_get_dir (struct pin_t p);
/** @} */

/** @name pullup
 * @{ */
void pin_set_pullup (struct pin_t p);
void pin_set_pullupoff (struct pin_t p);
void pin_set_pullup_val (struct pin_t p, u08 v);
u08 pin_get_pullup (struct pin_t p);
/** @} */

#endif /* __PIN_H_ */
/** @} */ /* defgroup pin */
