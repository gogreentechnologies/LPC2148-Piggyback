#include<lpc214x.h>
#include "lcd.h"
 
int main()
{
	lcd_init();
	gotoloc(1,1);
	LCD_WriteString("  Emtron Tech  ");
	gotoloc(2,1);
	LCD_WriteString("     Mumbai    ");


}

