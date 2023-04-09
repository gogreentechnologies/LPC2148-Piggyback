#include <lpc214x.h>
#include "lcd.h"
#include "stdlib.h"
#include "stdio.h"
#include "adc.h"

unsigned short adc_value = 0;
void process_adc(void)

{
	//unsigned short adc_value = 0;
  	unsigned char buf[16] = {0};
	  LCD_Cmd(0x01);
		soft_delay_ms(10);
	  gotoloc(1,1);
  	adc_value = adc_read(ADC0, CHANNEL_1);											// Read adc value 
}




int main()
{
	//unsigned char CHANNEL_1;
	unsigned char buffer[16];
	unsigned char buf[16] = {0};
	lcd_init();
	init_adc0();
	gotoloc(1,1);
	LCD_WriteString("  Emtron Tech  ");
	gotoloc(2,1);
	LCD_WriteString("     Mumbai    ");
	soft_delay_ms(200);

	

	
	while(1)     
	{ 
		/*
// Optocoupler %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		
     process_adc();       														// Read ADC value and display it on first line of LCD
	   soft_delay_ms(500);	
			
			  if ((adc_value) >= 500)
       { 
				 //adc_value = adc_read(ADC0, CHANNEL_1);
				 LCD_Cmd(0x01);
				 soft_delay_ms(10);
				 gotoloc(1,1);
			   LCD_WriteString("OPTO:");
				 gotoloc(2, 1);
				 LCD_WriteString("OBJECT PRESENT");					 
			 }
      else
			{
				LCD_Cmd(0x01);
				soft_delay_ms(10);
				gotoloc(1, 1);
			  LCD_WriteString("OPTO:");
				gotoloc(2, 1);	
				LCD_WriteString("   NO OBJECT  ");
        }
			  soft_delay_ms(200);						
			*/
	
	/*
// Temperature %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

		 LCD_Cmd(0x01);
		 soft_delay_ms(200);
		 gotoloc(1,1);
		 LCD_WriteString(" TEMPERATURE: ");
		 adc_value = (adc_read(ADC0, CHANNEL_1)-70)/10;
		 sprintf((char *)buf,"%d ", adc_value); 														// To convert adc value to string
     LCD_WriteString((char *)buf);
		 soft_delay_ms(500);
	*/
	
		/*
// Distance %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
			LCD_Cmd(0x01);
			soft_delay_ms(200);
			gotoloc(1,1);
      LCD_WriteString(" DISTANCE (cm): ");                                                 
      adc_value = 27- (adc_read(ADC0,CHANNEL_1))/100; 
			sprintf((char *)buf,"%d ", adc_value);
      //int_to_str(adc_value, 5, buffer, sizeof(buffer));
      gotoloc(2, 1);
      LCD_WriteString((char *)buf);
			soft_delay_ms(500);
	*/
			
/*
// LDR %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

			LCD_Cmd(0x01);
			soft_delay_ms(200);
			gotoloc(1, 1);
			LCD_WriteString("Darkness: ");

			adc_value = (adc_read(ADC0,CHANNEL_1));
      //printf(adc_value, 5, buffer, sizeof(buffer));
      sprintf((char *)buf,"%d ", adc_value);													// To convert adc value to string
			gotoloc(2, 1);
      LCD_WriteString((char *)buf);
      soft_delay_ms(300);
*/


// MAGNETIC  SENSOR  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     
		 if ((adc_read(ADC0,CHANNEL_1) & 0x0200) !=0x0000)
		{
				LCD_Cmd(0x01); 
			  LCD_WriteString("      MAGNETIC:      ");
				soft_delay_ms(1000);
				gotoloc(1, 1);	
				LCD_WriteString(" M: NO DANGER ");
	      soft_delay_ms(1000);	
		}
		else
		{
		  	LCD_Cmd(0x01);
			  LCD_WriteString("        MAGNETIC:     ");
				soft_delay_ms(1000);
				gotoloc(1, 1);	
				LCD_WriteString(" M: DANGER ");			
        soft_delay_ms(1000);		
		}

}
}

