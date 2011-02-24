/** @file 
 * @defgroup pin pin
 * @{
 * @example pinex.c */

#ifndef EHAL_PIN_H
#define EHAL_PIN_H

#ifdef EHAL_GLOBAL
#include "ehal_global.h"
#endif

#include <stdbool.h>
#include <stdint.h>
#include "tinytypes.h"
#include "port.h"

struct pin_t {
	void *port;
	u08 pin;
};

/** @return pin_t, where pin is a enum en_pin_number.
 * @note This function can return invalid pins, to make sure validate it
 * before using. */
struct pin_t pin_init (int port, int pin);

/** set the pin to high state. */
void pin_sethigh (struct pin_t p);

/** set the pin to low state. */
void pin_setlow (struct pin_t p);

/** true if pin is high */
bool pin_ishigh (struct pin_t p);

/** true if pin is low */
bool pin_islow (struct pin_t p);

/** set it to input. */
void pin_setin (struct pin_t p);

/** set it to output. */
void pin_setout (struct pin_t p);

/** @return 1 for in, 0 for out. */
bool pin_isin (struct pin_t p);

/** @return 0 for in, 1 for out. */
bool pin_isout (struct pin_t p);


/* :TODO: These names are terrible... */
void pin_setpullup (struct pin_t p);
void pin_clrpullup (struct pin_t p);
bool pin_getpullup (struct pin_t p);

void pin_setpulldn (struct pin_t p);
void pin_clrpulldn (struct pin_t p);
bool pin_getpullup (struct pin_t p);

#endif /* __PIN_H_ */
/** @} */ /* defgroup pin */
