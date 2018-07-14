#include "stdio.h" 
#include "math.h"
#include "windows.h"

#include "stdlib.h"


int i,X,Y,X0,Y0,Xe,Ye,F,N,step;
int a[30][2];

void main()
{ 
	int m; 
	int menu();//函数声明
	void yi();
	void er();
	void san();
	void si();
	void te(); 
	void shuchu();
 
	m=menu();
	a[0][0]=X0;
	a[0][1]=Y0;

	switch(m)
	{ 
	 	case 1:yi();shuchu();break;
		case 2:er();shuchu();break;
		case 3:san();shuchu();break;
		case 4:si();shuchu();break;
		case 5:te();shuchu();break;
		default:printf("无法插补\n");
	}
	system("Pause");
}

int menu()
{ 
	int t; 
	printf("输入起点坐标\n");
	scanf("%d,%d",&X0,&Y0);
	printf("输入终点坐标\n");
	scanf("%d,%d",&Xe,&Ye);

	if (Xe>X0&&Ye>Y0)//第一象限
		t=1;
	else if (Xe<X0&&Ye>Y0)//第二象限
		t=2; 
	else if (Xe<X0&&Ye<Y0)//第三象限
		t=3; 
	else if (Xe>X0&&Ye<Y0)//第四象限
		t=4; 
	else if ((Xe==X0)||(Ye==Y0))//
		t=5;
	else 
		t=6; 
		return(t);
}

void yi()
{ 
	F=0;  
	N=Xe-X0+Ye-Y0;//X轴+Y轴走的总步数
	X=X0;
	Y=Y0;

	for(i=1;i<=N;i++)
	{
		if(F>=0)
		{
			X++; 
    		a[i][0]=X;
    		a[i][1]=Y;
    		F-=Ye-Y0;
    	}else
    	{
    		Y++; 
			a[i][0]=X;
			a[i][1]=Y;
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
    		a[i][0]=X;
    		a[i][1]=Y;
    		F-=Ye-Y0;
    	}else
    	{
    		Y++; 
			a[i][0]=X;
			a[i][1]=Y;
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
			a[i][0]=X;
			a[i][1]=Y;
			F-=Y0-Ye;
		}else
		{
			Y--;
			a[i][0]=X;
			a[i][1]=Y;
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
			a[i][0]=X;
			a[i][1]=Y;
			F-=Y0-Ye;
		}else
		{
			Y--;
			a[i][0]=X;
			a[i][1]=Y;
			F+=Xe-X0;
		}
	}
}

void te()
{ 
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
			a[i][0]=X;
			a[i][1]=Y;
	   }
	}
	else
	{
	  for(i=1;i<=step;i++)
	    {
			Y++;
			a[i][0]=X;
			a[i][1]=Y;	
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
			a[i][0]=X;
			a[i][1]=Y;
	   }
	}
	else
	{
	  for(i=1;i<=step;i++)
	    {
			X++;
			a[i][0]=X;
			a[i][1]=Y;	
    	}
	}
   }
}

void shuchu()
{
	for(i=0;i<=N;i++)
	{
		printf("%d ",i); 
		printf("%d,%d\n",a[i][0],a[i][1]);
	}
} 
