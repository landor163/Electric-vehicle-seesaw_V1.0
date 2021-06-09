#include "Balance.h"
#include "System.h"
#include "stm32f10x.h"
#include "MPU6050.h"
#include "TB6612.h"
#include "bsp_GeneralTim_3.h" 
#include "stm32f10x.h"
/*
static int KP,KI,KD;

int Position_PID(int Encoder , int Target)
{
	static float Bias,Pwm,Intergral_Bias,Last_Bias;

	Bias=Encoder-Target;
	Intergral_Bias+=Bias;
	Pwm=KP*Bias+KI*Intergral_Bias+KD*(Bias-Last_Bias);
	Last_Bias=Bias;
	return Pwm;
}


int Incremental_PID(int Encoder , int Target)
{
	static float Bias,Pwm,Last_Bias;

	Bias=Encoder-Target;
	Pwm+=KP*(Bias-Last_Bias)+KI*Bias;
	Last_Bias=Bias;
	return Pwm;
}
*/
