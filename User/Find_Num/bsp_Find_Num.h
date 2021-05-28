#ifndef  _BSP_FIND_NUM_H
#define  _BSP_FIND_NUM_H

#include "stm32f10x.h"


//********************红外循迹模块IO配置（数字量）*****************//
// led 	1 
#define LED_1_GPIO_PORT   GPIOB
#define LED_1_GPIO_CLK    RCC_APB2Periph_GPIOB
#define LED_1_GPIO_PIN    GPIO_Pin_9

// led 	2
#define LED_2_GPIO_PORT   GPIOB
#define LED_2_GPIO_CLK    RCC_APB2Periph_GPIOB
#define LED_2_GPIO_PIN    GPIO_Pin_8 

// led	3 
#define LED_3_GPIO_PORT   GPIOB
#define LED_3_GPIO_CLK    RCC_APB2Periph_GPIOB
#define LED_3_GPIO_PIN    GPIO_Pin_4

// led 	4 
#define LED_4_GPIO_PORT   GPIOB
#define LED_4_GPIO_CLK    RCC_APB2Periph_GPIOB
#define LED_4_GPIO_PIN    GPIO_Pin_5

// led 	5 
#define LED_5_GPIO_PORT   GPIOB
#define LED_5_GPIO_CLK    RCC_APB2Periph_GPIOB
#define LED_5_GPIO_PIN    GPIO_Pin_6

//分别检测各路输入
#define LED_1_out  GPIO_ReadInputDataBit( LED_1_GPIO_PORT, LED_1_GPIO_PIN);
#define LED_2_out  GPIO_ReadInputDataBit( LED_2_GPIO_PORT, LED_2_GPIO_PIN);
#define LED_3_out  GPIO_ReadInputDataBit( LED_3_GPIO_PORT, LED_3_GPIO_PIN);
#define LED_4_out  GPIO_ReadInputDataBit( LED_4_GPIO_PORT, LED_4_GPIO_PIN);
#define LED_5_out  GPIO_ReadInputDataBit( LED_5_GPIO_PORT, LED_5_GPIO_PIN);


void Find_Nun_Init(void);				//初始化红外循迹模块

#endif
