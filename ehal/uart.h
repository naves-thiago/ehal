#ifndef __UART_H_
#define __UART_H_

#include "types.h"
#include "queue.h"

enum uart_baud_rate {
	B0,	B50,	B75,	B110,	B134,	B150,	B300,	B600,
	B1200,	B1800,	B2400,	B4800,	B9600,	B19200,	B38400,	B115200,
};

/* callback funtion */
typedef void (*uart_fn)(struct queue *q);

void	uart_init	(u08 id);
u08	uart_validate	(u08 id);
void	uart_set_baud	(u08 id, u08 baud, u32 fcpu);
u32	uart_get_baud	(u08 id, u32 fcpu);
u08	uart_cfg_bits	(u08 id, u08); /* default of init is 8. */

/* return a valid queue or NULL, also note that there will be one tx and one
 * rx per uart. so uart_validade also validate the number of queue pairs */
struct queue *uart_gettx	(u08 id);
struct queue *uart_getrx	(u08 id);

/* sends the data in the tx buffer. */
void	uart_send		(u08 id);

/* "events" for uart. For disabling, set as NULL. */
void	uart_set_on_txempty	(u08 id, uart_fn callback);
void	uart_set_on_rxfull	(u08 id, uart_fn callback);

#endif
