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

基本要求
（1）电动车从起始端 A 出发，在 30 秒钟内行驶到中心点 C 附近； 
（2）60 秒钟之内，电动车在中心点 C 附近使跷跷板处于平衡状态，保持平衡 5 秒钟，并给出明显的平衡指示； 
（3）电动车从（2）中的平衡点出发，30 秒钟内行驶到跷跷板末端 B 处（车 头距跷跷板末端 B 不大于 50mm）；
（4）电动车在 B 点停止 5 秒后，1 分钟内倒退回起始端 A，完成整个行程；
（5）在整个行驶过程中，电动车始终在跷跷板上，并分阶段实时显示电动车 行驶所用的时间。
发挥部分
（1）从板外爬上跷跷板。
（2）电动车在跷跷板上取得平衡，给出明显的平衡指示，保持平衡 5 秒钟以 上；
（3）将另一块质量为电动车质量 10％～20％的块状配重放置在 A 至 C 间指 定的位置，电动车能够重新取得平衡，给出明显的平衡指示，保持平衡 5 秒钟以 上；
（4）电动车在 3 分钟之内完成（1）～（3）全过程。 
（5）其他。
*/


int left,mid_l,mid_r,right;
int states;
int flag=0;
float a[10]={0};
float filPitch=0.00;
int OUT;
int KP=10,KI=0,KD=0;
int temp=0;


int Position_PID(int Encoder , int Target);


void data_collection()//数据采集；简单处理；
{
	left =LED_1_out;
	mid_l=LED_2_out;
	mid_r=LED_3_out;
	right=LED_4_out;
	//printf("left=%d,mid_l=%d,mid_r=%d,right=%d \n",left,mid_l,mid_r,right);

	Read_DMP();
	//printf ("Pitch=%f \n",Pitch);
//以上为数据采集
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
}


void Line_inspection()//巡线
{
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
}


void Overall_process()
{
	if(filPitch> 1 )
	{
		if(OUT>100)OUT=100;
		if(OUT<45)OUT=45;
		Car_Fore(OUT);
		flag=3;
	}
	if(filPitch< -1 )
	{
		OUT=-OUT;
		if(OUT>100)OUT=100;
		if(OUT<45)OUT=45;
		Car_Back(OUT);
		flag=4;
	}

	// if(filPitch==0)
	// {
	// 	states=4;//读数为0直接停车
	// }

	// OUT=Position_PID(filPitch , 0);

	// if((flag==0)&(left==0)&(mid_l==1)&(mid_r==1)&(right==0))
	// {
	// 	states=3;//直行
	// }
	// printf("flag=%d,OUT=%d,filPitch=%f \n",flag,OUT,filPitch);

	// states=3;
	// delay_ms(1000);
	// states=4;
	// delay_ms(4000);
	// states=3;
	// delay_ms(1000);
	

}


#if 0
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
	OUT=Position_PID(filPitch , 0);
	printf("flag=%d,OUT=%d,filPitch=%f \n",flag,OUT,filPitch);

	if(filPitch>10)
	{
		flag=3;//上板标志
		if(flag==4)
		{
			flag=4;
		}
	}
	if((flag==3)&(left==1)&(mid_l==1)&(mid_r==1)&(right==1))//全压黑线过A点
	{
		flag=4;//过第一条黑线标志
		if((flag!=4)|(filPitch>10))//检查
		{
			flag=4;
		}
	}
	if((flag==3)&(filPitch!=0))
	{
		if(filPitch> 1 )
		{
			if(OUT>100)
			{
				OUT=100;
			}
			if(OUT<45)
			{
				OUT=45;
			}
			PWMA_UP(OUT);
			PWMB_UP(OUT);
			flag=5;
		}
		if(filPitch< -1 )
		{
			OUT=-OUT;
			if(OUT>100)
			{
				OUT=100;
			}
			if(OUT<45)
			{
				OUT=45;
			}
			PWMA_BACK(OUT);
			PWMB_BACK(OUT);
			flag=6;
		}
	}
#endif
}
#endif


int Position_PID(int Encoder , int Target)
{
	static float Bias,Pwm,Intergral_Bias,Last_Bias;

	Bias=Encoder-Target;
	Intergral_Bias+=Bias;
	Pwm=KP*Bias+KI*Intergral_Bias+KD*(Bias-Last_Bias);
	Last_Bias=Bias;
	return Pwm;
}

