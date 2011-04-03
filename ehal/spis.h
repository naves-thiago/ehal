/**
 * @file
 * @defgroup spis spis
 * @{
 * @example spis.c
 */

#ifndef EHAL_SPIS_H
#define EHAL_SPIS_H

#ifdef EHAL_GLOBAL
#include "ehal_global.h"
#endif

#include <stdio.h>
#include "spis_specific.h"
#include "tinytypes.h"

#ifndef NSPIS
/** Maximum number of spiss. */
#define NSPIS <defined in spis_specific.h>
#error Undefined number of spiss
#endif

/** Initializes and returns a hdl from an id.
 * Puts the spis into the default state.
 *
 * @param id - index of spis from 0 to @ref NSPIS.
 * @return spis handler.
 ******************************************************************************/
void	*spis_init (int id);

/** write an array into the spis.
 * @param id - index of spis from 0 to @ref NSPIS.
 * @param buff - Buffer with data.
 * @param sz - number of bytes to write.
 * @return Actual number of written bytes.
 ******************************************************************************/
int	spis_write (void *id, char *buff, int sz);

/** Reads sz bytes into ptr.
 * @param id - index of spis from 0 to @ref NSPIS.
 * @param buff - Buffer to write data.
 * @param sz - number of bytes to read.
 * @return Number successfuly readed.
 ******************************************************************************/
int	spis_read (void *id, char *buff, int sz);

/** Same as @ref spis_write but non blocking.
 * @param id - index of spis from 0 to @ref NSPIS.
 * @param buff - Buffer with data.
 * @param sz - number of bytes to write.
 * @return Actual number of written bytes.
 ******************************************************************************/
int	spis_writenb (void *id, char *buff, int sz);

/** Same as @ref spis_read but non blocking.
 * @param id - index of spis from 0 to @ref NSPIS.
 * @param buff - Buffer to write data.
 * @param sz - number of bytes to read.
 * @return Number successfuly readed.
 ******************************************************************************/
int	spis_read (void *id, char *buff, int sz);

#endif /* EHAL_SPIS_H */

/** @} */
