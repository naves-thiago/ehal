#include "uart.h"
#include "LPC_17xx.h"
#include "core_cm3.h"
#include "uart_specific.h"

#define CHAR_5_BIT                      (0 << 0)
#define CHAR_6_BIT                      (1 << 0)
#define CHAR_7_BIT                      (2 << 0)
#define CHAR_8_BIT                      (3 << 0)

#define STOP_1_BIT                      (0 << 2)
#define STOP_2_BIT                      (1 << 2)

#define PARITY_NONE                     (0 << 3)
#define PARITY_ENABLE                   (1 << 3)

#define PARITY_ODD                      (0 << 4)
#define PARITY_EVEN                     (1 << 4)
#define PARITY_FORCED_1                 (2 << 4)
#define PARITY_FORCED_0                 (3 << 4)

#define FIFO_ENABLE                     (1 << 0)
#define RBR_IRQ_ENABLE                  (1 << 0)
#define THRE_IRQ_ENABLE                 (1 << 1)

#define RDA_INTERRUPT                   (2 << 1)
#define CTI_INTERRUPT                   (6 << 1)

// Masks
#define M_CHAR_BIT                      (3 << 0)
#define M_STOP_BIT                      (1 << 2)
#define M_PARITY_EN                     (1 << 3)
#define M_PARITY_TYPE                   (3 << 4)
#define M_FIFO_EN                       (1 << 0)

#define M_RDA_INTERRUPT                 (2 << 1)
#define M_CTI_INTERRUPT                 (6 << 1)




static __IO uint8_t * UART_LCR[] = { 
  &LPC_UART0->LCR,
  &LPC_UART1->LCR,
  &LPC_UART2->LCR,
  &LPC_UART3->LCR
};

static __IO uint32_t * UART_IER[] = { 
  &LPC_UART0->IER,
  &LPC_UART1->IER,
  &LPC_UART2->IER,
  &LPC_UART3->IER
};

static IRQn_Type UART_IRQn[] = {
  UART0_IRQn,
  UART1_IRQn,
  UART2_IRQn,
  UART3_IRQn
};

// Selects the UART function on the UART[id] pins
void uart_select(int id)
{
    switch (id)
    { 
      case 0:
        // Change P0.2 and P0.3 mode to TXD0 and RXD0
        reg_mask(LPC_PINCON->PINSEL0, 31<<4, 0x28<<4);
        break;
      case 1:
        // Change P0.15 mode to TXD1
        reg_mask(LPC_PINCON->PINSEL0, 3<<30, 1<<30);
        // Change P0.16 mode to RXD1
        reg_mask(LPC_PINCON->PINSEL1, 3, 1);
        break;
      case 2:
        // Change P0.10 and P0.11 mode to TXD2 and RXD2
        reg_mask(LPC_PINCON->PINSEL0, 31<<20, 0x28<<20);
        break;
      case 3:
        // Change P0.0 and P0.1 mode to TXD3 and RXD3
        reg_mask(LPC_PINCON->PINSEL0, 31, 0x28);
        break;
    }
}

void *uart_init(int id)
{
    // Select uart pin funcion
    uart_select(id);

    // Set 8N1 mode
    reg_mask(*UART_LCR[id], M_CHAR_BIT | M_STOP_BIT | M_PATITY_TYPE, CHAR_8_BIT | STOP_1_BIT | PARITY_NONE);

    // Set the baud rate
    uart_set_baudrate(baudrate);

    // Enable TX and RX FIFO
    // LPC_UART0->FCR |= FIFO_ENABLE;

    // Set FIFO to trigger when at least 14 characters available
    // LPC_UART0->FCR |= (3 << 6);

    // Enable UART RX interrupt (for LPC17xx UART)
    (*UART_IER[id]) = RBR_IRQ_ENABLE;

    // Enable the UART interrupt (for Cortex-CM3 NVIC)
    NVIC_EnableIRQ(UART_IRQn[id]);
  
}


