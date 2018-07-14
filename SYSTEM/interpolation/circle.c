#include "circle.h"
#include "sys.h"
#include "executeX.h"
#include "executeY.h"
#include "fenli.h"

#include <math.h>
#include <inttypes.h>    
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define X_AXIS 0 
#define Y_AXIS 1
#define Z_AXIS 2 
#define N_AXIS 3 

s32 XC,YC; //��ǰXY����
s32 XT,YT; //Ŀ��XY����
s32 Xee,Yee,L,FF,L2,S; //XY����λ��ʸ����L�岹���ȣ�F��־λ,L2 ���ٶ��߳� SΪ���ٶȲ岹��־

 //extern s32 X0,Y0;
 //extern s32 Xe,Ye;
 double xyz[N_AXIS];
 double ijk[N_AXIS];

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void runcw(void)  //˳԰��� 
 {	
			s32 RX=0; //����Բ��X���� 
	    s32 RY=0; //����Բ��Y���� 
	    s32 RXC=0;//��Բ��Ϊԭ�㽨������ϵ�����¼�������ֵ   �������X
	    s32 RYC=0;//��Բ��Ϊԭ�㽨������ϵ�����¼�������ֵ  �������Y
			s32 RXT=0;//��Բ��Ϊԭ�㽨������ϵ�����¼�������ֵ  Ŀ������X
			s32 RYT=0;//��Բ��Ϊԭ�㽨������ϵ�����¼�������ֵ  Ŀ������Y
	 //�����иĶ�
 			XT=(xyz[0]); //���������������
	    YT=(xyz[1]);	 
			RX=(ijk[0])+XC;
			RY=(ijk[1])+YC;
	 ///////////////////////////
			RXC=XC-RX;
			RYC=YC-RY;
			RXT=XT-RY;
			RYT=YT-RY;
	   if ((RXC<0&&RXT>0)||(RYC<0&&RYT>0)||(RXC>0&&RXT<0)||(RYC>0&&RYT>0))
			 {
					s32 YHR=0;
					YHR=sqrt((RXC*RXC)+(RYC*RYC));   //����Բ���뾶 ���ݰ뾶�󽻵�
				
			}
			else 
			{
	 		Xee=XT-XC;
		  Yee=YT-YC;
			L=abs(Xee)+abs(Yee);  //���㲽��
	    L2=(L>>1);
	   FF=0;
			if(RXC==0)
			{
						if(RYC==0)
						{
								printf("\r\n�ֳ���\r\n");
						}
						else if(RYC>0)
						{
								//��һ����˳԰�岹
							while(L!=0)
								{
											if(FF>=0)
											{
													Yfan();													
												  FF=FF-2*RYC+1;
													RYC--;
											}
											else
											{
													 zheng();
													 FF=FF+2*RXC+1;
													 RXC++;
											}
										L--;
								}
						}
						else 
						{
							while(L!=0)
								{           //��������˳԰�岹
															 if(FF>=0)
															 {
																			Yzheng();
																			FF=FF-2*abs(RYC)+1;
																			RYC=abs(RYC)-1;																		
															}
															else
															{
																		fan();
																		FF=FF+2*abs(RXC)+1;
																		RXC=abs(RXC)+1;
															}
											L--;
								}				
					}		
			}
			else if(RXC>0)
			{
					if(RYC==0)
					{
							//��������˳԰�岹
						while(L!=0)
						{
								if(FF>=0)
								{
									fan();
									FF=FF-2*abs(RXC)+1;
									RXC=abs(RXC)-1;
								}
								else
								{
										Yfan();
										FF=FF+2*abs(RYC)+1;
										RYC=abs(RYC)+1;
								}
							L--;
						}
					}
					else if(RYC>0)
					{
						//��һ����˳԰�岹
						while(L!=0)
								{
											if(FF>=0)
											{
													Yfan();													
												  FF=FF-2*RYC+1;
													RYC--;
											}
											else
											{
													 zheng();
													 FF=FF+2*RXC+1;
													 RXC++;
											}
										L--;
								}
					}
					else
					{
						//��������˳԰�岹
							while(L!=0)
							{
									if(FF>=0)
									{
										fan();
										FF=FF-2*abs(RXC)+1;
										RXC=abs(RXC)-1;
									}
									else
									{
											Yfan();
											FF=FF+2*abs(RYC)+1;
											RYC=abs(RYC)+1;
									}
								L--;
							}
					}
			}
			else if(RYC==0)
			{
						//�ڶ�����˳԰�岹
				   while(L!=0)
					 {
								if(FF>=0)
								{
									zheng();
									FF=FF-2*abs(RXC)+1;
									RXC=abs(RXC)-1;
								}
								else
								{
									Yzheng();
									FF=FF+2*abs(RYC)+1;
									RYC=abs(RYC)+1;
								}
							L--;
						}
			}
			else if(RYC>0)
			{
			    //�ڶ�����˳԰�岹
				 while(L!=0)
					 {
								if(FF>=0)
								{
									zheng();
									FF=FF-2*abs(RXC)+1;
									RXC=abs(RXC)-1;
								}
								else
								{
									Yzheng();
									FF=FF+2*abs(RYC)+1;
									RYC=abs(RYC)+1;
								}
							L--;
						}
			}
			else
			{
				//��������˳԰�岹
											while(L!=0)
														{           //��������˳԰�岹
															 if(FF>=0)
															 {
																			Yzheng();
																			FF=FF-2*abs(RYC)+1;
																			RYC=abs(RYC)-1;																		
															}
															else
															{
																		fan();
																		FF=FF+2*abs(RXC)+1;
																		RXC=abs(RXC)+1;
															}
											L--;
												}				
						}
					}
 }
 
 
 ////////////////////////////////////////////////////////////////////////////////////
  void runccw(void)  //��԰��� 
 {			
			s32 RX=0; //����Բ��X���� 
	    s32 RY=0; //����Բ��Y���� 
	    s32 RXC=0;//��Բ��Ϊԭ�㽨������ϵ�����¼�������ֵ   �������X
	    s32 RYC=0;//��Բ��Ϊԭ�㽨������ϵ�����¼�������ֵ  �������Y
			//s32 RXT=0;//��Բ��Ϊԭ�㽨������ϵ�����¼�������ֵ  Ŀ������X
			//s32 RYT=0;//��Բ��Ϊԭ�㽨������ϵ�����¼�������ֵ  Ŀ������Y
	 //�����иĶ�
 			XT=(xyz[0]); //���������������
	    YT=(xyz[1]);	 
			RX=(ijk[0])+XC;
			RY=(ijk[1])+YC;
	 /////////////////////////////////
			RXC=XC-RX;
			RYC=YC-RY;
			//RXT=XT-RY;
			//RYT=YT-RY;
	 		Xee=XT-XC;
		  Yee=YT-YC;
			L=abs(Xee)+abs(Yee);  //���㲽��
			L2=(L>>1);
	    FF=0;					

			if(RXC==0)
			{
						if(RYC==0)
						{
								printf("\r\n�ֳ���\r\n");
						}
						else if(RYC>0)
						{
								//�ڶ���
									while(L!=0)
								{
										if(FF>=0)
											{
											Yfan();
											FF=FF-2*abs(RYC)+1;
										 RYC=abs(RYC)-1;
											}
										else 
										{
												zheng();
												FF=FF+2*abs(RXC)+1;
												RXC=abs(RXC)+1;
										}
									 L--;
								}
						}
						else 
						{
								//������
									while(L!=0)
								{
										if(FF>=0)
											{
											Yzheng();
											FF=FF-2*abs(RYC)+1;
										 RYC=abs(RYC)-1;
											}
										else 
										{
												zheng();
												FF=FF+2*abs(RXC)+1;
												RXC=abs(RXC)+1;
										}
									 L--;
								}
					}		
			}
			else if(RXC>0)
			{
					if(RYC==0)
					{
								//��һ
	 							while(L!=0)
								{
										if(FF>=0)
											{
											fan();
											FF=FF-2*RXC+1;
										 RXC--;
											}
										else 
										{
												Yzheng();
												FF=FF+2*RYC+1;
												RYC++;
										}
									 L--;
								}
					}
					else if(RYC>0)
					{
						//��һ
	 							while(L!=0)
								{
										if(FF>=0)
											{
											fan();
											FF=FF-2*RXC+1;
										 RXC--;
											}
										else 
										{
												Yzheng();
												FF=FF+2*RYC+1;
												RYC++;
										}
									 L--;
								}
					}
					else
					{
						//����
						while(L!=0)
								{
										if(FF>=0)
											{
											Yzheng();
											FF=FF-2*abs(RYC)+1;
										 RYC=abs(RYC)-1;
											}
										else 
										{
												fan();
												FF=FF+2*abs(RXC)+1;
												RXC=abs(RXC)+1;
										}
									 L--;
								}
					}
			}
			else if(RYC==0)
			{
						//����
									while(L!=0)
								{
										if(FF>=0)
											{
											zheng();
											FF=FF-2*abs(RXC)+1;
										 RXC=abs(RXC)-1;
											}
										else 
										{
												Yfan();
												FF=FF+2*abs(RYC)+1;
												RYC=abs(RYC)+1;
										}
									 L--;
								}
			}
			else if(RYC>0)
			{
			    //�ڶ�
						while(L!=0)
								{
										if(FF>=0)
											{
											Yfan();
											FF=FF-2*abs(RYC)+1;
										 RYC=abs(RYC)-1;
											}
										else 
										{
												zheng();
												FF=FF+2*abs(RXC)+1;
												RXC=abs(RXC)+1;
										}
									 L--;
								}
			}
			else
			{
				//����
											while(L!=0)
								{
										if(FF>=0)
											{
											zheng();
											FF=FF-2*abs(RXC)+1;
										 RXC=abs(RXC)-1;
											}
										else 
										{
												Yfan();
												FF=FF+2*abs(RYC)+1;
												RYC=abs(RYC)+1;
										}
									 L--;
								}
			}

 }