#ifndef PORT_SPECIFIC_H
#define PORT_SPECIFIC_H

#include "tinytypes.h"

typedef u08 port_t;

#if defined (ehal_msp430x2012)
#define NPORT 2
#elif defined (ehal_msp430x2013)
#define NPORT 2
#endif

#endif
