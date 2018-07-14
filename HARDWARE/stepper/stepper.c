#include "stepper.h"
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//版权所有，盗版必究。
//Copyright(C) 山东大学（威海）15号楼2区303室
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

//注：DIR =0 向电机走
//    DIR =1 远离电机走

//x轴电机为立着的
//y轴电机为水平着的

void stepper_init(void)
{
 //以下为LED指示灯使能
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOF, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
 GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 输出高

	
//以下为X轴(一号)步进电机使能（PE0 STEP;PE1 DIR）
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	 //PE0  STEP 		 
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  			
 GPIO_ResetBits(GPIOE,GPIO_Pin_0); 		
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	    	//	 PE1=0向电机走
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				//   PE1=1远离电机走
 GPIO_SetBits(GPIOE,GPIO_Pin_1); 				

//以下为Y轴(二号)步进电机使能（PE2 STEP;PE3 DIR）
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	 //PE2  STEP 		 
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  			
 GPIO_ResetBits(GPIOE,GPIO_Pin_2); 		
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	    	//	 PE3=0向电机走
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				//   PE3=1远离电机走
 GPIO_SetBits(GPIOE,GPIO_Pin_3); 

/*以下配置细分，可以不用
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	    		//PF0 MS1=0
 GPIO_Init(GPIOF, &GPIO_InitStructure);	  			
 GPIO_SetBits(GPIOF,GPIO_Pin_0);

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	    		 //PF1 MS2=1
 GPIO_Init(GPIOF, &GPIO_InitStructure);	  				 
 GPIO_SetBits(GPIOF,GPIO_Pin_1); 						 
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //PF2 MS3=0
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 
 GPIO_SetBits(GPIOF,GPIO_Pin_2); 	*/		
 
 //以下为激光使能
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	    		//PB0 激光  Reset关闭
 GPIO_Init(GPIOB, &GPIO_InitStructure);	  			
 GPIO_ResetBits(GPIOB,GPIO_Pin_0);

}
 
//细分设置如下
//MS1	MS2	MS3	细分
//0 0	0	1
//1	0	0	2//185*2步
//0	1	0	4//385*2步走一个行程
//1	1	0	8
//1	1	1	16




