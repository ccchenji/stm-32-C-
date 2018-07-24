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
	InitData();//将结构体的数据初始化
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
		if (studyFlag > 0)//大于零开始学习
		{
			  GetData(studyFlag,numData);
		}
		/*-----------------模式I------------------------*/
		if (mode1Flag == 1)
		{
			mode1End = handMode(numData);
		}
		/*-----------------模式2------------------------*/
		if (mode2Flag == 1)
		{
			mode2End = numMode(date2);
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

