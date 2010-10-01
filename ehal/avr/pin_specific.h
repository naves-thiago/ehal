#ifndef __PIN_H_
#define __PIN_H_

#include "types.h"

struct pin_t {
	u08 port:4;
	u08 pin:4;
};

#define pin_shift(x)	P ## x = (1<<x)

enum pin_name {
	pin_shift(0),
	pin_shift(1),
	pin_shift(2),
	pin_shift(3),
	pin_shift(4),
	pin_shift(5),
	pin_shift(6),
	pin_shift(7),
};

#endif
