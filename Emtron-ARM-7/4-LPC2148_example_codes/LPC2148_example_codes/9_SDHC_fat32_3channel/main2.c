// FAT 32, 1024 bytes sector size, do full format

#include <LPC214x.H>                       /* LPC214x definitions */
#include <stdio.h>
#include "type.h"
#include "Serial.h"
#include "ssp.h"
#include "rtc.h"
#include "sd.h"
#include "utils.h"
#include "lcd.h"
#include "FAT.h"

//#include "lpc2000_spi.h"

//#define SD_CARD BIT20
//#define SD_SELECTION_DIR_SET (IO0DIR |= SD_CARD)
//#define SD_SELECTION_SET (IO0SET = SD_CARD)
//#define SD_SELECTION_CLR (IO0CLR = SD_CARD)




extern unsigned char SD_version, cardType, SDHC_flag,sd_buf[512];
extern char currentDir[16],cmd[4],args[32];
unsigned long curCluster;
char buf[32];

void delay(int count)
{
  int j=0,i=0;

  for(j=0;j<count;j++)
  {
    /* At 60Mhz, the below loop introduces
    delay of 10 us */
    for(i=0;i<35;i++);
  }
}

/**
*******************************************************************
	Funtion Name : test_sd_card()

	Description  : 

	Input        : 

	Output       : None

	Note         :
*****************************************************************
*/
U8 test_sd_card(void)
{
	
  if(sdInit())
  {
   	uart0_puts("\n\rError!");
	return 0;
  }
  else
  {
    uart0_puts("\n\rMemory Card Detected");
	sprintf((char *)buf,"\n\rSD Version=%02d",SD_version);
	uart0_puts((char *)buf);
	if(SDHC_flag)
		uart0_puts("\n\rCard Type:SDHC");
	else
		uart0_puts("\n\rCard Type:SD");
    return 1;		
  }
}

/***********************************************************/
int main (void) 
{
	//unsigned char sd_buf[512];
	signed char resp;
	U8 ucTemp,buf[128];
	U16 uiTemp;
	U32 fsize,dt1,dt2,dt3;
//	unsigned int baseAddr,bytesPerSec,totalSec,j,secPerFAT,resSecCnt,maxRootEntry;
	U32 size;
	struct dirTab *rootTab;
	U32 uliTemp,i,temp1;
	

 // init_lcd();
 	spi1_init();
  	uart0_init();
    uart1_init();
	rtc_init();
  //SD_SELECTION_SET;	
  
  delay(10000);
  uart0_puts("\n\r\n****************************************************\n\r");
  uart0_puts("SOLAR LOGGER");
  uart0_puts("\n\r****************************************************\n\r");
  
  if(!test_sd_card())
  	while(1);

  fsize=sd_getDriveSize();
  
  	uart0_puts("\n\rDrive Size:");
  	displaySize(fsize);
  
  
  	uart0_puts("\n\r");	
  
  	resp=getBSData();
  	if(resp)
  		uart0_puts("Error!");	
	
	ucTemp=0;  	
	init_adc0(1);
	init_adc0(2);	
	init_adc0(3);
	while(1)
	{
		if(!(MIN%4) && !ucTemp)
		{
			ucTemp=1;
			temp1=0;		
			AD0CR = 0x00200D00 | 2;    // select channel
    		AD0CR |= 0x01000000; // Start A/D Conversion
		    	
			do
    		{
	    		temp1 = AD0GDR; // Read A/D Data Register
    		} while ((temp1 & 0x80000000) == 0); // Wait for end of A/D Conversion
			dt1=((temp1>>6)&0x000003FF);
		
			/*****************************************************/
			temp1=0;		
			AD0CR = 0x00200D00 | 4;    // select channel
    		AD0CR |= 0x01000000; // Start A/D Conversion
    	
			do
    		{
    			temp1 = AD0GDR; // Read A/D Data Register
    		} while ((temp1 & 0x80000000) == 0); // Wait for end of A/D Conversion
			dt2=((temp1>>6)&0x000003FF);
			/*****************************************************/
			temp1=0;
			AD0CR = 0x00200D00 | 8;    // select channel
    		AD0CR |= 0x01000000; // Start A/D Conversion
	    	
			do
	    	{
    			temp1 = AD0GDR; // Read A/D Data Register
	    	} while ((temp1 & 0x80000000) == 0); // Wait for end of A/D Conversion
			dt3=((temp1>>6)&0x000003FF);

			sprintf((unsigned char *)buf,"Date=%02d-%02d-%04d Time=%02d-%02d ad0=%04d ad1=%04d ad2=%04d;",DOM,MONTH,YEAR,HOUR,MIN,dt1,dt2,dt3);
			//sprintf((unsigned char *)buf,"Date=%02d-%02d-%04d;",DOM,MONTH,YEAR);

			writeFile("LOG1.TXT",2,54,buf,0);
			//ucTemp++;
			//delay(10000);		

		}
		if(MIN%4)
			ucTemp=0;
			
  	}  	
}
