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
 
 extern double xyz[N_AXIS];    // X,Y,Z 目标XYZ坐标
 extern double ijk[N_AXIS];     // ijk偏移坐标
 

 int main(void)
 {		
 	u16 t;  
	u16 len;	
	u16 times=0;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 //串口初始化为115200
 	LED_Init();			     //LED端口初始化
	KEY_Init();          //初始化与按键连接的硬件接口
	stepper_init();		//stepper motor initialized
	printf("\r\nGrbl 0.9g\r\n\r\n");
	 printf("ok\r\n");
	
	 while(1)// Main Loop Start!
	{
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			//printf("\r\n您发送的消息为:\r\n\r\n");
			for(t=0;t<len;t++)
			{
				line[t]=USART_RX_BUF[t];	//Get G code from master PC and save it.
				//USART_SendData(USART1, USART_RX_BUF[t]);//向串口1发送数据
				//while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
			}
			//printf("\r\n\r\n");//插入换行
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
			if(times%30==0)LED0=!LED0;//闪烁LED,提示系统正在运行.
			delay_ms(10);  	
		}
	}
}

