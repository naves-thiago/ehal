/** @file
 * @defgroup uart uart
 * @{
 * @example uartex.c */

#ifndef __UART_H_
#define __UART_H_

#include "types.h"
#include "queue.h"

/** @brief possible baud rates. */
enum uart_baud_rate {
	B0,	B50,	B75,	B110,	B134,	B150,	B300,	B600,
	B1200,	B1800,	B2400,	B4800,	B9600,	B19200,	B38400,	B115200,
};

/** Must be called before the other functions of the module.
 * Set the uart to 9600 - 8N1.
 * @arg id - uart number. (0..n) */
void	uart_init	(u08 id);

/** Return true if id is valid. */
u08	uart_isvalid	(u08 id);

/** Set the baud rate as close as possible to baud.
 * @arg baud - a @ref uart_baud_rate constant.
 * @arg fcpu - the frequency that the cpu is currently running. */
void	uart_setbaud	(u08 id, u08 baud);

/** Check if set_baud got the right value.
 * @return baud the mcu is actually using. */
u32	uart_getbaud	(u08 id);

/** Set the number of bits of the uart "word", default is 8.
 * @note This might not exist in all platforms. */
void	uart_setnbits	(u08 id, u08 n);

/** Get the number of bits the uart is using. */
u08	uart_getnbits	(u08 id);

/** Set the number of stop bits. */
void	uart_setstopbits(u08 id, u08 stopbits);

/** get the number of stop bits. */
u08	uart_getstopbits(u08 id);

/** Send sz bytes of buff to the uart from buff, non blocking.
 * @arg buff - ptr to array.
 * @arg sz - size of buff
 * @return the number of successfully enqueued. */
u08	uart_write	(u08 id, void *buff, u08 sz);

/** Receive sz bytes from the uart, into buff.
 * @arg buff - ptr to array.
 * @arg sz - size of buff */
u08	uart_read	(u08 id, void *buff, u08 sz);

/** Initialize the TX buffer. */
void	uart_inittx	(u08 id, u08 *buff, u08 sz);

u08	uart_txready	(u08 id);
#endif

/** @} */ /* defgroup uart */
