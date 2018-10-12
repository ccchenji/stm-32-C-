#include "AD.h"
/**************************ADC初始化函数********************************/
void InitADC()
{
   ADC_CONTR=0XC8;//没180个时钟周期转换一次，选P1^0口作为AD输入来用
	 P1ASF=0X01;//P1^0口作为模拟ADC功能使用（采集这个引脚的数据）
//	 EA=1;//打开总中断
//	 IE=0XB0;//打开ADC中断
	 ADC_RES=0;//清除原来的数据
	 ADC_RESL=0;  
	 _nop_;
	 _nop_;
	 _nop_;
	 _nop_;
	 _nop_;  
}
/**************************得到ADC的值**********************************/
int AD_get()
{
    static  unsigned int i=0;
	  static	double k=0;
    while(!(ADC_CONTR&0x10));   		//等待转换完成
	  i=ADC_RES;							//取高八位
	  i=i<<2;								
	  i=i|ADC_RESL;						//取低二位
	  ADC_CONTR=0XC8;//初始化
  	return i;
}