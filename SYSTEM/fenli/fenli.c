#include "fenli.h"
#include "interpolation.h"
#include <math.h>
#include <inttypes.h>    
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define bool int
#define false 0
#define true 1

#define X_AXIS 0 
#define Y_AXIS 1
#define Z_AXIS 2 
#define N_AXIS 3 

#define MAX_INT_DIGITS 12

//以下真正激光控制用(Laser ON/OFF)///////////////////////////////
#define laseron  GPIO_SetBits(GPIOB,GPIO_Pin_0);
#define laseroff  GPIO_ResetBits(GPIOB,GPIO_Pin_0);
///////////////////////////////////////////////////

//以下激光测试用(test use only)//////////////////////////////////
//#define laseron   GPIO_ResetBits(GPIOE,GPIO_Pin_5);
//#define laseroff   GPIO_SetBits(GPIOE,GPIO_Pin_5);
/////////////////////////////////////////////////

u8 read_float(u8 *line, u8 *char_counter, double *float_ptr) ;
u8 motion;
int laser;
s32 X0=0,Y0=0; //当前XY坐标
s32 Xe=0,Ye=0; //目标XY坐标

extern double xyz[N_AXIS];
extern double ijk[N_AXIS];


void fenli(u8 *line)
{
  u8 char_counter = 0;
	u8 letter;
	double value;
	u8 int_value;
		while(line[char_counter]!='\0')
		{
		        letter=line[char_counter];
						char_counter++;
						read_float(line, &char_counter, &value);
				   	int_value=(u8)value;
		  switch(letter)
			{
				case 'G':switch(int_value)
			            {
										case 0:motion=0;break;//定位(fast locating)
										case 1:motion=1;break;//直线差补(linear interpolation)
										case 2: motion = 2; break; // G2 顺时针圆弧插补(clockwise circular interpolation, not finished)
										case 3: motion = 3; break; // G3 逆时针圆弧插补(counterclockwise circular inpterpolation, not finished)
										case 75: motion=4,xyz[X_AXIS] =0,xyz[Y_AXIS] =0,xyz[Z_AXIS] =0; break; //回到坐标原点
										case 30: X0=0,Y0=0,Xe=0,Ye=0,Xe=0,Ye=0,xyz[X_AXIS] =0,xyz[Y_AXIS] =0,xyz[Z_AXIS] =0;break; //设置为坐标零点
									}break;
						//以下为激光开关标志位设定(the following is used to control the on/off of the laser)			
           					case 'M':
										switch(int_value)
										  {
												case 3: laser = 1; break;  //激光开(laser on)
												case 5: laser = 0; break;  //激光关(laser off)
											}
									break;
											
			  case 'X':xyz[X_AXIS] = value;Xe=value;break;
				case 'Y':xyz[Y_AXIS] = value;Ye=value;break;
        
			  case 'I':ijk[X_AXIS] = value;break;
				case 'J':ijk[Y_AXIS] = value;break;	
			
			}
		}
		
			//以下激光开关使能(Enable/disenable the laser)
										if(laser==1)
				{
							laseron;

				}
				else
				{
							laseroff;
				}
		
		switch(motion)
					{
						case 0: interpolation(); 
						        break; // G0 快速定位 (fast locating)
						case 1: interpolation(); 
						        break; // G1 直线插补 (linear interpolation)
						case 2: //runcw();
       							break; // G2 顺时针圆弧插补 (circular interpolation not available)
						case 3: //runccw();
         						break; // G3 逆时针圆弧插补	(circular interpolation not available)
						case 4: //runline();
       							break; // G75 回到编程0点 (not available)
					}
//printf("G=%d\r\n\r\n",motion);
//printf("X=%f\r\n\r\n",xyz[X_AXIS]);//用浮点
//printf("Y=%f\r\n\r\n",xyz[Y_AXIS]);//用浮点
	//printf("i=%f\r\n\r\n",ijk[X_AXIS]);//用浮点
	//printf("j=%f\r\n\r\n",ijk[Y_AXIS]);//用浮点



}

u8 read_float(u8 *line, u8 *char_counter, double *float_ptr) //提取字符串内指定字符开始的浮点数字，遇到非数字字符停止，并赋值给双精度浮点数 value(seize float in the string)               
{
	u32 intval = 0;
  s8 exp = 0;
  u8 ndigit = 0;
	u8 c;
  double fval;
	bool isnegative = false; //正负标志位
  bool isdecimal = false;  //小数标志位
	
  u8 *ptr = line + *char_counter;
  
  
  //设第一个字符和增量指针。
  c = *ptr++;
  
  // 捕捉最初的正/负号
 
  if (c == '-') {
    isnegative = true;
    c = *ptr++;
  } else if (c == '+') {
    c = *ptr++;
  }
  
  // 提取整数，并计算小数


  while(1) {
    c -= '0';  //将字符转化为数字 赋值给c
    if (c <= 9) {
      ndigit++;
      if (MAX_INT_DIGITS <= 12) { //判断是否到最大位数
        if (isdecimal) { exp--; }  //如果是小数
        intval = (((intval << 2) + intval) << 1) + c; // intval*10 + c  用左移节省时间
      } else {
        if (!(isdecimal)) { exp++; }  //如果没有小树
      }
    }
		else if (c == (('.'-'0') & 0xff)  &&  !(isdecimal)) {
      isdecimal = true;
    } else {
      break;
    }
    c = *ptr++;
  }
  
  // 如果没有数字了 返回假
  if (!ndigit) { return(false); };
  
  //  整数转换成浮点数。

  fval = (double)intval; //强制转换
  
	//应用小数，应执行的不超过两个浮点乘法 
  // E0至E-4的预期范围。
  if (fval != 0) {
    while (exp <= -2) {
      fval *= 0.01; 
      exp += 2;
    }
    if (exp < 0) { 
      fval *= 0.1; 
    } else if (exp > 0) {
      do {
        fval *= 10.0;
      } while (--exp > 0);
    } 
  }   //计算小数点的位置 

  //   指定浮点值与正确的标志。
  if (isnegative) {
    *float_ptr = -fval;
  } else {
    *float_ptr = fval;
  }

  *char_counter = ptr - line - 1; //  设置char_counter到下一条语句
  
  return(true);
}
