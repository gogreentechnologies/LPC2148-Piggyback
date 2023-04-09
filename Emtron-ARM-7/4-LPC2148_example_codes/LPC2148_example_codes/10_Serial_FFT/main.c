#include <LPC214X.h>
#include <stdio.h>
#include <math.h>
#include "Serial.h"
#include "adc.h"

#define PI 3.14
#define RESOLUTION_OF_DFT_N 10 

unsigned short adcc[RESOLUTION_OF_DFT_N];
unsigned short FFT[RESOLUTION_OF_DFT_N]; 
 
  

 /*void process_adc(void)
{
//	unsigned short adc_value = 0;
//  	unsigned char buf[16] = {0};

//  	adc_value = adc_read(ADC0, CHANNEL_1);
	adcc[i] = adc_read(ADC0, CHANNEL_1);
//	adcc[i]=adc_value;	
//  	sprintf((char *)buf, "%04d ", adcc[i]);
  	
//	uart0_puts((char *)buf);

}  */



int main()
{
     unsigned int n= 0x00010000;
     float A=0;
	 float B=0;
	 unsigned int i,j;
	unsigned char disp_buf[100] = {0};

    init_adc0();


	uart0_init();

    for ( i=0;i<RESOLUTION_OF_DFT_N;i++) 
	{
	    IOSET1 = n;  
		adcc[i] = adc_read(ADC0, CHANNEL_1);
        IOCLR1 = 0x00FF0000;                  /* Turn off LEDs */
	}
    AD0CR &= ~0x01000000;
	
    for (i=0;i<RESOLUTION_OF_DFT_N;i++)
	{
      for (j=0;j<RESOLUTION_OF_DFT_N;j++)
	  {
          A+=adcc[j]*cos(2*PI*i*j/RESOLUTION_OF_DFT_N);
          B+=adcc[j]*sin(2*PI*i*j/RESOLUTION_OF_DFT_N);    
      }
     FFT[i]=sqrt(A*A+B*B);
     A=0;
     B=0;
    }
	 for ( i=0;i<RESOLUTION_OF_DFT_N;i++)
	 {
 	sprintf((char *)disp_buf, "%f", FFT[i]);
	uart0_puts((char *)disp_buf);
	uart0_puts("\n\r");
	}
}

