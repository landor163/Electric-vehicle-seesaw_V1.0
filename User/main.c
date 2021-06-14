#include "stm32f10x.h"
#include "TB6612.h"
#include "bsp_GeneralTim_3.h" 
#include "bsp_usart.h"
#include "System.h" 
#include "Balance.h"
#include "MPU6050.h"
#include "Buzzer.h"
#include "bsp_Find_Num.h"
#include "Control_Flow.h"
#include "bsp_SysTick.h"
#include "Filter.h"


int main(void)
{
	delay_init(72);
	
	AIN1_GPIO_Config();
	AIN2_GPIO_Config();
	BIN1_GPIO_Config();
	BIN2_GPIO_Config();
	GENERAL_TIM_3_Init();
	
	Buz_GPIO_Config();
	
	USART_Config();
	
	Find_Nun_Init();
	
	IIC_Init();
	MPU6050_initialize();
	DMP_Init();	
	while(1)
	{
		data_collection();
		//Line_inspection();
		Overall_process();
	}
}

