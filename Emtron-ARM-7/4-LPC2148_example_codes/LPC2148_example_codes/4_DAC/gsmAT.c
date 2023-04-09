#include<lpc214x.h>
#include "lcd.h"
#include <math.h>


int main()
{
	unsigned char wav[100];
	unsigned char ucTemp,buf[16],j=0;
	PINSEL1=(1<<19);						 // DAC Function Select A.OUT
	lcd_init();
	gotoloc(1,1);
	LCD_WriteString("  Emtron Tech  ");
	gotoloc(2,1);
	LCD_WriteString("   DAC TEST    ");
	soft_delay_ms(3000);
	lcd_clear();

	for(ucTemp=0;ucTemp<100;ucTemp++)
		{
		 	wav[ucTemp]=100*sin(((float)ucTemp/100)*3.1415);			// Half Wave
			wav[ucTemp]=(wav[ucTemp]*wav[ucTemp])/100;
																	   // Full Wave
		}
		gotoloc(1,1);
	  	LCD_WriteString("  DAC OUTPUT  ");

 while(j<1000)
	{	
		 for(ucTemp=0;ucTemp<100;ucTemp++)
		{
		 	DACR=wav[ucTemp]<<8;									 // 	shift the data to D6 to D15 of DACR and increase the amplitude by 4  
			//sprintf((char *)buf,"DAC VALUE:%d",wav[ucTemp]);
			//gotoloc(2,1);
			//LCD_WriteString((char *)buf);
			//delay(1000);
			
		}
		j++;
	}



}

