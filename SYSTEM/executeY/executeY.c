#include "executeY.h"
#include "delay.h"
#include "interpolation.h"

extern int flag;

  void Yzheng(void);
	void Yfan(void);

void executeY()
{
  if (flag==1||flag==2 )
	{
	 Yzheng();
	}
	else
	{
	Yfan();
	}
}

void Yzheng()
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

void Yfan()
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
