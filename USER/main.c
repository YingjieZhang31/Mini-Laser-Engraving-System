#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "fenli.h"
#include "stepper.h"
#include "interpolation.h"
#include <string.h> 
 
#define X_AXIS 0 
#define Y_AXIS 1
#define Z_AXIS 2 
#define N_AXIS 3 
 
 u8 line[250]={0};
 extern s32 X0,Y0;
 extern s32 Xe,Ye;
 
 extern double xyz[N_AXIS];    // X,Y,Z Ŀ��XYZ����
 extern double ijk[N_AXIS];     // ijkƫ������
 

 int main(void)
 {		
 	u16 t;  
	u16 len;	
	u16 times=0;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 //���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
	KEY_Init();          //��ʼ���밴�����ӵ�Ӳ���ӿ�
	stepper_init();		//stepper motor initialized
	printf("\r\nGrbl 0.9g\r\n\r\n");
	 printf("ok\r\n");
	
	 while(1)// Main Loop Start!
	{
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			//printf("\r\n�����͵���ϢΪ:\r\n\r\n");
			for(t=0;t<len;t++)
			{
				line[t]=USART_RX_BUF[t];	//Get G code from master PC and save it.
				//USART_SendData(USART1, USART_RX_BUF[t]);//�򴮿�1��������
				//while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
			}
			//printf("\r\n\r\n");//���뻻��
			USART_RX_STA=0;
     	fenli(line);         //Parse G code and control the motor(Important!!!!!!)
			delay_us(500);
			X0=Xe;
			Y0=Ye;
			printf("ok\r\n");// After handling one command, send ok to the master PC and PC will send next G code command. 
			//interpolation();
		}else
		{
			times++;
			//if(times%200==0)printf("Please enter your G code command...\r\n");  
			if(times%30==0)LED0=!LED0;//��˸LED,��ʾϵͳ��������.
			delay_ms(10);  	
		}
	}
}

