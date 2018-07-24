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
#include "OLED.H"
#include "timer.h"

//��������
int openData=14700000;
int openErr=60000;
int openTime=25;

extern MenuPage firstPage;//ҳ��һ
uint32_t date0, date1, date2, date3;
uint32_t fre0, fre1, fre2, fre3;
/*-----------------------------ͼ��-------------------------------------------*/
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

int studyFlag = 0;//ѧϰ��־λ
int mode1Flag = 0;//ģʽ1��־λ
int mode1End = 0;//ģʽ1�Ľ����־λ

int mode2Flag = 0;//ģʽ2��־λ
int mode2End = 0;//ģʽ2�Ľ����־λ

int studyHandFlag=0;//ѧϰ����
int studyNumFlag=0;//ѧϰ����

int openflag=1;

extern int learnTime;//ѧϰʱ��
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
	TIM4_Int_Init(7199,9999);//��ʱ����ʼ��,��ʱ10ms
	TIM4->CR1 &=~(0x01);//�رն�ʱ��
	InitData();//���ṹ������ݳ�ʼ��
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
		/*------------------ѧϰ�׶�---------------------*/
		if (studyHandFlag > 0&&studyNumFlag==0)//ѧϰ����
		{
			  GetData(studyHandFlag,numData);
			  
		}
		if(studyNumFlag>0&&studyHandFlag==0)
		{
			  if(studyNumFlag==1)//����1ѧϰ����ֵ
				{
					GetData(studyNumFlag,numData); 
				}
				else
				{
					GetData(studyNumFlag+3,numData); //ѧϰ����
				}
		}
		if(studyHandFlag>0||studyNumFlag>0)//�����һ����ʼѧϰ��ʼ��ʱ
		{
			 TIM4->CR1 |=0x01;//�򿪶�ʱ��
		}
		else
		{
			 learnTime=0;
			 TIM4->CR1 &=~(0x01);//�رն�ʱ��
		}
		/*-----------------ģʽI------------------------*/
		if (mode1Flag == 1&&studyHandFlag==0&&studyNumFlag==0)
		{
			mode1End = handMode(numData);
		}
		else
		{
			 mode1Flag=0;
		}
		/*-----------------ģʽ2------------------------*/
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
 *          ���汣��             ������BUG
 */

