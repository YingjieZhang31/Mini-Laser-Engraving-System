#include "executeX.h"
#include "delay.h"
#include "interpolation.h"

extern int flag;


  void zheng(void);
	void fan(void);

void executeX()
{
  if (flag==1||flag==4)
	{
	  zheng();
	}
	else
	{
	fan();
	}
}

void zheng()
{
			int n=2;
	
 GPIO_SetBits(GPIOE,GPIO_Pin_1);
	
		while(n>0){
		 GPIO_SetBits(GPIOE,GPIO_Pin_0);
		delay_ms(30);
		 GPIO_ResetBits(GPIOE,GPIO_Pin_0);
			delay_ms(30);
			n=n-1;
	  }
}

void fan()
{
	int n=2;
	
 GPIO_ResetBits(GPIOE,GPIO_Pin_1);
		
		while(n>0){
		 GPIO_SetBits(GPIOE,GPIO_Pin_0);
		delay_ms(30);
		 GPIO_ResetBits(GPIOE,GPIO_Pin_0);
			delay_ms(30);
			n=n-1;
	  }
}
