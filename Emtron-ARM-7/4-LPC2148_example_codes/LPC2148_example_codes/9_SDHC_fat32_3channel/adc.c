#include "adc.h"
#include <LPC214x.H>                       /* LPC214x definitions */

#define ECG_ARRAY_LEN 240

extern unsigned char ecgData[ECG_ARRAY_LEN];
extern unsigned short writeIndex,readIndex;

/***** Tried this but anothr irq messes with the timer 0 irq (scheduler) ***/
/*__irq void adc0_ch1_ir(void )
{
	unsigned int i;
	VICVectAddr=0;	
	i=AD0DR1;
    ecgData[writeIndex]=(i>>8) & 0x00FF;
	writeIndex=(writeIndex+1)%ECG_ARRAY_LEN;		
}
  */
/*******************************************************************************/	
void init_adc0(unsigned char ch)
{
	if(ch==1)
  		PINSEL1 = (PINSEL1 & ~(3 << 24)) | (1 << 24);
	else if(ch==2)
  		PINSEL1 = (PINSEL1 & ~(3 << 26)) | (1 << 26);
	else if(ch==3)
  		PINSEL1 = (PINSEL1 & ~(3 << 28)) | (1 << 28);
				
/*	VICIntEnable |= (unsigned long int)(1<<18);                  // Enable adc0 int
  	VICVectCntl2 = 0x20 | 18;                    // use it for adc0 int
  	VICVectAddr2 = (unsigned long int) adc0_ch1_ir;         // set interrupt vector in 2
  	AD0INTEN=0x00000002;
*/
 //	AD0CR = 0x00200D00 | 2;    // start first conversion
// 	AD0CR |= 0x01000000; 
 
}

/*******************************************************************************/	
void init_adc1(void)
{

}

/*******************************************************************************/

unsigned short adc_read(unsigned char adc_num, unsigned char ch)
{
  unsigned int i=0;
  
  switch(adc_num)
  {
    case ADC0:
      AD0CR = 0x00200D00 | (1<<ch);    // select channel
      AD0CR |= 0x01000000; // Start A/D Conversion
    
      do
      {
        i = AD0GDR; // Read A/D Data Register
      } while ((i & 0x80000000) == 0); // Wait for end of A/D Conversion
      break;
    
    case ADC1:
      AD1CR = 0x00200D00 | (1<<ch); // select channel
      AD1CR |= 0x01000000; // Start A/D Conversion
      do
      {
        i = AD1GDR; // Read A/D Data Register
      } while ((i & 0x80000000) == 0); // Wait for end of A/D Conversion
      break;
  }
 
  return (i >> 6) & 0x03FF; // bit 6:15 is 10 bit AD value
}

/**************************************************************/
__inline unsigned char inline_adc0_read()
{
	unsigned int i=0;
	AD0CR = 0x00200D00 | 2;    // select channel
    AD0CR |= 0x01000000; // Start A/D Conversion
    
    do
    {
    	i = AD0GDR; // Read A/D Data Register
    } while ((i & 0x80000000) == 0); // Wait for end of A/D Conversion
	return (i >> 8) & 0x00FF; // bit 6:15 is 10 bit AD value
}