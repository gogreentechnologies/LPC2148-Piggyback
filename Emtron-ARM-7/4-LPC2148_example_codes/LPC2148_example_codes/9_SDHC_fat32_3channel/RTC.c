#include <stdio.h>                /* prototype declarations for I/O functions */
#include <LPC214x.H>              /* LPC21xx definitions  */

/******** Template for interrupt routine *******
unsigned char cnt;
__irq void rtc_ir()
{
//	IO0PIN=(~IO0PIN)&0x80000000;
	
  //T0IR = 1;                                   // Clear interrupt flag
  	ILR=1;
  	VICVectAddr = 0;                            // Acknowledge Interrupt
	cnt++;
	if(cnt%2)
		IO0SET=0x80000000;
	else
		IO0CLR=0x80000000;
}
***************************************************/

void rtc_init() 
{
	HOUR=0;
  	MIN=0;
  	SEC=0;
	DOM=1;
	MONTH=1;
	YEAR=2012;
  	AMR=0x0f;
  	CCR=(1<<CLKEN)|(1<<CLKSRC);
  	ILR=3;
}
