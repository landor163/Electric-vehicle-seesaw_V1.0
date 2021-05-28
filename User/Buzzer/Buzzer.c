#include "stm32f10x.h"
#include "Buzzer.h"
#include "Delay.h"


void Buz_GPIO_Config(void)
{
	GPIO_InitTypeDef		GPIO_InitStruct;

	RCC_APB2PeriphClockCmd(Buz_GPIO_CLK,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = Buz_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(Buz_GPIO_PORT,&GPIO_InitStruct);
}

void BEEP(int x)
{
	Buz_ON;
	delay_ms(x);
	Buz_OFF;
	delay_ms(x);
	Buz_ON;
}

