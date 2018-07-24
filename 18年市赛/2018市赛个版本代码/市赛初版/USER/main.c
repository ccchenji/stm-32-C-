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

int baseData1 = 0;//��׼ֵ1
int baseData2 = 0;//��׼ֵ2

int base1Err = 0;

int stoneErr = 0;//ʯͷ
int clothErr = 0;//��
int shearErr = 0;//����

int oneErr = 0;//1�Ĳ�ֵ
int twoErr = 0;//2�Ĳ�ֵ
int threeErr = 0;//3�Ĳ�ֵ
int fourErr = 0;//4�Ĳ�ֵ
int fiveErr = 0;//5�Ĳ�ֵ


int middleData = 0;
/*------------------------------ģʽ1-----------------------------------*/
int mode1(int data)
{
	int i = 0, j = 0;
	int errData = baseData1 - data;//�õ���ǰ�Ĳ�ֵ
	myData errDataAll[4];
	myData baseData;//�м����
	errDataAll[0].dataErr = abs(errData - 0); errDataAll[0].flag = 0;//�õ��ͻ���ֵ�Ĳ�ֵ
	errDataAll[1].dataErr = abs(errData - stoneErr); errDataAll[1].flag = 1;//�õ���ʯͷ�Ĳ�ֵ
	errDataAll[2].dataErr = abs(errData - clothErr); errDataAll[2].flag = 2;//�õ��Ͳ��Ĳ�ֵ
	errDataAll[3].dataErr = abs(errData - shearErr); errDataAll[3].flag = 3;//�õ��ͼ����Ĳ�ֵ	
	for (i = 0; i < 3; i++)//ð������(����)�õ���Ŀ��ֵ�����ֵ
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
/*-----------------------------ģʽ2------------------------------------*/
int mode2(int data)
{
	int i = 0, j = 0;
	int errData = baseData1 - data;//�õ���ǰ�Ĳ�ֵ
	myData errDataAll[6];
	myData baseData;//�м����
	errDataAll[0].dataErr = abs(errData - 0); errDataAll[0].flag = 0;//�õ������ֵ�Ĳ�ֵ
	errDataAll[1].dataErr = abs(errData - oneErr); errDataAll[1].flag = 1;//�õ���1�Ĳ�ֵ
	errDataAll[2].dataErr = abs(errData - twoErr); errDataAll[2].flag = 2;//�õ���2�Ĳ�ֵ
	errDataAll[3].dataErr = abs(errData - threeErr); errDataAll[3].flag = 3;//�õ���3�Ĳ�ֵ
	errDataAll[4].dataErr = abs(errData - fourErr); errDataAll[4].flag = 4;//�õ���4�Ĳ�ֵ
	errDataAll[5].dataErr = abs(errData - fiveErr); errDataAll[5].flag = 5;//�õ���5�Ĳ�ֵ
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
/*------------------------------ѧϰģʽ--------------------------------*/
int modeStudy(int baseData)
{
	static int flag = 0;
	static int nowData = 0;
	int data;
	if (studyFlag > 0)
	{
		if (flag < 10)	//ȡʮ����ƽ��ֵ
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
/*----------------------------------�������˲�----------------------------------------*/
static double KalmanFilter(const double ResrcData, double ProcessNiose_Q, double MeasureNoise_R)
{

	double R = MeasureNoise_R;
	double Q = ProcessNiose_Q;

	static double x_last;
	double x_mid = x_last;
	double x_now;

	static double p_last;
	double p_mid;
	double p_now;

	double kg;

	x_mid = x_last;                       //x_last=x(k-1|k-1),x_mid=x(k|k-1)
	p_mid = p_last + Q;                     //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=����

	/*
	 *  �������˲��������Ҫ��ʽ
	 */
	kg = p_mid / (p_mid + R);                 //kgΪkalman filter��R Ϊ����
	x_now = x_mid + kg * (ResrcData - x_mid);   //���Ƴ�������ֵ
	p_now = (1 - kg)*p_mid;                 //����ֵ��Ӧ��covariance
	p_last = p_now;                     //����covariance ֵ
	x_last = x_now;                     //����ϵͳ״ֵ̬

	return x_now;
}
int main(void)
{
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);
	Init_Menue(&firstPage);
	IIC_Init();
	FDC2214_Init();
	KEY_Init();
	while (1)
	{
		Menue_Show();
		KeyNumGet(KEY_Scan());
		FDC2214_GetChannelData(FDC2214_Channel_0, &date0);
		//    FDC2214_GetChannelData(FDC2214_Channel_1, &date1);
		//    FDC2214_GetChannelData(FDC2214_Channel_2, &date2);
		//    FDC2214_GetChannelData(FDC2214_Channel_3, &date3);        
		//    fre0 = FDC2214_CalculateFrequency(FDC2214_Channel_0, date0);
		//    fre1 = FDC2214_CalculateFrequency(FDC2214_Channel_1, date1);
		//    fre2 = FDC2214_CalculateFrequency(FDC2214_Channel_2, date2);
		//    fre3 = FDC2214_CalculateFrequency(FDC2214_Channel_3, date3);
		date0 = date0 % 100000000;
		date1 = date1 % 100000000;
		date2 = date2 % 100000000;
		date3 = date3 % 100000000;
		//date0=KalmanFilter(date0,0.05,5);
		send_date_u16(date0, date1, date2);
		/*------------------ѧϰ�׶�---------------------*/
		if (studyFlag > 0)//�����㿪ʼѧϰ
		{
			middleData = modeStudy(date0);
			if (middleData > 0)
			{
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
		}
		/*-----------------ģʽI------------------------*/
		if (mode1Flag == 1)
		{
			mode1End = mode1(date0);
		}
		/*-----------------ģʽ2------------------------*/
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
 *          ���汣��             ������BUG
 */

