#include <LPC214X.h>


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

unsigned long i=0;
int main()
{	 	PINSEL2 = 0x00000000;
		IO1DIR |= 0x00FF0000;

		// DC Motor-1 & 2 ON   0x00500000	for opposite Direction
		//IO1SET |= 0x00A00000;


	
 	while(1){
		IO1CLR |= 0x00FF0000;
 		IO1SET |= 0x00800000;
	  	wait(100000);
		IO1CLR |= 0x00800000;
   		IO1SET |= 0x00400000;
	  	wait(100000);
		IO1CLR |= 0x00400000;
   		IO1SET |= 0x00200000;
	  	wait(100000);
		IO1CLR |= 0x00200000;
   		IO1SET |= 0x00100000;
	  	wait(100000);
     
   
   
   //		IO1CLR |= 0x00FF0000;
		wait(100000);
		i++;
	}
}

