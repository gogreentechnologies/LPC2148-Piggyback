//RTC checking

#include <LPC214x.H>                       /* LPC214x definitions */
#include <stdio.h>
#include "rtc.h"
#include "lcd.h"



int main (void) 
{


	char buf[128]	;

 	lcd_init();
    lcd_clear();
    gotoloc(1,1);
	LCD_WriteString("  RTC TEST  ");
	soft_delay_ms(3000);
 
    HOUR=0;
    MIN=0;
    SEC=0;
	 
	rtc_init(0,0);
	CCR=0x01; /* Clock Control Register  start RTC */
	while(1)
	{
	 gotoloc(2,1);
     sprintf((char *)buf,"%02d : %02d : %02d",HOUR,MIN,SEC);
	 LCD_WriteString((char *)buf);


	}
}