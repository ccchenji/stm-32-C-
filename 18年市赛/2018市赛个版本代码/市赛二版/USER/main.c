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
extern MenuPage firstPage;//页面一
uint32_t date0, date1, date2, date3;
uint32_t fre0, fre1, fre2, fre3;

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

int baseData1 = 0;//基准值1
int baseData2 = 0;//基准值2

int base1Err = 0;

int stoneErr = 0;//石头
int clothErr = 0;//布
int shearErr = 0;//剪刀

int oneErr = 0;//1的差值
int twoErr = 0;//2的差值
int threeErr = 0;//3的差值
int fourErr = 0;//4的差值
int fiveErr = 0;//5的差值


int middleData = 0;

/*------------------------滤波部分变量---------------------------------*/
int firstData[5]={0};
int secondData=0;
int thirdData[3]={0};
/*------------------------------模式1-----------------------------------*/
int mode1(int data)
{
	int i = 0, j = 0;
	int errData = baseData1 - data;//得到当前的差值
	myData errDataAll[4];
	myData baseData;//中间变量
	errDataAll[0].dataErr = abs(errData - 0); errDataAll[0].flag = 0;//得到和基础值的差值
	errDataAll[1].dataErr = abs(errData - stoneErr); errDataAll[1].flag = 1;//得到和石头的差值
	errDataAll[2].dataErr = abs(errData - clothErr); errDataAll[2].flag = 2;//得到和布的差值
	errDataAll[3].dataErr = abs(errData - shearErr); errDataAll[3].flag = 3;//得到和剪刀的差值	
	for (i = 0; i < 3; i++)//冒泡排序法(升序)得到里目标值最近的值
	{
		for (j = 0; j < 3 - i; j++)
		{
			if (errDataAll[j].dataErr > errDataAll[j + 1].dataErr)
			{
				baseData.dataErr = errDataAll[j + 1].dataErr;
				baseData.flag = errDataAll[j + 1].flag;
				errDataAll[j + 1].dataErr = errDataAll[j].dataErr;
				errDataAll[j + 1].flag = errDataAll[j].flag;
				errDataAll[j].dataErr = baseData.dataErr;
				errDataAll[j].flag = baseData.flag;
			}
		}
	}
	return errDataAll[0].flag;
}
/*-----------------------------模式2------------------------------------*/
int mode2(int data)
{
	int i = 0, j = 0;
	int errData = baseData1 - data;//得到当前的差值
	myData errDataAll[6];
	myData baseData;//中间变量
	errDataAll[0].dataErr = abs(errData - 0); errDataAll[0].flag = 0;//得到与基础值的差值
	errDataAll[1].dataErr = abs(errData - oneErr); errDataAll[1].flag = 1;//得到与1的差值
	errDataAll[2].dataErr = abs(errData - twoErr); errDataAll[2].flag = 2;//得到与2的差值
	errDataAll[3].dataErr = abs(errData - threeErr); errDataAll[3].flag = 3;//得到与3的差值
	errDataAll[4].dataErr = abs(errData - fourErr); errDataAll[4].flag = 4;//得到与4的差值
	errDataAll[5].dataErr = abs(errData - fiveErr); errDataAll[5].flag = 5;//得到与5的差值
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5 - i; j++)
		{
			if (errDataAll[j].dataErr > errDataAll[j + 1].dataErr)
			{
				baseData.dataErr = errDataAll[j + 1].dataErr;
				baseData.flag = errDataAll[j + 1].flag;
				errDataAll[j + 1].dataErr = errDataAll[j].dataErr;
				errDataAll[j + 1].flag = errDataAll[j].flag;
				errDataAll[j].dataErr = baseData.dataErr;
				errDataAll[j].flag = baseData.flag;
			}
		}
	}
	return errDataAll[0].flag;
}
/*------------------------------学习模式--------------------------------*/
int modeStudy()
{
    int i,j,temp,finallyData=0;
	  for(i=0;i<5;i++)//得到初始的数据
		{
			FDC2214_GetChannelData(FDC2214_Channel_0, &date2);
			date0 = date0 % 100000000;
			firstData[i]=date0;
		}
	 for(i=0;i<4;i++)//冒泡排序升序
	 {
		  for(j=0;j<4-i;j++)
			{
				 if(firstData[j]>firstData[j+1])
				 {
					 temp=firstData[j+1];
					 firstData[j+1]=firstData[j];
					 firstData[j]=temp;
				 }
			}
	 }
	 secondData=(firstData[1]+firstData[2]+firstData[3])/3;//均值滤波
	 for(i=0;i<2;i++)//滑平滤波
	 {
		  thirdData[i]=thirdData[i+1];
	 }
	 thirdData[2]=secondData;
	 finallyData=(thirdData[0]+thirdData[1]+thirdData[2])/3;
   return finallyData;
}
int main(void)
{
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);
	Init_Menue(&firstPage);
	IIC_Init();
	FDC2214_Init();
	KEY_Init();
	while (1)
	{
		Menue_Show();
		KeyNumGet(KEY_Scan());
		//    FDC2214_GetChannelData(FDC2214_Channel_1, &date1);
		//    FDC2214_GetChannelData(FDC2214_Channel_2, &date2);
		//    FDC2214_GetChannelData(FDC2214_Channel_3, &date3);        
		//    fre0 = FDC2214_CalculateFrequency(FDC2214_Channel_0, date0);
		//    fre1 = FDC2214_CalculateFrequency(FDC2214_Channel_1, date1);
		//    fre2 = FDC2214_CalculateFrequency(FDC2214_Channel_2, date2);
		//    fre3 = FDC2214_CalculateFrequency(FDC2214_Channel_3, date3);
		date1 = date1 % 100000000;
		date2 = date2 % 100000000;
		date3 = date3 % 100000000;
		middleData = modeStudy();
		FDC2214_GetChannelData(FDC2214_Channel_0, &date2);
		date2 = date2 % 100000000;
		send_date_u16(middleData, date2, date2);
		/*------------------学习阶段---------------------*/
		if (studyFlag > 0)//大于零开始学习
		{
			  middleData = modeStudy();
				switch (studyFlag)
				{
				case 1:baseData1 = middleData; break;
				case 2:stoneErr = baseData1 - middleData; break;
				case 3:clothErr = baseData1 - middleData; break;
				case 4:shearErr = baseData1 - middleData; break;
				case 5:oneErr = baseData1 - middleData; break;
				case 6:twoErr = baseData1 - middleData; break;
				case 7:threeErr = baseData1 - middleData; break;
				case 8:fourErr = baseData1 - middleData; break;
				case 9:fiveErr = baseData1 - middleData; break;
				default:
					break;
				}
		}
		/*-----------------模式I------------------------*/
		if (mode1Flag == 1)
		{
			mode1End = mode1(date0);
		}
		/*-----------------模式2------------------------*/
		if (mode2Flag == 1)
		{
			mode2End = mode2(date0);
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

