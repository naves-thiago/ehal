#ifndef EHAL_I2C_H
#define EHAL_I2C_H

#ifndef EHAL_GLOBAL
#include "ehal_global.h"
#endif

#include "tinytipes.h"

void	i2cm_init (void *id);
void	i2cm_setfreq (void *, int freq);
void	i2cm_setslave (void *, int slave);
int	i2cm_write (void *id, char *buff, int sz);
int	i2cm_read (void *id, char *buff, int sz);

#endif
