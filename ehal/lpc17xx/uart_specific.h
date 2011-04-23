#ifndef UART_SPECIFIC_H
#define UART_SPECIFIC_H

#define NUART	3

#define reg_mask(p, m, v) do { p = ((p) & ~(m)) | ((v) & (m)); } while(0)

int uart_set_baudrate(unsigned int baudrate);
void uart_select(int id);

#endif
