#include <LPC214X.h>
#include "Serial.h"


void wait(int count)
{
  int j=0,i=0;

  for(j=0;j<count;j++)
  {
    /* At 60Mhz, the below loop introduces
    delay of 10 us */
    for(i=0;i<35;i++);
  }
}


int main()
{
	uart0_init();
 //	IO0DIR|=((unsigned long)1<<31);

 	while(1){
 	uart0_puts("\n\rHello World!!!");
	wait(1000);
	}
	
}

