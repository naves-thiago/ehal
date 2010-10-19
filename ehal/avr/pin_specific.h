#ifndef __PIN_SPECIFIC_H_
#define __PIN_SPECIFIC_H_

#include "types.h"

struct pin_t {
	u08 port;
	u08 pin;
};

#define PIN_SIZE 8

#define ENUM_EPIN(_p) P ## _p = (1 << _p)
enum en_pin_number {
	ENUM_EPIN(0),  ENUM_EPIN(1),  ENUM_EPIN(2),  ENUM_EPIN(3),
	ENUM_EPIN(4), ENUM_EPIN(5),  ENUM_EPIN(6), ENUM_EPIN(7),
};

#endif
