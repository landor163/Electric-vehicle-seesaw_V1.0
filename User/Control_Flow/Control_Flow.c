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
调试细节，光电管调整到刚好可以识别到白光的阈值
压线，灭灯，为1；
不压线，为0；

左47右50简单为直线

||或
&&与

涉及标志位赋值的，判定条件就要加上上一个标志位的情况
*/


void Plan_A(void)
{
	
	int left,mid_l,mid_r,right;

	static int flag,states;

	left =LED_1_out;
	mid_l=LED_2_out;
	mid_r=LED_3_out;
	right=LED_4_out;
	#if 1
	if((flag==0)&(left==0)&(mid_l==0)&(mid_r==0)&(right==0))//都不压线
	{
		states=3;//直行
	}
	if((flag==0)&(left==1)|(mid_l==1)|(mid_r==1)|(right==1))//有一个压了线
	{
		flag=1;
	}
	if((flag==1)&(mid_l==1)&(right==0))//右偏
	{
		states=1;//左慢右快
		if(states==1)
		{
			flag=3;
		}
	}
	if((flag==1)&(mid_r==1)&(left==0))//左偏
	{
		states=2;//左快右慢

	}
	if((flag==1)&(left==1)&(mid_l==1)&(mid_r==1)&(right==1))//全压黑线过A点
	{
		states=3;
		//delay_ms(1000);
		SysTick_Delay_Ms(1000);
		flag=2;
	}
	if((flag==2)&(left==1)&(mid_l==1)&(mid_r==1)&(right==1))//第二次全压黑线
	{
		states=4;
	}
	#endif

	printf("flag=%d\n",flag);

	switch(states)
	{
		case 1: PWMA_UP(47-20),PWMB_UP(50+20);break;
		case 2: PWMA_UP(47+20),PWMB_UP(50-20);break;
		case 3: PWMA_UP(47),PWMB_UP(50);break;
		case 4: PWMB_STOP(),PWMA_STOP();break;
	}
/*=================================================================================================================================================================================*/			
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
	printf ("Pitch=%f \n",Pitch)；
	#endif
}

