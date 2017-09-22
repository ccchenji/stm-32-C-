#include <PWM_12.h>
void PWM_port()
{
    CCON=0;
	CL=0;
	CH=0;
	CMOD=0X02;//可以调节PWM的输出频率（此时的晶振频率为SYSclk/2)

	CCAP0H=CCAP0L=0X80;//调节PWM0的占空比（此时的占空比为50%）（P1^3口输出）
	CCAPM0=0X42;//配置CCAPM0为脉宽调节模式
	//PCAPWM0=0X03;

    CCAP1H=CCAP1L=0XFF;//调节PWM1的占空比（此时为0%）（P1^4口输出）
	PCAPWM1=0X03;
	CCAPM1=0X42;//配置CCAPM1为脉宽调节模式
	CR=1;//打开PCA
}
/**************************PWM的频率计算方式************************
 ***************PWM的频率=PCA时钟输入源频率/256*********************/


/*******************调节占空比的函数*********************************/
void PWM_change(unsigned char a)
{
  CCAP0H=255-a;  
  CCAP0L=CCAP0H;
}
//CCAP0H的值等于255-255*占空比/100              