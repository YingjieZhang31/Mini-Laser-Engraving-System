#include "interpolation.h"
#include "sys.h"
#include "usart.h"
#include "executeX.h"
#include "executeY.h"
#include "executeTE.h"
#include "math.h"
//#include "stdio.h"

extern s32 X0,Y0; //当前XY坐标
extern s32 Xe,Ye; //目标XY坐标

int i,X,Y,F,N;
int flag=0;    //判断行走方向
//int a[30][2];

void interpolation()
{
  int m;
	int menu();
	void yi();//1st quadrant linear interpolation
	void er();//2nd quadrant linear interpolation
	void san();//3rd quadrant linear interpolation
	void si();//4th quadrant linear interpolation
	void te(); //exceptional case(the line from starting point to terminal parallels to coordinate axis):linear interpolation
	//void shuchu();
	
  m=menu();
//	a[0][0]=X0;
//	a[0][1]=Y0;
	
		switch(m)
	{ 
	 	case 1:flag=1;yi();//shuchu();//first quadrant
		break;
		case 2:flag=2;er();//shuchu();//second quadrant
		break;
		case 3:flag=3;san();//shuchu();//third quadrant
		break;
		case 4:flag=4;si();//shuchu();//forth quadrant
		break;
		case 5:flag=5;te();//shuchu();//parallel to coordinate axis
		break;
		case 6:flag=0;printf("无法插补.Error!\n");
	}
	
}

int menu()
{
	int t; 
/*	printf("输入起点坐标\n");
	scanf("%d,%d",&X0,&Y0);
	printf("输入终点坐标\n");
	scanf("%d,%d",&Xe,&Ye);?
*/
	if (Xe>X0&&Ye>Y0)//第一象限(1st quadrant)
		t=1;
	else if (Xe<X0&&Ye>Y0)//第二象限(2nd quadrant)
		t=2; 
	else if (Xe<X0&&Ye<Y0)//第三象限(3rd quadrant)
		t=3; 
	else if (Xe>X0&&Ye<Y0)//第四象限(4th quadrant)
		t=4; 
	else if ((Xe==X0)||(Ye==Y0))//exceptional case
		t=5;
	else //error
		t=6; 
		return(t);
}

void yi()
{ 
	F=0;  
	N=Xe-X0+Ye-Y0;//X轴+Y轴走的总步数(total step number)
	X=X0;
	Y=Y0;

	for(i=1;i<=N;i++)
	{
		if(F>=0)
		{
			X++; 
    //		a[i][0]=X;
    	//	a[i][1]=Y;
			executeX();
    		F-=Ye-Y0;
    	}else
    	{
    		Y++; 
	//		a[i][0]=X;
		//	a[i][1]=Y;
				executeY();
			F+=Xe-X0;
		}
	}
}

void er()
{ 
	F=0;  
	N=X0-Xe+Ye-Y0;
	X=X0;
	Y=Y0;

	for(i=1;i<=N;i++)
	{
		if(F>=0)
		{
			X--; 
			executeX();
    	//	a[i][0]=X;
    	//	a[i][1]=Y;
    		F-=Ye-Y0;
    	}else
    	{
    		Y++; 
				executeY();
	//		a[i][0]=X;
	//		a[i][1]=Y;
			F+=X0-Xe;
		}
	}
}

void san()
{ 
	F=0;
	N=X0-Xe+Y0-Ye;
	X=X0;
	Y=Y0;

	for(i=1;i<=N;i++)
	{
		if(F>=0)
		{
			X--;
			executeX();
		//	a[i][0]=X;
		//	a[i][1]=Y;
			F-=Y0-Ye;
		}else
		{
			Y--;
			executeY();
	//		a[i][0]=X;
		//	a[i][1]=Y;
			F+=X0-Xe;
		}
	}
}

void si()
{ 
	F=0;
	N=Xe-X0+Y0-Ye;
	X=X0;
	Y=Y0;

	for(i=1;i<=N;i++)
	{
		if(F>=0)
		{
			X++;
			executeX();
	//		a[i][0]=X;
	//		a[i][1]=Y;
			F-=Y0-Ye;
		}else
		{
			Y--;
			executeY();
		//	a[i][0]=X;
		//	a[i][1]=Y;
			F+=Xe-X0;
		}
	}
}

void te()
{ 
	int step;
	X=X0;
	Y=Y0;
  if(Xe==X0)
  {
	N=Ye-Y0;
	step=abs(N);
	if(N<0)
	{
	  for(i=1;i<=step;i++)
	   {
			Y--;
	    Yfan();		 
	//		a[i][0]=X;
	//		a[i][1]=Y;
	   }
	}
	else
	{
	  for(i=1;i<=step;i++)
	    {
			Y++;
				Yzheng();
	//		a[i][0]=X;
	//		a[i][1]=Y;	
    	}
	}
  }
  else
   { 
	N=Xe-X0;
	step=abs(N);
	if(N<0)
	{
	  for(i=1;i<=step;i++)
	   {
			X--;
			 fan();
		//	a[i][0]=X;
		//	a[i][1]=Y;
	   }
	}
	else
	{
	  for(i=1;i<=step;i++)
	    {
			X++;
				zheng();
	//		a[i][0]=X;
	//		a[i][1]=Y;	
    	}
	}
   }
}

/*void shuchu()
{
	for(i=0;i<=N;i++)
	{
		printf("%d\n",i); 
	//	printf("%d,%d\n\r",a[i][0],a[i][1]);
	}
} 
*/
