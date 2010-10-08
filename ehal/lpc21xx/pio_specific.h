#ifndef __PIO_SPECIFIC_H
#define __PIO_SPECIFIC_H

#include "types.h"

typedef struct pio_pin_t {
	u32 port:16;
	u32 pin:16;
} pio_pin;

typedef u32 pio_t;

#endif
