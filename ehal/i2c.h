#ifndef EHAL_I2C_H
#define EHAL_I2C_H

#ifndef EHAL_GLOBAL
#include "ehal_global.h"
#endif

#include "tinytipes.h"

void	i2c_init (void *id);
void	i2c_setfreq (void *, u08 freq);
int	i2c_write (void *id, u08 *buf, u08 sz);
int	i2c_read (void *id, u08 *buf, u08 sz);

#endif
