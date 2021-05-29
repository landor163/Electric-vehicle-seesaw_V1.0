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


/*
左47右50简单为直线

||或
&&与

涉及标志位赋值的，判定条件就要加上上一个标志位的情况

调试理想环境要绝对的理想，不要自己骗自己

压线为1，不压为0
压线灭灯，不压亮灯
*/


int left,mid_l,mid_r,right,states;
static int flag=0;


void Follow_line()
{
	left =LED_1_out;
	mid_l=LED_2_out;
	mid_r=LED_3_out;
	right=LED_4_out;
	if((flag!=1)&(mid_l==1)&(right==0))//右偏
	{
		states=1;//左慢右快
	}
	if((flag!=1)&(mid_r==1)&(left==0))//左偏
	{
		states=2;//左快右慢
	}
}

void Plan_A(void)
{
	#if 1
	printf("flag=%d\n",flag);
	
	if((flag==0)&(left==0)&(mid_l==0)&(mid_r==0)&(right==0))//都不压线 且 flag为0
	{
		Car_Fore(50);//直行 不循线的
		flag=1;
	}

	if((flag==1)&(left==1)|(mid_l==1)|(mid_r==1)|(right==1))//flag为0 且 有一个压了线
	{
		flag=2;//开始巡线模式
	}
	if((flag==1)&(left==1)&(mid_l==1)&(mid_r==1)&(right==1))//全压黑线过A点
	{
		//第一次识别到黑线，也就是A点
		Car_Fore(50);		
		SysTick_Delay_Ms(1000);
		Car_Stop();
		flag=2;
	}

	switch(states)//电机控制状态
	{
		case 1: PWMA_UP(47-20),PWMB_UP(50+20);break;//左转
		case 2: PWMA_UP(47+20),PWMB_UP(50-20);break;//右转
		case 3: PWMA_UP(47),PWMB_UP(50);break;//直行
		case 4: PWMB_STOP(),PWMA_STOP();break;//停车
	}
	#endif
/*==========================================================================================================================================================================*/			
	#if 0	//测试红外传感器阈值
	int left,mid_l,mid_r,right;
	
	left=LED_1_out;
	mid_l=LED_2_out;
	mid_r=LED_3_out;
	right=LED_4_out;
	
	printf("left=%d,mid_l=%d,mid_r=%d,right=%d \n",left,mid_l,mid_r,right);
	#endif
	
	#if 0
	PWMA_UP(47);
	PWMB_UP(50);
	#endif
	
	#if 0	//角度
	Read_DMP();
	printf ("Pitch=%f \n",(Pitch-3.5));
	#endif
}

