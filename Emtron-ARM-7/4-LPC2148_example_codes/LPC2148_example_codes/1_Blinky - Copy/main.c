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
 	IO0DIR|=((unsigned long)1<<5);
	IO0DIR|=((unsigned long)1<<6);
	IO0DIR|=((unsigned long)1<<7);
	IO0DIR|=((unsigned long)1<<11);
	IO0DIR|=((unsigned long)1<<31);
 	
	while(1){
 		IO0SET=((unsigned long)1<<5);
		IO0SET=((unsigned long)1<<31);
		wait(100000);
		IO0CLR=((unsigned long)1<<5);
		IO0CLR=((unsigned long)1<<31);
		wait(100000);
		
		IO0SET=((unsigned long)1<<6);
		wait(100000);
		IO0CLR=((unsigned long)1<<6);
		wait(100000);
		
		IO0SET=((unsigned long)1<<7);
		wait(100000);
		IO0CLR=((unsigned long)1<<7);
		wait(100000);
		
		IO0SET=((unsigned long)1<<11);
		wait(100000);
		IO0CLR=((unsigned long)1<<11);
		wait(100000);
		
		
		
		
		i++;
	}
}

