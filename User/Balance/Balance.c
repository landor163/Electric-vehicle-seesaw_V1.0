#include "Balance.h"
#include "System.h"
#include "stm32f10x.h"
#include "MPU6050.h"
#include "TB6612.h"
#include "bsp_GeneralTim_3.h" 
#include "stm32f10x.h"


double PID_Position (PID *pid , int TarVal , int StaVal)
{
	int ParErr,//局部当前误差
		Out;//实际输出
	
	ParErr = TarVal - StaVal;
	pid->Error += pid->Int * ParErr;//可以适当限幅，但是我没有
	Out = pid->Pro * ParErr
		+ pid->Error
		+ pid->Der * (ParErr - pid->LastErr);

	return Out;
}

