/** \@file
 * \@defgroup hd44780 HD44780 display driver
 * \@{
*/

#include <stdio.h>

#ifndef HD44780_H
#define HD44780_H

#define HD44780_WIDTH		0x10
#define HD44780_HEIGHT		0x02
#define HD44780_LINE0		0x00
#define HD44780_LINE1		0x40


/**************************************************************************
			Interface
**************************************************************************/
void		hd44780_init (void);
void		hd44780_write_data (unsigned char c);
void		hd44780_write_cmd (unsigned char c);
unsigned char	hd44780_read_data (void);
unsigned char	hd44780_read_status (void);

void		hd44780_write_buff (void);
void		hd44780_write_buff_char (char);
/**************************************************************************
			Display Commands
**************************************************************************/

#define hd44780_clear()		hd44780_write_cmd (0x01)
#define hd44780_home()		hd44780_write_cmd (0x02)

/** @param id - cursor increment/decrement direction.
 * @param s - cursor seems still & display shifts. */
#define hd44780_mode(id, s)	hd44780_write_cmd\
	(0x04			\
	| ((id) ? 0x02 : 0)	\
	| ((s) ? 0x01 : 0))

/** @param d - display on/!off
 * @param c - cursor on/!off
 * @param b - cursonr blinking on/!off */
#define hd44780_control(d, c, b) hd44780_write_cmd\
	(0x08			\
	| ((d) ? 0x04 : 0)	\
	| ((c) ? 0x02 : 0)	\
	| ((b) ? 0x01 : 0))

/** @param sc - shift display without changing its content.
 * @param rl - */
#define hd44780_shift(s, r)	hd44780_write_cmd\
	(0x10			\
	| ((sc) ? 0x08 : 0)	\
	| ((rl) ? 0x04 : 0))

/** @param dl - data lenth.
 * @param n - number of lines.
 * @param f - character font. */
#define hd44780_fnset(dl, n, f)	hd44780_write_cmd\
	(0x20			\
	| ((dl) ? 0x10 : 0)	\
	| ((n) ? 0x08 : 0)	\
	| ((f) ? 0x04 : 0))

#define hd44780_cgram_adr(adr)	hd44780_write_cmd\
	(0x40			\
	| ((adr) & 0x3F)

#define hd44780_ddram_adr(adr)	hd44780_write_cmd\
	(0x80			\
	| ((adr) & 0x7F))

#endif /* __HD44780_H_ */
/** @} */ /*  @defgroup hd44780 */
