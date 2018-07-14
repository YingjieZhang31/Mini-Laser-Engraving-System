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

s32 XC,YC; //当前XY坐标
s32 XT,YT; //目标XY坐标
s32 Xee,Yee,L,FF,L2,S; //XY坐标位移矢量，L插补长度，F标志位,L2 加速度线长 S为加速度插补标志

 //extern s32 X0,Y0;
 //extern s32 Xe,Ye;
 double xyz[N_AXIS];
 double ijk[N_AXIS];

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void runcw(void)  //顺园入口 
 {	
			s32 RX=0; //定义圆心X坐标 
	    s32 RY=0; //定义圆心Y坐标 
	    s32 RXC=0;//以圆心为原点建立坐标系并重新计算坐标值   起点坐标X
	    s32 RYC=0;//以圆心为原点建立坐标系并重新计算坐标值  起点坐标Y
			s32 RXT=0;//以圆心为原点建立坐标系并重新计算坐标值  目标坐标X
			s32 RYT=0;//以圆心为原点建立坐标系并重新计算坐标值  目标坐标Y
	 //以下有改动
 			XT=(xyz[0]); //浮点数扩大成整数
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
					YHR=sqrt((RXC*RXC)+(RYC*RYC));   //计算圆弧半径 根据半径求交点
				
			}
			else 
			{
	 		Xee=XT-XC;
		  Yee=YT-YC;
			L=abs(Xee)+abs(Yee);  //计算步数
	    L2=(L>>1);
	   FF=0;
			if(RXC==0)
			{
						if(RYC==0)
						{
								printf("\r\n字出错\r\n");
						}
						else if(RYC>0)
						{
								//第一象限顺园插补
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
								{           //第三象限顺园插补
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
							//第四象限顺园插补
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
						//第一象限顺园插补
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
						//第四象限顺园插补
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
						//第二象限顺园插补
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
			    //第二象限顺园插补
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
				//第三象限顺园插补
											while(L!=0)
														{           //第三象限顺园插补
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
  void runccw(void)  //逆园入口 
 {			
			s32 RX=0; //定义圆心X坐标 
	    s32 RY=0; //定义圆心Y坐标 
	    s32 RXC=0;//以圆心为原点建立坐标系并重新计算坐标值   起点坐标X
	    s32 RYC=0;//以圆心为原点建立坐标系并重新计算坐标值  起点坐标Y
			//s32 RXT=0;//以圆心为原点建立坐标系并重新计算坐标值  目标坐标X
			//s32 RYT=0;//以圆心为原点建立坐标系并重新计算坐标值  目标坐标Y
	 //以下有改动
 			XT=(xyz[0]); //浮点数扩大成整数
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
			L=abs(Xee)+abs(Yee);  //计算步数
			L2=(L>>1);
	    FF=0;					

			if(RXC==0)
			{
						if(RYC==0)
						{
								printf("\r\n字出错\r\n");
						}
						else if(RYC>0)
						{
								//第二象
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
								//第四象
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
								//第一
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
						//第一
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
						//第四
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
						//第三
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
			    //第二
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
				//第三
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