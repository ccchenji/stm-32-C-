/*---------------ǰ��������¥�����з��汣�ӣ��ҾͲ��Ż���bug------------------------------------*/
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
*        |           |             ���ޱ��Ӵ�����bug
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
extern MenuPage firstPage;//ҳ��һ
uint32_t date0, date1, date2, date3;
uint32_t fre0, fre1, fre2, fre3;

typedef struct _err
{
	int dataErr;
	int flag;
}myData;

int studyFlag = 0;//ѧϰ��־λ
int mode1Flag = 0;//ģʽ1��־λ
int mode1End = 0;//ģʽ1�Ľ����־λ

int mode2Flag = 0;//ģʽ2��־λ
int mode2End = 0;//ģʽ2�Ľ����־λ



int main(void)
{
	structData numData;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);
	Init_Menue(&firstPage);
	IIC_Init();
	FDC2214_Init();
	KEY_Init();
	InitData();//���ṹ������ݳ�ʼ��
	while (1)
	{
		Menue_Show();
		KeyNumGet(KEY_Scan());
		FDC2214_GetChannelData(FDC2214_Channel_2, &date2);
		FDC2214_GetChannelData(FDC2214_Channel_3, &date3);  
    numData.data1=date2;
    numData.data2=date3;		
		send_date_u16(date2, date3, date3);
		/*------------------ѧϰ�׶�---------------------*/
		if (studyFlag > 0)//�����㿪ʼѧϰ
		{
			  GetData(studyFlag,numData);
		}
		/*-----------------ģʽI------------------------*/
		if (mode1Flag == 1)
		{
			mode1End = handMode(numData);
		}
		/*-----------------ģʽ2------------------------*/
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
 *          ���汣��             ������BUG
 */

