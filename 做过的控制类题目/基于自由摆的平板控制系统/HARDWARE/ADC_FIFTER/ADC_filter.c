#include "ADC_filter.h"
#include "adc.h"
#include "math.h"
#define N 10
float Last_num=0;
float New_num=0;
float value_buf[N];
float value_buf2[N];
short timer=0;
//平滑中位值平均滤波
float MyADC_filter()
{
	 short i=0;
	 short j=0;
	 float temp=0;
	 float sum=0;
	for(i=1;i<N;i++)
	  {
			value_buf[i-1]=value_buf[i];
	  }
		value_buf[N-1]=Get_Adc(ADC_Channel_1);
		for(i=0;i<N;i++)
		{
			 value_buf2[i]=value_buf[i];
		}
//冒泡排序法
	for(j=0;j<N-1;j++)
	{
		 for(i=0;i<N-j-1;i++)
		 {
			  if(value_buf2[i]>value_buf2[i+1])
				{
					  temp=value_buf2[i];
					  value_buf2[i]=value_buf2[i+1];
					  value_buf2[i+1]=temp;
				}
		 }
	}
	for(i=1;i<N-1;i++)
	{
		 sum+=value_buf2[i];
	}
	return sum/(N-2);
}


