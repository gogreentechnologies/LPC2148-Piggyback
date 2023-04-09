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


int main()
{
 unsigned long i=0;

 IO0DIR &= ~((1<<16)) ; // explicitly making P0.16 as Input - even though by default its already Input
 IO0DIR |= (1<<31); // Configuring P0.31 as Output 

 while(1)
   {
   if(IO0PIN & (1<<16))
   		{
		IO0SET |= (1<<31); // drive P0.30 High
		wait(100000);
		IO0SET=(1<<16);
		}
	else
		{
		IO0CLR|=(1<<31);
		wait(100000);
		IO0CLR=(1<<16);
		}
		i++;
   }
}

