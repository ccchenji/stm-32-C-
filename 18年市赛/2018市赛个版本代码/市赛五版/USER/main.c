/*---------------前有神兽镇楼，后有佛祖保佑，我就不信还有bug------------------------------------*/
/**********************************************************************************************
*      +--+          +-+  + +
*      |  +          + +
*    + |       +  +
*  +-+ +-------+  +-+  +  +
*  |                +
*  |                        +
*  |            +--+        +
*  |                       +
*XXXXXXXX   XXXXXXXX   +   |  +-+   ++  +-+
*XXXXXXXX+--XXXXXXXX   | + +
*XXXXXXXX   XXXXXXXX   +
*  +                       +
*  |          +          + + +
*  |         -+-         |
*  |                     + +
*  |                  +    + ++
*  +---+          +---+
*      + +        +
*        |           +
*        |           |
*        |           |   ++  ++  ++
*        |           |
*        |           |
*        |           |   ++
*        |           |
*        |           |             Code is far away from bug with the animal protecting
*        |           |             神兽保佑代码无bug
*        |           |
*        |           +  +
*        |              +----+  +-+
*        |                   |    +-+
*        |                        + |
*        |                          |
*        |                        +-+
*        |                    +   +
*        +--+ ++ +-----+-+  +-+
*           +  + +     + +  +     ++   +-+    +-+ +-+
*             + + +       +  + +
*             | | |       |  | |
*             +---+       +----+
*             + + +       +  + +  ++   +-+  +--+   +-+
*************************************************************************************************/
#include "stm32f10x.h"
#include "menu.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "FDC2214.h"
#include "IIC.h"
#include "send.h"
#include "key.h"
#include "math.h"
#include "fliter.h"
#include "dealDate.h"
#include "OLED.H"
#include "timer.h"

//开机参数
int openData=14700000;
int openErr=60000;
int openTime=25;

extern MenuPage firstPage;//页面一
uint32_t date0, date1, date2, date3;
uint32_t fre0, fre1, fre2, fre3;
/*-----------------------------图标-------------------------------------------*/
unsigned char gImage_school[518] = { //0XC0,0X01,0X40,0X00,0X40,0X00,
0X00,0X00,0X00,0X1F,0XF8,0X00,0X00,0X00,0X00,0X00,0X01,0XFF,0XFF,0X80,0X00,0X00,
0X00,0X00,0X0F,0XFF,0XFF,0XF0,0X00,0X00,0X00,0X00,0X7F,0XFF,0XFF,0XFE,0X00,0X00,
0X00,0X01,0XFF,0XF8,0X1F,0XFF,0X80,0X00,0X00,0X07,0XFE,0X00,0X00,0X7F,0XE0,0X00,
0X00,0X0F,0XF0,0X00,0X00,0X0F,0XF0,0X00,0X00,0X0F,0XC0,0X00,0X00,0X03,0XF0,0X00,
0X00,0X1F,0X80,0X00,0X00,0X01,0XF8,0X00,0X00,0X3E,0X00,0X00,0X00,0X00,0X7C,0X00,
0X00,0X7C,0X00,0X00,0X00,0X00,0X3E,0X00,0X00,0XF8,0X00,0X00,0X00,0X00,0X1F,0X00,
0X03,0XF0,0X00,0X08,0X20,0X00,0X0F,0XC0,0X07,0XE0,0X00,0XEE,0X77,0X00,0X07,0XE0,
0X07,0XC0,0X00,0X76,0X6E,0X00,0X03,0XE0,0X0F,0X80,0X00,0X36,0X6C,0X00,0X01,0XF0,
0X0F,0X80,0X00,0X3F,0XFC,0X00,0X01,0XF0,0X1F,0X00,0X00,0X3F,0XFC,0X00,0X00,0XF8,
0X1E,0X00,0X00,0X3F,0XFC,0X00,0X00,0X78,0X1E,0X00,0X00,0X3F,0XFC,0X00,0X00,0X78,
0X3C,0X00,0X00,0X3F,0XFF,0XC0,0X00,0X3C,0X3C,0X00,0X00,0X3F,0XFF,0XF0,0X00,0X3C,
0X3C,0X00,0X00,0X3F,0XFF,0XF8,0X00,0X3C,0X78,0X00,0X00,0X3F,0XFE,0X38,0X00,0X1E,
0X78,0X00,0X00,0X3F,0XF8,0X18,0X00,0X1E,0X78,0X00,0X00,0X1F,0XF8,0X0C,0X00,0X1E,
0X78,0X00,0X00,0X1F,0XF8,0X06,0X00,0X1E,0XF8,0X00,0X01,0XFF,0XFF,0X03,0X00,0X1F,
0XF8,0X00,0X03,0XF8,0X1F,0XC0,0X00,0X1F,0XF0,0X00,0X0E,0X00,0X00,0X70,0X00,0X0F,
0XF1,0X00,0X1C,0X00,0X00,0X38,0X00,0X8F,0XF0,0X30,0X18,0X00,0X00,0X18,0X0C,0X0F,
0XF0,0X00,0X38,0X60,0X06,0X1C,0X00,0X0F,0XF0,0X38,0X38,0XE0,0X0E,0X1E,0X0C,0X0F,
0XF0,0X00,0X38,0XE0,0X0F,0X1E,0X00,0X0F,0XF8,0X00,0X78,0XE0,0X07,0X1E,0X00,0X1F,
0XF8,0X00,0X78,0XC0,0X02,0X1E,0X00,0X1F,0X78,0X00,0X78,0X00,0X00,0X1E,0X00,0X1E,
0X78,0X00,0X7C,0X00,0X00,0X3E,0X00,0X1E,0X78,0X00,0X7F,0X00,0X00,0XFE,0X00,0X1E,
0X78,0X00,0X7F,0XFF,0XFF,0XFE,0X00,0X1E,0X3C,0X00,0X3F,0XFF,0XFF,0XFE,0X00,0X3C,
0X3C,0X00,0X3F,0XFF,0XFF,0XFE,0X00,0X3C,0X3C,0X00,0X3F,0XFF,0XFF,0XFC,0X00,0X3C,
0X1E,0X00,0X1F,0XFF,0XFF,0XF8,0X00,0X78,0X1E,0X00,0X1F,0XFF,0XFF,0XF8,0X00,0X78,
0X1F,0X00,0X1F,0XFF,0XFF,0XF8,0X00,0XF8,0X0F,0X80,0X1F,0XFF,0XFF,0XF8,0X01,0XF0,
0X0F,0X80,0X1F,0XFF,0XFF,0XF8,0X01,0XF0,0X07,0XC0,0X1F,0XCF,0XF1,0XF8,0X03,0XE0,
0X07,0XE0,0X0F,0X80,0X00,0XF8,0X07,0XE0,0X03,0XF0,0X04,0X00,0X00,0X10,0X0F,0XC0,
0X00,0XF8,0X00,0X00,0X00,0X00,0X1F,0X00,0X00,0X7C,0X00,0X00,0X00,0X00,0X3E,0X00,
0X00,0X3E,0X00,0X00,0X00,0X00,0X7C,0X00,0X00,0X1F,0X80,0X00,0X00,0X01,0XF8,0X00,
0X00,0X0F,0XC0,0X00,0X00,0X03,0XF0,0X00,0X00,0X0F,0XF0,0X00,0X00,0X0F,0XF0,0X00,
0X00,0X07,0XFE,0X00,0X00,0X7F,0XE0,0X00,0X00,0X01,0XFF,0XF8,0X1F,0XFF,0X80,0X00,
0X00,0X00,0X7F,0XFF,0XFF,0XFE,0X00,0X00,0X00,0X00,0X0F,0XFF,0XFF,0XF0,0X00,0X00,
0X00,0X00,0X01,0XFF,0XFF,0X80,0X00,0X00,0X00,0X00,0X00,0X1F,0XF8,0X00,0X00,0X00,
};


typedef struct _err
{
	int dataErr;
	int flag;
}myData;

int studyFlag = 0;//学习标志位
int mode1Flag = 0;//模式1标志位
int mode1End = 0;//模式1的结果标志位

int mode2Flag = 0;//模式2标志位
int mode2End = 0;//模式2的结果标志位

int studyHandFlag=0;//学习手势
int studyNumFlag=0;//学习数字

int openflag=1;

extern int learnTime;//学习时间
int main(void)
{
	structData numData;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);
	Init_Menue(&firstPage);
	IIC_Init();
	FDC2214_Init();
	KEY_Init();
	TIM4_Int_Init(7199,9999);//定时器初始化,定时10ms
	TIM4->CR1 &=~(0x01);//关闭定时器
	InitData();//将结构体的数据初始化
	while(openflag)
	{
		OLED_Fill();
	  Draw_Picture(openTime,0,64,64,gImage_school);
		OLED_Refresh_Gram();
		FDC2214_GetChannelData(FDC2214_Channel_2, &date2);
		if(abs(openData-date2)>openErr)
		{
			 delay_ms(10);
			 openTime++;
			 if(openTime>100)
			 {
				  openflag=0;
			 }
		}
		else
		{
			 openTime=25;			 
		}
		if(KEY_Scan()!=0)
		{
			 openflag=0;
		}
	}
	while (1)
	{
		Menue_Show();
		KeyNumGet(KEY_Scan());
		FDC2214_GetChannelData(FDC2214_Channel_2, &date2);
		FDC2214_GetChannelData(FDC2214_Channel_3, &date3);  
    numData.data1=date2;
    numData.data2=date3;		
		send_date_u16(date2, date3, date3);
		/*------------------学习阶段---------------------*/
		if (studyHandFlag > 0&&studyNumFlag==0)//学习手势
		{
			  GetData(studyHandFlag,numData);
			  
		}
		if(studyNumFlag>0&&studyHandFlag==0)
		{
			  if(studyNumFlag==1)//等于1学习基础值
				{
					GetData(studyNumFlag,numData); 
				}
				else
				{
					GetData(studyNumFlag+3,numData); //学习数据
				}
		}
		if(studyHandFlag>0||studyNumFlag>0)//如果有一个开始学习则开始计时
		{
			 TIM4->CR1 |=0x01;//打开定时器
		}
		else
		{
			 learnTime=0;
			 TIM4->CR1 &=~(0x01);//关闭定时器
		}
		/*-----------------模式I------------------------*/
		if (mode1Flag == 1&&studyHandFlag==0&&studyNumFlag==0)
		{
			mode1End = handMode(numData);
		}
		else
		{
			 mode1Flag=0;
		}
		/*-----------------模式2------------------------*/
		if (mode2Flag == 1&&studyNumFlag==0&&studyHandFlag==0)
		{
			mode2End = numMode(date2);
		}
		else
		{
			 mode2Flag=0;
		}
	}
}
/**
 *                    _ooOoo_
 *                   o8888888o
 *                   88" . "88
 *                   (| -_- |)
 *                    O\ = /O
 *                ____/`---'\____
 *              .   ' \\| |// `.
 *               / \\||| : |||// \
 *             / _||||| -:- |||||- \
 *               | | \\\ - /// | |
 *             | \_| ''\---/'' | |
 *              \ .-\__ `-` ___/-. /
 *           ___`. .' /--.--\ `. . __
 *        ."" '< `.___\_<|>_/___.' >'"".
 *       | | : `- \`.;`\ _ /`;.`/ - ` : | |
 *         \ \ `-. \_ __\ /__ _/ .-` / /
 * ======`-.____`-.___\_____/___.-`____.-'======
 *                    `=---='
 *
 * .............................................
 *          佛祖保佑             代码无BUG
 */

