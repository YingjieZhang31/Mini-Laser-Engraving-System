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

//�����������������(Laser ON/OFF)///////////////////////////////
#define laseron  GPIO_SetBits(GPIOB,GPIO_Pin_0);
#define laseroff  GPIO_ResetBits(GPIOB,GPIO_Pin_0);
///////////////////////////////////////////////////

//���¼��������(test use only)//////////////////////////////////
//#define laseron   GPIO_ResetBits(GPIOE,GPIO_Pin_5);
//#define laseroff   GPIO_SetBits(GPIOE,GPIO_Pin_5);
/////////////////////////////////////////////////

u8 read_float(u8 *line, u8 *char_counter, double *float_ptr) ;
u8 motion;
int laser;
s32 X0=0,Y0=0; //��ǰXY����
s32 Xe=0,Ye=0; //Ŀ��XY����

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
										case 0:motion=0;break;//��λ(fast locating)
										case 1:motion=1;break;//ֱ�߲(linear interpolation)
										case 2: motion = 2; break; // G2 ˳ʱ��Բ���岹(clockwise circular interpolation, not finished)
										case 3: motion = 3; break; // G3 ��ʱ��Բ���岹(counterclockwise circular inpterpolation, not finished)
										case 75: motion=4,xyz[X_AXIS] =0,xyz[Y_AXIS] =0,xyz[Z_AXIS] =0; break; //�ص�����ԭ��
										case 30: X0=0,Y0=0,Xe=0,Ye=0,Xe=0,Ye=0,xyz[X_AXIS] =0,xyz[Y_AXIS] =0,xyz[Z_AXIS] =0;break; //����Ϊ�������
									}break;
						//����Ϊ���⿪�ر�־λ�趨(the following is used to control the on/off of the laser)			
           					case 'M':
										switch(int_value)
										  {
												case 3: laser = 1; break;  //���⿪(laser on)
												case 5: laser = 0; break;  //�����(laser off)
											}
									break;
											
			  case 'X':xyz[X_AXIS] = value;Xe=value;break;
				case 'Y':xyz[Y_AXIS] = value;Ye=value;break;
        
			  case 'I':ijk[X_AXIS] = value;break;
				case 'J':ijk[Y_AXIS] = value;break;	
			
			}
		}
		
			//���¼��⿪��ʹ��(Enable/disenable the laser)
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
						        break; // G0 ���ٶ�λ (fast locating)
						case 1: interpolation(); 
						        break; // G1 ֱ�߲岹 (linear interpolation)
						case 2: //runcw();
       							break; // G2 ˳ʱ��Բ���岹 (circular interpolation not available)
						case 3: //runccw();
         						break; // G3 ��ʱ��Բ���岹	(circular interpolation not available)
						case 4: //runline();
       							break; // G75 �ص����0�� (not available)
					}
//printf("G=%d\r\n\r\n",motion);
//printf("X=%f\r\n\r\n",xyz[X_AXIS]);//�ø���
//printf("Y=%f\r\n\r\n",xyz[Y_AXIS]);//�ø���
	//printf("i=%f\r\n\r\n",ijk[X_AXIS]);//�ø���
	//printf("j=%f\r\n\r\n",ijk[Y_AXIS]);//�ø���



}

u8 read_float(u8 *line, u8 *char_counter, double *float_ptr) //��ȡ�ַ�����ָ���ַ���ʼ�ĸ������֣������������ַ�ֹͣ������ֵ��˫���ȸ����� value(seize float in the string)               
{
	u32 intval = 0;
  s8 exp = 0;
  u8 ndigit = 0;
	u8 c;
  double fval;
	bool isnegative = false; //������־λ
  bool isdecimal = false;  //С����־λ
	
  u8 *ptr = line + *char_counter;
  
  
  //���һ���ַ�������ָ�롣
  c = *ptr++;
  
  // ��׽�������/����
 
  if (c == '-') {
    isnegative = true;
    c = *ptr++;
  } else if (c == '+') {
    c = *ptr++;
  }
  
  // ��ȡ������������С��


  while(1) {
    c -= '0';  //���ַ�ת��Ϊ���� ��ֵ��c
    if (c <= 9) {
      ndigit++;
      if (MAX_INT_DIGITS <= 12) { //�ж��Ƿ����λ��
        if (isdecimal) { exp--; }  //�����С��
        intval = (((intval << 2) + intval) << 1) + c; // intval*10 + c  �����ƽ�ʡʱ��
      } else {
        if (!(isdecimal)) { exp++; }  //���û��С��
      }
    }
		else if (c == (('.'-'0') & 0xff)  &&  !(isdecimal)) {
      isdecimal = true;
    } else {
      break;
    }
    c = *ptr++;
  }
  
  // ���û�������� ���ؼ�
  if (!ndigit) { return(false); };
  
  //  ����ת���ɸ�������

  fval = (double)intval; //ǿ��ת��
  
	//Ӧ��С����Ӧִ�еĲ�������������˷� 
  // E0��E-4��Ԥ�ڷ�Χ��
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
  }   //����С�����λ�� 

  //   ָ������ֵ����ȷ�ı�־��
  if (isnegative) {
    *float_ptr = -fval;
  } else {
    *float_ptr = fval;
  }

  *char_counter = ptr - line - 1; //  ����char_counter����һ�����
  
  return(true);
}
