/**
 * @file
 * @defgroup uart uart
 * @{
 * @example uartex.c
 */

#ifndef EHAL_UART_H
#define EHAL_UART_H

#ifdef EHAL_GLOBAL
#include "ehal_global.h"
#endif

#include <stdio.h>
#include "uart_specific.h"
#include "tinytypes.h"

#ifndef NUART
/** Maximum number of uarts. */
#define NUART <defined in uart_specific.h>
#error Undefined number of uarts
#endif


/** Possible baud rates. */
enum uart_baud_rate {
	B1200,	B1800,	B2400,	B4800,	B9600,	B19200,	B38400,	B115200,
};

/** Possible parity values */
enum uart_parity {
	PAR_NONE, PAR_EVEN, PAR_ODD,
};

/** Possible stop Bits */
enum uart_stopbits {
	STOP_BITS_1, STOP_BITS_1_5, STOP_BITS_2,
};

#ifndef NUART
/** Number of uarts present on platform */
#define NUART <defined in uart_specific.h>
#error undefined NUART
#endif

/** Initializes TX, RX and returns a hdl from an id.
 * Puts the uart into the default state: 9600 8N1
 *
 * @param id - index of uart from 0 to @ref NUART.
 * @return uart handler.
 * ****************************************************************************/
void	*uart_init (int id);

/** Set to one of the @ref uart_baud_rate values.
 * @param u - index of uart from 0 to @ref NUART.
 * @param baud - one of @ref uart_baud_rate.
 * ****************************************************************************/
void	uart_setbaud (void *u, enum uart_baud_rate baud);

/** Get the numerical with error value.
 * @param u - index of uart from 0 to @ref NUART.
 * @return The baud rate in bps.
 * @note This value might be diferent from the one passed on setbaud, problems
 * might be related to a crystal not multiple of baud.
 * ****************************************************************************/
u32	uart_getbaud (void *u);

/** Set number of bits for tx and rx. The default is 8.
 * @param u - index of uart from 0 to @ref NUART.
 * @param n - number of bits, normally this value goes from 4 to 8.
 * Check if it worked with @ref uart_getnbits.
 * ****************************************************************************/
void	uart_setnbits (void *u, u08 n);

/** Gets the number of bits of the transmission.
 * @param u - index of uart from 0 to @ref NUART.
 * @return number of bits.
 * ****************************************************************************/
u08	uart_getnbits (void *u);

/** Set the number of stop bits.
 * @param u - index of uart from 0 to @ref NUART.
 * @param stopbits - 1, 1.5 or 2. Defaults to 1.
 * ****************************************************************************/
void	uart_setstopbits(void *u, enum uart_stopbits stopbits);

/** Get the number of stop bits.
 * @param u - index of uart from 0 to @ref NUART.
 * @return 1, 1.5 or 2.
 * ****************************************************************************/
enum uart_stopbits uart_getstopbits (void *u);

/** Set parity.
 * @param u - index of uart from 0 to @ref NUART.
 * @param par - none, even or odd.
 * ****************************************************************************/
void	uart_setparity (void *u, enum uart_parity par);

/** Get parity.
 * @param u - index of uart from 0 to @ref NUART.
 * @return none, even or odd.
 * ****************************************************************************/
enum uart_parity uart_getparity (void *u);

/** write an array into the uart.
 * @param u - index of uart from 0 to @ref NUART.
 * @param ptr - Pointer with data.
 * @param sz - number of bytes from ptr to write.
 * @return Actual number of written bytes.
 * ****************************************************************************/
int	uart_write (void *u, const char *ptr, int sz);

/** Same as @ref uart_write but non blocking.
 * @param u - index of uart from 0 to @ref NUART.
 * @param ptr - Pointer with data.
 * @param sz - number of bytes from ptr to write.
 * @return Actual number of written bytes.
 ******************************************************************************/
int	uart_writenb (void *u, const char *ptr, int sz);

/** Reads sz bytes into ptr.
 * @param u - index of uart from 0 to @ref NUART.
 * @param ptr - Buffer to write data.
 * @param sz - number of bytes to read.
 * @return Number successfuly readed.
 ******************************************************************************/
int	uart_read (void *u, char *ptr, int sz);

/** Same as @ref uart_read but non blocking.
 * @param u - index of uart from 0 to @ref NUART.
 * @param ptr - Buffer to write data.
 * @param sz - number of bytes to read.
 * @return Number successfuly readed.
 ******************************************************************************/
int	uart_readnb (void *u, char *ptr, int sz);

#endif

/** @} */
