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

/** @brief Must be called before the other functions of the module.
 * @arg id - uart number. (0..n) */
void	uart_init	(u08 id);

/** @brief Return true if id is valid. */
u08	uart_is_valid	(u08 id);

/** @name config
 * @{ */
/** @brief Set the baud rate as close as possible to baud.
 * @arg baud - a @ref uart_baud_rate constant.
 * @arg fcpu - the frequency that the cpu is currently running. */
void	uart_set_baud	(u08 id, u08 baud, u32 fcpu);

/** @brief Check if set_baud got the right value.
 * @return baud the mcu is actually using. */
u32	uart_get_baud	(u08 id, u32 fcpu);

/** @brief Set the number of bits of the uart "word", default is 8.
 * @note This might not exist in all platforms. */
void	uart_set_nbits	(u08 id, u08 n); /* default of init is 8. */

/** @brief get the previous value. */
u08	uart_get_nbits	(u08 id);
/** @} */

/** @name send/recv
 * @{ */
/** @brief Send sz bytes of buff to the uart from buff.
 * @arg buff - ptr to array.
 * @arg sz - size of buff */
void	uart_send	(u08 id, u08 *buff, u08 sz);
/** @brief Receive sz bytes from the uart, into buff.
 * @arg buff - ptr to array.
 * @arg sz - size of buff */
void	uart_recv	(u08 id, u08 *buff, u08 sz);

/** @brief set a callback for when tx is completed.
 * @arg txcb - a funtion that will be called when done. */
void	uart_set_txdone_cb	(u08 id, void (*txcb)(u08 *buff, u08 sz));

/** @brief set a callback for when rx is completed.
 * @arg rxcb - a funtion that will be called when done. */
void	uart_set_rxdone_cb	(u08 id, void (*rxcb)(u08 *buff, u08 sz));

/** @brief set a callback for when received char 'c'
 * @arg fccb - a function that will be called when uart get the char 'c'.
 * @arg c - char that defines when to call fccb, common value is '\\n'. */
void	uart_set_foundc_cb	(u08 id,
		void (*fccb)(u08 *buff, u08 sz),
		char c);

/** @brief flag for transmission completed (buffer empty).
 * @return 1 if done, 0 otherwise. */
u08	uart_txdone	(u08 id);
/** @brief flag for receive completed (buffer full).
 * @return 1 if done, 0 otherwise. */
u08	uart_rxdone	(u08 id);
/** @} */

#endif

/** @} */
