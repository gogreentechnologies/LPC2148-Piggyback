#include <LPC214X.h>
#include "Serial.h"
#include "adc.h"

unsigned int cnt;
  
  
  

 void process_adc(void)
{
	unsigned short adc_value = 0;
  	unsigned char buf[16] = {0};

  	adc_value = adc_read(ADC0, CHANNEL_1);	
  	sprintf((char *)buf, "ADC:%d ", adc_value);
  	uart0_puts((char *)buf);

}



int main()
{
     unsigned int n= 0x00010000;
     unsigned int i;


    init_adc0();


	uart0_init();

    for ( i=1;i<=100;i++) 
	{
	    IOSET1 = n;  
		process_adc();
      IOCLR1 = 0x00FF0000;                  /* Turn off LEDs */
	}
    AD0CR &= ~0x01000000;
	

 	
	
}

