#include "uart.h"
#include "LPC_17xx.h"
#include "core_cm3.h"
#include "uart_specific.h"

// Accepted Error baud rate value (in percent unit)
#define UART_ACCEPTED_BAUDRATE_ERROR    3

#define DLAB_ENABLE                     (1 << 7)

int uart_set_baudrate(unsigned int baudrate)
{
    unsigned int uClk = SystemCoreClock / 4;
    unsigned int calcBaudrate = 0;
    unsigned int temp = 0;

    unsigned int mulFracDiv, dividerAddFracDiv;
    unsigned int divider = 0;
    unsigned int mulFracDivOptimal = 1;
    unsigned int dividerAddOptimal = 0;
    unsigned int dividerOptimal = 0;

    unsigned int relativeError = 0;
    unsigned int relativeOptimalError = 100000;

    uClk = uClk >> 4; /* div by 16 */

    /*
     *  The formula is :
     * BaudRate= uClk * (mulFracDiv/(mulFracDiv+dividerAddFracDiv) / (16 * DLL)
     */

    /*
     * The value of mulFracDiv and dividerAddFracDiv should comply to the following expressions:
     * 0 < mulFracDiv <= 15, 0 <= dividerAddFracDiv <= 15
     */
    for (mulFracDiv = 1; mulFracDiv <= 15; mulFracDiv++) {
        for (dividerAddFracDiv = 0; dividerAddFracDiv <= 15; dividerAddFracDiv++) {
            temp = (mulFracDiv * uClk) / (mulFracDiv + dividerAddFracDiv);

            divider = temp / baudrate;
            if ((temp % baudrate) > (baudrate / 2))
                divider++;

            if (divider > 2 && divider < 65536) {
                calcBaudrate = temp / divider;

                if (calcBaudrate <= baudrate) {
                    relativeError = baudrate - calcBaudrate;
                } else {
                    relativeError = calcBaudrate - baudrate;
                }

                if (relativeError < relativeOptimalError) {
                    mulFracDivOptimal = mulFracDiv;
                    dividerAddOptimal = dividerAddFracDiv;
                    dividerOptimal = divider;
                    relativeOptimalError = relativeError;
                    if (relativeError == 0)
                        break;
                }
            }
        }

        if (relativeError == 0)
            break;
    }


    LPC_UART0->LCR |= DLAB_ENABLE;
    LPC_UART0->DLM = (unsigned char) ((dividerOptimal >> 8) & 0xFF);
    LPC_UART0->DLL = (unsigned char) dividerOptimal;
    LPC_UART0->LCR &= ~DLAB_ENABLE;

    LPC_UART0->FDR = ((mulFracDivOptimal << 4) & 0xF0) | (dividerAddOptimal & 0x0F);


    return baudrate;
}

int uart_getbaud(int id)
{
  //                                     PCLK
  // Baudrate = ------------------------------------------------------
  //              16 x (256 x DLM + DLL) x (1+ DivAddVal / MulVal)


  int MulVal, DivAddVal, DLL, DLM, PCLK, ClkDiv;

  switch (id)
  {
    case 0:
      ClkDiv = (PCLKSEL0 & (3<<6)) >> 6;
      DLL = LPC_UART0->DLL;
      DLM = LPC_UART0->DLM;
      break;

    case 1:
      ClkDiv = (PCLKSEL0 & (3<<8)) >> 8;
      DLL = LPC_UART1->DLL;
      DLM = LPC_UART1->DLM;
      break;

    case 2:
      ClkDiv = (PCLKSEL1 & (3<<16)) >> 16;
      DLL = LPC_UART2->DLL;
      DLM = LPC_UART2->DLM;
      break;

    case 3:
      ClkDiv = (PCLKSEL1 & (3<<18)) >> 18;
      DLL = LPC_UART3->DLL;
      DLM = LPC_UART3->DLM;
      break;
  }


  MulVal = ( DLL & 0xF0 ) >> 4;
  DivAddVal = ( DLL & 0x0F );

  switch (ClkDiv)
  {
    case 0:
      PCLK = SystemCoreClock / 4;
      break;

    case 1:
      PCLK = SystemCoreClock;
      break;

    case 2:
      PCLK = SystemCoreClock / 2;
      break;

    case 3:
      PCLK = SystemCoreClock / 8;
      break;
  }

  return PCLK / (16 * (256 * DLM * DLL) * (1+ DivAddVal / MulVal)); 
}
