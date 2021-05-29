#ifndef TB6612_H
#define TB6612_H


#include "stm32f10x.h"


/*B0端口*/
#define AIN1_GPIO_PIN		GPIO_Pin_0
#define AIN1_GPIO_PORT  	GPIOB
#define AIN1_GPIO_CLK		RCC_APB2Periph_GPIOB

/*输出高电平*/
#define AIN1_ON			GPIO_SetBits(AIN1_GPIO_PORT,AIN1_GPIO_PIN)
/*输出低电平*/
#define AIN1_OFF		GPIO_ResetBits(AIN1_GPIO_PORT,AIN1_GPIO_PIN)


/*B1端口*/
#define AIN2_GPIO_PIN		GPIO_Pin_1
#define AIN2_GPIO_PORT	GPIOB
#define AIN2_GPIO_CLK		RCC_APB2Periph_GPIOB

/*输出高电平*/
#define AIN2_ON			GPIO_SetBits(AIN2_GPIO_PORT,AIN2_GPIO_PIN)
/*输出低电平*/
#define AIN2_OFF		GPIO_ResetBits(AIN2_GPIO_PORT,AIN2_GPIO_PIN)


/*B10端口*/
#define BIN1_GPIO_PIN		GPIO_Pin_10
#define BIN1_GPIO_PORT	GPIOB
#define BIN1_GPIO_CLK		RCC_APB2Periph_GPIOB

/*输出高电平*/
#define BIN1_ON			GPIO_SetBits(BIN1_GPIO_PORT,BIN1_GPIO_PIN)
/*输出低电平*/
#define BIN1_OFF		GPIO_ResetBits(BIN1_GPIO_PORT,BIN1_GPIO_PIN)


/*B11端口*/
#define BIN2_GPIO_PIN		GPIO_Pin_11
#define BIN2_GPIO_PORT	GPIOB
#define BIN2_GPIO_CLK		RCC_APB2Periph_GPIOB

/*输出高电平*/
#define BIN2_ON			GPIO_SetBits(BIN2_GPIO_PORT,BIN2_GPIO_PIN)
/*输出低电平*/
#define BIN2_OFF		GPIO_ResetBits(BIN2_GPIO_PORT,BIN2_GPIO_PIN)


void AIN1_GPIO_Config(void);
void AIN2_GPIO_Config(void);

void BIN1_GPIO_Config(void);
void BIN2_GPIO_Config(void);


void PWMA_UP(int a);
void PWMA_BACK(int a);
void PWMA_STOP(void);
void PWMB_UP(int a);
void PWMB_BACK(int a);
void PWMB_STOP(void);

void Car_Fore(int a);
void Car_Stop(void);
#endif

