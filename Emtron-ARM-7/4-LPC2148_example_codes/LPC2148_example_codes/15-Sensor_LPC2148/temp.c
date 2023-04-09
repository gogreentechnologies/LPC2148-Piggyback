#include <lpc214x.h>
#include "lcd.h"
#include "stdlib.h"
#include "stdio.h"
int adc_value;
int ADC0;
int main()
{
	unsigned char CHANNEL_1;
	char buffer[16];
	lcd_init();
	gotoloc(1,1);
	LCD_WriteString("  Emtron Tech  ");
	gotoloc(2,1);
	LCD_WriteString("     Mumbai    ");
	soft_delay_ms(200);
	gotoloc(1,1);
LCD_WriteString("TEMPERATURE: ");

	adc_value = (adc_read(ADC0, CHANNEL_1)-70)/10;
     
	// To convert adc value to string
    // sprintf(adc_value, 20, buffer, sizeof(buffer));
	 sprintf((char *)buffer, "ADC VALUE:%d ", adc_value);
     gotoloc(1, 1);
     //LCD_WriteString(buffer);

}

