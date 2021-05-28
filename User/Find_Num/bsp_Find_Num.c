#include "bsp_Find_Num.h"

void Find_Nun_Init()
{
	GPIO_InitTypeDef  GPIO_InitStruct;																					 //定义一个 GPIO_InitTypeDef 类型的结构体
	RCC_APB2PeriphClockCmd(LED_1_GPIO_CLK|LED_2_GPIO_CLK|LED_3_GPIO_CLK|LED_4_GPIO_CLK|LED_5_GPIO_CLK, ENABLE);//开启led对应GPIO的时钟
	GPIO_InitStruct.GPIO_Pin = LED_1_GPIO_PIN|LED_2_GPIO_PIN|LED_3_GPIO_PIN|LED_4_GPIO_PIN|LED_5_GPIO_PIN;//设置需要控制的GPIO引脚
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;																 //设置为下拉电阻输入
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;															 //设置GPIO速率
	
	GPIO_Init(LED_2_GPIO_PORT,&GPIO_InitStruct);
}

