#ifndef EHAL_I2C_H
#define EHAL_I2C_H

#ifndef EHAL_GLOBAL
#include "ehal_global.h"
#endif

#include "tinytipes.h"

void	i2cm_init (void *id);
void	i2cm_setfreq (void *, u08 freq);
void	i2cm_setslave (void *, u08 slave);
int	i2cm_write (void *id, u08 *buf, u08 sz);
int	i2cm_read (void *id, u08 *buf, u08 sz);

#endif
