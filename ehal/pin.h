#ifndef __PIN_H_
#define __PIN_H_

#include "types.h"
#include "pin_specific.h"

/* Pin Interface */
extern pin_t	pin_make	(u08 port, u08 pin);
/* value */
extern void	pin_high	(pin_t p);
extern void	pin_low		(pin_t p);
extern u08	pin_getvalue	(pin_t p);
/* dir */
extern void	pin_in		(pin_t p);
extern void	pin_out		(pin_t p);
extern u08	pin_getdir	(pin_t p);
/* pullup */
extern void	pin_pullup	(pin_t p);
extern void	pin_nopullup	(pin_t p);
extern u08	pin_getpullup	(pin_t p);

extern u08	pin_validate	(pin_t p);

#endif
