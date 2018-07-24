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

int handFlag=0;//模式一的评估标志位

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
int modeStudy(int baseData)
{
	static int flag = 0;
	static int nowData = 0;
	int data;
	if (studyFlag > 0)
	{
		if (flag < 10)	//取十次求平均值
		{
			nowData += baseData;
			flag++;
		}
		else
		{
			flag = 0;
			data = nowData;
			nowData = 0;
			return data / 10;
		}
	}
	else
	{
		flag = 0;
		nowData = 0;
	}
	return 0;
}

/*----------------------------------数据滤波部分--------------------------------------*/
int fliterForDate(FDC2214_channel_t channle)
{
	  int i,j,temp,finallyData=0;
	  unsigned int basedata=0;
	  for(i=0;i<5;i++)//得到初始的数据
		{
			FDC2214_GetChannelData(channle, &basedata);
			firstData[i]=basedata;
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
	 basedata=(firstData[1]+firstData[2]+firstData[3])/3;//均值滤波	 
	 return basedata;
}
int main(void)
{
	lineData getAllData;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);
	Init_Menue(&firstPage);
	IIC_Init();
	FDC2214_Init();
	KEY_Init();
	InitLine();
	while (1)
	{
		Menue_Show();
		KeyNumGet(KEY_Scan());
//		date0=fliterForDate(FDC2214_Channel_0);
//		date1=fliterForDate(FDC2214_Channel_1);
//		date2=fliterForDate(FDC2214_Channel_2);
//		date3=fliterForDate(FDC2214_Channel_3);
    FDC2214_GetChannelData(FDC2214_Channel_0, &date0);
		FDC2214_GetChannelData(FDC2214_Channel_1, &date1);
		FDC2214_GetChannelData(FDC2214_Channel_2, &date2);
		FDC2214_GetChannelData(FDC2214_Channel_3, &date3);
		getAllData.line1.nodeData=date0;
		getAllData.line2.nodeData=date1;
		getAllData.line3.nodeData=date2;
		getAllData.line4.nodeData=date3;
		send_date_u32(date0, date1, date2,date3);
		/*------------------学习阶段---------------------*/
		if (studyFlag > 0)//大于零开始学习
		{
			 GetData(studyFlag,getAllData);
		}
		/*-----------------模式I------------------------*/
		if (mode1Flag == 1&&handFlag==0)
		{
			mode1End = returnHand(getAllData);
		}
		/*-----------------模式2------------------------*/
		if (mode2Flag == 1)
		{
			mode2End = mode2(date0);
		}		
		/*-----------------评估-------------------------*/
		if(handFlag==1)
		{
			 GetImtStone(&lineStoneErr,lineClothErr,lineShearErr);
			 GetImtStone(&lineClothErr,lineStoneErr,lineShearErr);
			 GetImtStone(&lineShearErr,lineClothErr,lineStoneErr);
			 handFlag=0;
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

