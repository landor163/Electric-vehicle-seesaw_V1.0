#include "Control_Flow.h"
#include "stm32f10x.h"
#include "bsp_Find_Num.h"
#include "bsp_usart.h"
#include "MPU6050.h"
#include "TB6612.h"
#include "bsp_GeneralTim_3.h" 
#include "Buzzer.h"
#include "Delay.h"
#include "bsp_SysTick.h"
#include "Filter.h"


/*
调试理想环境要绝对的理想，不要自己骗自己
*/


int left,mid_l,mid_r,right,states;
int flag=0;
float a[10]={0};
int temp=0;
float filPitch=0.00;
int OUT;
int KP=10,KI=0,KD=0;

int Position_PID(int Encoder , int Target);

void Plan_A(void)
{
#if 1
/*
以下为数据采集；俯仰角在地面上水平为 2.7 ，车头抬高读数变大，车尾抬高读数变小；20秒后数据稳定，波动中数据没上 5；车头向北为 2.9，车头向东为 3.2；
在板上数据范围从 11.2到 -4.3 之间；板子平衡时数值为 0；
*/
	left =LED_1_out;
	mid_l=LED_2_out;
	mid_r=LED_3_out;
	right=LED_4_out;
	//printf("left=%d,mid_l=%d,mid_r=%d,right=%d \n",left,mid_l,mid_r,right);

	Read_DMP();
	//printf ("Pitch=%f \n",Pitch);

	for (int i = 0; i < 10; i++)
	{
		a[i]=Pitch;
	}
	for(int i=0;i<10;i++)
	{
		if(a[i]>a[i+1])
		{
			temp=a[i];
            a[i]=a[i+1];
            a[i+1]=temp;
		}
	}
	filPitch = (a[4]+a[5])/2;
	//printf ("filPitch=%f \n",filPitch);
	OUT=Position_PID(filPitch , 0);
	printf("OUT=%d,filPitch=%f \n",OUT,filPitch);
#endif


#if 1
/*
以下为一个简单的巡线程序；压线为1，不压为0；压线灭灯，不压亮灯；一开始没有找到线所有灯全亮，未压线。
*/
	if((flag==0)&(left==0)&(mid_l==0)&(mid_r==0)&(right==0))
	{
		states=3;//直行
	}
	if((mid_l==1)&(right==0))//右偏
	{
		states=1;//左转
		flag=1;
	}
	if((mid_r==1)&(left==0))//左偏
	{
		states=2;//右转
		flag=2;
	}
	
	switch(states)//电机控制状态
	{
		case 1: PWMA_UP(47-20),PWMB_UP(50+20);break;//左转
		case 2: PWMA_UP(47+20),PWMB_UP(50-20);break;//右转
		case 3: PWMA_UP(47),PWMB_UP(50);break;//直行
		case 4: PWMB_STOP(),PWMA_STOP();break;//停车
		case 5: PWMA_BACK(50);PWMB_BACK(50);break;//倒车
	}
	//printf("flag=%d \n",flag);
#endif


#if 1
/*
以下为在跷跷板上自平衡程序；
电机死区计算，电池输出 7.72V 时
A UP 45自己能动 40自己就动不了了    BACK 45凑活 40一点都不动
B UP 50劲很大 40垃圾的不行 45也不错 BACK 40也不行 45很好
*/
	if(filPitch>10)
	{
		flag=3;//上板标志
	}
	if((flag==3)&(left==1)&(mid_l==1)&(mid_r==1)&(right==1))//全压黑线过A点
	{
		flag=4;//过第一条黑线标志
	}
	if(flag==4)
	{
		if(filPitch> 1 )
		{
			PWMA_UP(OUT);
			PWMB_UP(OUT);
		}
		if(filPitch< -1 )
		{
			OUT=-OUT;
			PWMA_BACK(OUT);
			PWMB_BACK(OUT);
		}
	}
#endif
}

int Position_PID(int Encoder , int Target)
{
	static float Bias,Pwm,Intergral_Bias,Last_Bias;

	Bias=Encoder-Target;
	Intergral_Bias+=Bias;
	Pwm=KP*Bias+KI*Intergral_Bias+KD*(Bias-Last_Bias);
	Last_Bias=Bias;
	return Pwm;
}

