#include "executeX.h"
#include "delay.h"
#include "interpolation.h"

extern int Ye;

  void TEzheng(void);
	void TEfan(void);

void executeTE()
{
  if (Ye>=0)
	{
	 TEzheng();
	}
	else
	{
	TEfan();
	}
}

void TEzheng()
{
			int n=2;
	
 GPIO_SetBits(GPIOE,GPIO_Pin_3);
	
		while(n>0){
		 GPIO_SetBits(GPIOE,GPIO_Pin_2);
		delay_ms(30);
		 GPIO_ResetBits(GPIOE,GPIO_Pin_2);
			delay_ms(30);
			n=n-1;
	  }
}

void TEfan()
{
	int n=2;
	
 GPIO_ResetBits(GPIOE,GPIO_Pin_3);
		
		while(n>0){
		 GPIO_SetBits(GPIOE,GPIO_Pin_2);
		delay_ms(30);
		 GPIO_ResetBits(GPIOE,GPIO_Pin_2);
			delay_ms(30);
			n=n-1;
	  }
}
