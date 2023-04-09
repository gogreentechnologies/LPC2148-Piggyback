#include<LPC214X.h>
#include "Serial.h"
#include "adc.h"
#include "lcd.h"
#include<String.h>
#include<stdio.h>
#include<stdlib.h>

char api[120];

void generateApi(int adcVal){
	
	sprintf(api,"GET /update?api_key=17VEYZI06JHI8X1U&field1=%4d HTTP/1.0\r\nHost:api.thingspeak.com\r\n\r\n",adcVal);
}


void flush(char *s){
	
	while(*s){
		*(s++) = '\0';
	}
}

int main(){
	
	char keyPressed;
	char userString[20];
	char connectAp[40];
	char psk[16];
	unsigned int i=0;
	//Initialisation
	lcd_init();
	init_adc0();
	uart1_init();
	uart0_init();
	
	char adc[4];
	/*
	gotoloc(1,1);
	LCD_Cmd(0x01);
	soft_delay_ms(50);
	LCD_WriteString("Open Terminal &");
	soft_delay_ms(100);
	gotoloc(2,1);
	LCD_WriteString("Press Enter");
	
	while(keyPressed!='\r'){
		keyPressed = uart0_getkey();
	}
	keyPressed = uart0_getkey();*/
	//Sending AT
	LCD_Cmd(0x01);
	soft_delay_ms(50);
	gotoloc(1,1);
	LCD_WriteString("SENDING AT");
	uart1_puts("AT\r\n");
	soft_delay_ms(1000);
	
	//Setting Mode=1
	LCD_Cmd(0x01);
	soft_delay_ms(50);
	gotoloc(1,1);
	LCD_WriteString("MODE=1");
	soft_delay_ms(100);
	uart1_puts("AT+CWMODE=1\r\n");
	soft_delay_ms(1000);
	
	//get ssid from terminal
	LCD_Cmd(0x01);
	soft_delay_ms(100);
	gotoloc(1,1);
	LCD_WriteString("ssid:?");
	soft_delay_ms(100);
	uart0_puts("Please enter ssid:");
	while(1){
		keyPressed = uart0_getkey();
		
		if (keyPressed == '\r')
			break;
		else
			userString[i++] = keyPressed;
		uart0_putc(keyPressed);
	}
	keyPressed = uart0_getkey();
	userString[i]='\0';
	
	sprintf(connectAp,"AT+CWJAP=\"%s\",",userString);
	flush(userString);
	i=0;

	//getting password from the terminal
	LCD_Cmd(0x01);
	soft_delay_ms(100);
	gotoloc(1,1);
	LCD_WriteString("psk:?");
	soft_delay_ms(100);
	uart0_puts("\r\nPlease enter password:");
	while(1){
		keyPressed = uart0_getkey();
		
		if (keyPressed == '\r')
			break;
		else
			userString[i++] = keyPressed;
	}
	keyPressed = uart0_getkey();
	userString[i] = '\0';
	
	
	sprintf(psk,"\"%s\"\r\n",userString);
	strcat(connectAp,psk);
	
	flush(userString);
	
	//Connecting to AP
	LCD_Cmd(0x01);
	soft_delay_ms(100);
	gotoloc(1,1);
	LCD_WriteString("CONNECTING TO AP");
	uart1_puts("AT+CWJAP=\"iPhone\",\"11111111\"\r\n");
	soft_delay_ms(1000);
	soft_delay_ms(500);
	gotoloc(2,1);
	LCD_WriteString("CONNECTED");
	soft_delay_ms(100);
	
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
		sprintf(adc,"%4d",val);
		generateApi(val);
		
		//Send command
		LCD_Cmd(0x01);
		soft_delay_ms(100);
		gotoloc(1,1);
		LCD_WriteString("SENDING API");
		uart1_puts("AT+CIPSEND=86\r\n");    // 86 is the number of characters in the api link
		soft_delay_ms(300);
		
		//Sending API
		uart1_puts(api);
		//uart0_puts(api);
		soft_delay_ms(3000);
		LCD_Cmd(0x01);
		soft_delay_ms(100);
		gotoloc(1,1);
		LCD_WriteString("SENT");
		soft_delay_ms(100);
		gotoloc(2,1);
		LCD_WriteString(adc);
		soft_delay_ms(100);
		flush(api);
		
		//totoal 15 sec delay is required
		//soft_delay_ms(4000);
	}
	
return 0;	
}


