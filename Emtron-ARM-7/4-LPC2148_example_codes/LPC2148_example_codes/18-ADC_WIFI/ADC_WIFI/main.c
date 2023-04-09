#include<LPC214X.h>
#include "Serial.h"
#include "adc.h"
#include "lcd.h"
#include<String.h>
#include<stdio.h>
#include<stdlib.h>

char api[120];

void generateApi(int adcVal){
	
	sprintf(api,"GET /update?api_key=OB2VNU2SE5UIYYMA&field1=%4d HTTP/1.0\r\nHost:api.thingspeak.com\r\n\r\n",adcVal); //change this api key with your edited api key
}


void flush(char *s){
	
	while(*s){
		*(s++) = '\0';
	}
}

int main(){

	//Initialisation
	lcd_init();
	init_adc0();
	uart1_init();
	uart0_init();
	
	char adc[3];
	
	//Sending AT
	gotoloc(1,1);
	LCD_WriteString("SENDING AT");
	uart1_puts("AT\r\n");
	soft_delay_ms(1000);
	
	//Setting Mode=1
	LCD_Cmd(0x01);
	soft_delay_ms(100);
	gotoloc(1,1);
	LCD_WriteString("MODE=1");
	uart1_puts("AT+CWMODE=1\r\n");
	soft_delay_ms(1000);
	
	//Connecting to AP
	LCD_Cmd(0x01);
	soft_delay_ms(100);
	gotoloc(1,1);
	LCD_WriteString("CONNECTING TO AP");
	uart1_puts("AT+CWJAP=\"abc\",\"11111111\"\r\n"); // put your ssid and password in place of abc and 11111111
	soft_delay_ms(1000);
	soft_delay_ms(500);
	gotoloc(2,1);
	LCD_WriteString("CONNECTED");
	
	//Enabling multiple connections
	LCD_Cmd(0x01);
	soft_delay_ms(100);
	uart1_puts("AT+CIPMUX=1\r\n");
	soft_delay_ms(1000);
	
	
	//variable declaration 
	unsigned short val;
	
	while(1){

		//Starting Connection
		LCD_Cmd(0x01);
		soft_delay_ms(100);
		gotoloc(1,1);
		LCD_WriteString("CONNECTING");
		uart1_puts("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
		soft_delay_ms(3000);
		gotoloc(2,1);
		LCD_WriteString("CONNECTED");

		//Reading ADC value and generating api
		val = adc_read(ADC0,CHANNEL_1);
		sprintf(adc,"%3d",val);
		generateApi(val);
		
		//Send command
		LCD_Cmd(0x01);
		soft_delay_ms(100);
		gotoloc(1,1);
		LCD_WriteString("SENDING API");
		uart1_puts("AT+CIPSEND=86\r\n"); // calculate the number of characters of your edited api key and put it in place of 86 
		soft_delay_ms(300);
		
		//Sending API
		uart1_puts(api);
		soft_delay_ms(3000);
		LCD_Cmd(0x01);
		soft_delay_ms(100);
		gotoloc(1,1);
		LCD_WriteString("SENT");
		gotoloc(2,1);
		LCD_WriteString(adc);
		flush(api);
		
		//totoal 15 sec delay is required
		//7soft_delay_ms(4000);
	}
	
return 0;	
}


