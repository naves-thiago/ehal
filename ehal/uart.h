/** @file
 * @defgroup uart uart
 * @{
 * @example uartex.c */

#ifndef EHAL_UART
#define EHAL_UART

#include "types.h"
#include "queue.h"

/** Possible baud rates. */
enum uart_baud_rate {
	B0,	B50,	B75,	B110,	B134,	B150,	B300,	B600,
	B1200,	B1800,	B2400,	B4800,	B9600,	B19200,	B38400,	B115200,
};

/** Must be called before the other functions of the module.
 * Set the uart to 9600 - 8N1.
 * @param id - uart number. (0..n) */
void uart_init (u08 id);

/** Return true if id is valid. */
u08 uart_isvalid (u08 id);

void uart_settxqueue (u08 id, struct queue *q);
struct queue *uart_gettxqueue (u08 id);

void uart_setrxqueue (u08 id, struct queue *q);
struct queue *uart_getrxqueue (u08 id);

void uart_onrx_cb (u08 id, void (*nrx_cb)(void), u08 n);
void uart_oncntrl_cb (u08 id, void (*nrx_cb)(void));

/** Set the baud rate as close as possible to baud.
 * @param baud - a @ref uart_baud_rate constant.
 * @param fcpu - the frequency that the cpu is currently running. */
void uart_setbaud (u08 id, u08 baud);

/** Check if uart_setbaud got the right value.
 * @return baud the mcu is actually using. */
u32 uart_getbaud (u08 id);

/** Set the number of bits of the uart "word", default is 8.
 * @note This might not exist in all platforms. */
void uart_setnbits (u08 id, u08 n);

/** Get the number of bits the uart is using. */
u08 uart_getnbits (u08 id);

/** Set the number of stop bits. */
void uart_setstopbits(u08 id, u08 stopbits);

/** get the number of stop bits. */
u08 uart_getstopbits (u08 id);

/** Issue a transmit from all bytes in the tx queue */
void uart_transmit (u08 id);

/** true when queue is empty and no tx transfer. */
u08 uart_txready (u08 id);
#endif

/** @} */ /* defgroup uart */
