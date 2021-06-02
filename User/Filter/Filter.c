#include "Filter.h"


/*======================================================================
限幅滤波法

优点：能有效克服因偶然因素引起的脉冲干扰
缺点：无法抑制周期性干扰；平滑度查

输入量：x 为采集值
       A 为最大偏差值
输出量：sample_value为滤波后的采集值
======================================================================*/
int Limit_Filter(int x,int A)
{
    static int sample_value,last_value;

    sample_value=x;
    last_value=sample_value;
    
    if( (sample_value-last_value)<=A )
    {

    }
    else
    {
        sample_value=last_value;
    }

    return sample_value;
}

