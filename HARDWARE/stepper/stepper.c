#include "stepper.h"
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//��Ȩ���У�����ؾ���
//Copyright(C) ɽ����ѧ��������15��¥2��303��
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

//ע��DIR =0 ������
//    DIR =1 Զ������

//x����Ϊ���ŵ�
//y����Ϊˮƽ�ŵ�

void stepper_init(void)
{
 //����ΪLEDָʾ��ʹ��
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOF, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
 GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 �����

	
//����ΪX��(һ��)�������ʹ�ܣ�PE0 STEP;PE1 DIR��
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	 //PE0  STEP 		 
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  			
 GPIO_ResetBits(GPIOE,GPIO_Pin_0); 		
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	    	//	 PE1=0������
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				//   PE1=1Զ������
 GPIO_SetBits(GPIOE,GPIO_Pin_1); 				

//����ΪY��(����)�������ʹ�ܣ�PE2 STEP;PE3 DIR��
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	 //PE2  STEP 		 
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  			
 GPIO_ResetBits(GPIOE,GPIO_Pin_2); 		
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	    	//	 PE3=0������
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				//   PE3=1Զ������
 GPIO_SetBits(GPIOE,GPIO_Pin_3); 

/*��������ϸ�֣����Բ���
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	    		//PF0 MS1=0
 GPIO_Init(GPIOF, &GPIO_InitStructure);	  			
 GPIO_SetBits(GPIOF,GPIO_Pin_0);

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	    		 //PF1 MS2=1
 GPIO_Init(GPIOF, &GPIO_InitStructure);	  				 
 GPIO_SetBits(GPIOF,GPIO_Pin_1); 						 
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //PF2 MS3=0
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 
 GPIO_SetBits(GPIOF,GPIO_Pin_2); 	*/		
 
 //����Ϊ����ʹ��
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	    		//PB0 ����  Reset�ر�
 GPIO_Init(GPIOB, &GPIO_InitStructure);	  			
 GPIO_ResetBits(GPIOB,GPIO_Pin_0);

}
 
//ϸ����������
//MS1	MS2	MS3	ϸ��
//0 0	0	1
//1	0	0	2//185*2��
//0	1	0	4//385*2����һ���г�
//1	1	0	8
//1	1	1	16




