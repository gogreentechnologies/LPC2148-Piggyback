#include <stdio.h>                /* prototype declarations for I/O functions */
#include <LPC214x.H>              /* LPC21xx definitions  */



void rtc_init(int hour, int minute) 
{

PCONP |= 0x200;
CCR=0x2; /* Reset the clock */
ILR=0x3; /* Clear the Interrupt Location Register */
CIIR=0x01;	  /* Enable seconds Increment Interruptr */

HOUR=hour;
SEC=0x0;
MIN=minute;
PREINT = 0x01C8;
PREFRAC = 0x61C0;
}
