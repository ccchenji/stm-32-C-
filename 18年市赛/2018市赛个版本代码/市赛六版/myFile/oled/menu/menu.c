#include "menu.h"
#include "OLED.H"
#include "Queue.h"
#include "stack.h"
#include "dealDate.h"
#include "map.h"
extern float Mydata;
Queue KeyQueue;//��ֵ����
                                    MyStack DataStack;//����ջ
char KeyNum = 0;//ȫ�ֵļ�ֵ
Mycourse cour = { 0,1 ,0 };//��ʼ�����
Mycourse *course = &cour;//����ȫ�ֹ�겢��ʼ��
MenuPage *nowPage;//��ǰ��ҳ��
MenuPage firstPage;//ҳ��һ

MenuPage mode1Page;//ģʽ1
MenuPage mode2Page;//ģʽ2
MenuPage mode3Page;//ģʽ3
MenuPage mode4Page;//ģʽ4
MenuPage gamePage;//ģʽ5

/**
 * http://www.flvcd.com/
 *  .--,       .--,
 * ( (  \.---./  ) )
 *  '.__/o   o\__.'
 *     {=  ^  =}
 *      >  -  <
 *     /       \
 *    //       \\
 *   //|   .   |\\
 *   "'\       /'"_.-~^`'-.
 *      \  _  /--'         `
 *    ___)( )(___
 *   (((__) (__)))   ��ɽ��ֹ��������ֹ���䲻������������֮
 */


extern int studyFlag;
extern int mode1Flag;
extern int mode1End;//ģʽ1�Ľ����־λ 
char *end1Data="nothing";

extern int mode2Flag;//ģʽ2��־λ
extern int mode2End;//ģʽ2�Ľ����־λ

extern int studyHandFlag;//ѧϰ����
extern int studyNumFlag;//ѧϰ����


extern int gameFlag;//��Ϸ��ʼ��־λ
extern StructGame gameEndFlag;//��Ϸ���

int nowNum=0;



extern uint32_t date0;
extern uint32_t date1;
extern uint32_t date2;
extern uint32_t date3;


extern int learnTime;//ѧϰʱ��
//------------------------����ʾ�Ķ����ŵ�����--------------------------------
/*------------------------------ģʽѡ��--------------------------*/
_Menue(firstPage, "MODE", PAGE_NULL,
	{
		Set_Courese(5);
		Show_Text(1,"1:JudgeHand");
		Change_Page(1,&mode1Page);
		Show_Text(2,"2:JudgeNum");
		Change_Page(2,&mode2Page);
		Show_Text(3,"3:LearnHand");
		Change_Page(3,&mode3Page);
	  Show_Text(4,"4:LearnNum");
	  Change_Page(4,&mode4Page);
		Show_Text(5,"5:PlayGame");
	  Change_Page(5,&gamePage);
		gameFlag=0;
	})
/*-------------------------------�ж�����--------------------------*/	
_Menue(mode1Page, "JudgeHand", &firstPage,
	{
		Set_Courese(1);
		Show_Text(1,"startJudge:%d",mode1Flag);
		Change_Data(1,&mode1Flag);
		if(mode1Flag>1)mode1Flag=1;else if(mode1Flag<0)mode1Flag=0;
		switch(mode1End)
		{
			case 0:end1Data="end:nothing";break;
			case 1:end1Data="end:stone";Draw_Picture(90,0,40,40,gImage_stone);break;
			case 2:end1Data="end:cloth";Draw_Picture(90,0,40,40,gImage_cloth);break;
			case 3:end1Data="end:shear";Draw_Picture(90,0,40,40,gImage_shear);break;
			default:
				      break;
		}
		Show_Text(3,"err1:%d",date2);
		Show_Text(5,"err2:%d",date3);
		Show_Text(7,end1Data);
	})
/*-----------------------------�ж�����----------------------------*/
_Menue(mode2Page, "JudgeNum", &firstPage,
	{
		Set_Courese(2);
		Show_Text(1,"startJudge:%d",mode2Flag);
		Change_Data(1,&mode2Flag);
		if(mode2Flag>1)mode2Flag=1;else if(mode2Flag<0)mode2Flag=0;
		switch(mode2End)
		{
			case 0:nowNum=0;break;
			case 1:nowNum=1;Draw_Picture(90,0,40,40,gImage_one);break;
			case 2:nowNum=2;Draw_Picture(90,0,40,40,gImage_two);break;
			case 3:nowNum=3;Draw_Picture(90,0,40,40,gImage_three);break;
			case 4:nowNum=4;Draw_Picture(90,0,40,40,gImage_four);break;
			case 5:nowNum=5;Draw_Picture(90,0,40,40,gImage_five);break;
			default:
				      break;
		}
		Show_Text(3,"err1:%d",date2);
		Show_Text(5,"err2:%d",date3);
		Show_Text(7,"endData:%d",nowNum);
	})
/*---------------------------ѧϰ����---------------------------------*/
_Menue(mode3Page, "LearnHand", &firstPage,
	{
		Set_Courese(1);//studyHandFlag
		Show_Text(1,"studyHandFlag:%d",studyHandFlag);
		Change_Data(1,&studyHandFlag);
		if(studyHandFlag>4)studyHandFlag=0;else if(studyHandFlag<0)studyHandFlag=4;
		switch(studyHandFlag)
		{
			case 1:Draw_Rectangle(80,0,40,40);
			       Show_Text(3,"Data11:%d",tBaseData.data1);
			       Show_Text(5,"Data12:%d",tBaseData.data2);
			       break;
			case 2:Draw_Picture(90,0,40,40,gImage_stone);
			       Show_Text(3,"Data11:%d",tStoneErr.data1);
			       Show_Text(5,"Data12:%d",tStoneErr.data2);
			       break;
			case 3:Draw_Picture(90,0,40,40,gImage_cloth);
			       Show_Text(3,"Data11:%d",tClothErr.data1);
			       Show_Text(5,"Data12:%d",tClothErr.data2);
			       break;
			case 4:Draw_Picture(90,0,40,40,gImage_shear);
			       Show_Text(3,"Data11:%d",tShearErr.data1);
			       Show_Text(5,"Data12:%d",tShearErr.data2);
			       break;
			default:
				     break;
		}
		Show_Text(7,"learnTime:%d",learnTime);
	})
/*-------------------------ѧϰ����---------------------------*/
_Menue(mode4Page, "LearnNum", &firstPage,
	{
		Set_Courese(1);
		Show_Text(1,"studyNumFlag:%d",studyNumFlag);
		Change_Data(1,&studyNumFlag);
		if(studyNumFlag>6)studyNumFlag=0;else if(studyNumFlag<0)studyNumFlag=6;
		switch(studyNumFlag)
		{
			case 1:Draw_Rectangle(80,0,40,40);
			       Show_Text(3,"Data11:%d",tBaseData.data1);
			       Show_Text(5,"Data12:%d",tBaseData.data2);
			       break;
			case 2:Draw_Picture(90,0,40,40,gImage_one);
			       Show_Text(3,"Data11:%d",tOneErr.data1);
			       Show_Text(5,"Data12:%d",tOneErr.data2);
			       break;
			case 3:Draw_Picture(90,0,40,40,gImage_two);
			       Show_Text(3,"Data11:%d",tTwoErr.data1);
			       Show_Text(5,"Data12:%d",tTwoErr.data2);
			       break;
			case 4:Draw_Picture(90,0,40,40,gImage_three);
			       Show_Text(3,"Data11:%d",tThreeErr.data1);
			       Show_Text(5,"Data12:%d",tThreeErr.data2);
			       break;
			case 5:Draw_Picture(90,0,40,40,gImage_four);
			       Show_Text(3,"Data11:%d",tFourErr.data1);
			       Show_Text(5,"Data12:%d",tFourErr.data2);
			       break;
			case 6:Draw_Picture(90,0,40,40,gImage_five);
			       Show_Text(3,"Data11:%d",tFiveErr.data1);
			       Show_Text(5,"Data12:%d",tFiveErr.data2);
				     break;
			default:
				     break;
		}
		Show_Text(7,"learnTime:%d",learnTime);
	})
/*---------------------------------��ȭ��Ϸ------------------------------------*/
_Menue(gamePage, "GAME", &firstPage,
	{
		Get_key(1);//�õ���ֵ
		gameFlag=1;
		Draw_line(0,32,128,32);
	  switch(gameEndFlag.line1)
		 {
			case 0:Show_Text(2,"nothing");break;
			case 1:Draw_Picture(100,40,24,24,gImages_school);break;
			case 2:Draw_Picture(100,40,24,24,gImagec_school);break;
			case 3:Draw_Picture(100,40,24,24,gImageh_school);break;
			default:
				      break;
		 }
		 switch(gameEndFlag.line2)
		 {
			case 0:Show_Text(6,"nothing");break;
			case 1:Draw_Picture(100,0,24,24,gImages_school);break;
			case 2:Draw_Picture(100,0,24,24,gImagec_school);break;
			case 3:Draw_Picture(100,0,24,24,gImageh_school);break;
			default:
				      break;
		 }
		 if(gameEndFlag.end!=0)
		 {
			  switch(gameEndFlag.end)
				{
					case 1:Show_Text(2,"WIN");Show_Text(6,"LOSE");break;
					case 2:Show_Text(2,"LOSE");Show_Text(6,"WIN");break;
					case 3:Show_Text(2,"EQ");Show_Text(6,"EQ");break;
				}
		 }
		
	})
//-------------------------�˵���ʾ����-------------------------------------
		void Menue_Show()//��ʾ��ǰҳ��
	{
		OLED_Fill();
		nowPage->nowPage();
		OLED_Refresh_Gram();
	}
//-------------------------�˵���ʼ������-----------------------------------
	void Init_Menue(MenuPage *page)
	{
		OLED_Init();//��ʼ��LED
		OLED_Clear();//��LED����
		KeyQueue.first = 0;//��ʼ����ֵ����
		KeyQueue.last = 0;
		DataStack.top = -1;//��ʼ������ջ
		nowPage = page;//�õ���ʼ��ҳ��
	}
//-------------------------�������ļ�ֵ�������-----------------------------
	void KeyNumGet(int key)
	{
		IQueue(&KeyQueue, key);
	}
	void StringCopy(char *desition, char *source, char length)//copyһ���ַ����е�һ�����ȵ����ݵ���һ�ַ���
	{
		int i = 0;
		for (i = 0; i < length; i++)
		{
			*(desition++) = *(source++);
		}
	}
//------------------------���㵱ǰӦ����ʾ����------------------------------
	int CountLine(int location)
	{
		return location - course->page_skewing;
	}
//------------------------�ж��Ƿ��ڿ���ʾ����------------------------------
	int CanShow(int location)
	{
		int cm = location - course->page_skewing;
		return cm > 0 && cm < MAX_LINE + 1;
	}
//------------------------���ߺ���-----------------------------------------
	void Draw_line(float X1, float Y1, float X2, float Y2)
	{
		int i = 0;
		if ((X2 - X1) != 0)//�ж�б���Ƿ����
		{
			float k = (Y2 - Y1) / (X2 - X1);//�õ�ֱ�ߵ�б��
			float d = Y1 - k * X1;//�õ���Y��ļн�
			unsigned char length = abs((int)(X1 - X2)) + 1;//�õ�X�᷽����Ƶĳ���
			for (i = 0; i < length; i++)
			{
				OLED_DrawPoint(X1 + i, k*(X1 + i) + d, 1);
			}
		}
		else
		{
			for (i = 0; i < Y2 - Y1 + 1; i++)
			{
				OLED_DrawPoint(X1, Y1 + i, 1);
			}
		}
	}
//-------------------------------������-----------------------------------------
	void Draw_Rectangle(char x, char y, char width, char height)
	{
		Draw_line(x, y, x + width, y);
		Draw_line(x, y, x, y + height);
		Draw_line(x, y + height, x + width, y + height);
		Draw_line(x + width, y, x + width, y + height);
	}
//---------------------------------��Բ-----------------------------------------
	void Draw_Circle(float x, float y, float R)
	{
		float angle = 0;//��ʼ�Ƕ�
		for (angle = 0; angle < 360; angle += 1)
		{
			OLED_DrawPoint(R*sin(angle*3.14 / 180) + x, y + R * cos(angle*3.14 / 180), 1);
		}
	}
/*-----------------------��ͼ����------------------------------------*/
	void Draw_Picture(char x,char y,char width,char height,unsigned char BMP[])//ˮƽɨ�裬��������
	{
     char x0=width/8;
		 char middleDate=0;
		 int i=0,j=0,k=1,m=0;
		 int movDate=0;
		 for(i=0;i<height;i++)
		{
			for(m=0;m<x0;m++)
			{
			  middleDate=BMP[i*x0+m];
			 for(j=0;j<8;j++)
			 {
				  movDate=(k<<(7-j))&middleDate;
				  if(movDate!=0)
					{
					  OLED_DrawPoint(m*8+j+x,i+y,1); 
					}
			 } 
		  }
		}
	}
//---------------------------------�����--------------------------------------
	void Draw_course(char x, char y)
	{
		if (y > 7)
		{
			y = 7;
		}
		OLED_ShowString(x, y, ">");
	}
//--------------------------------�õ���ֵ-------------------------------------
	void Get_key(int allLine)
	{
		KeyNum = OQueue(&KeyQueue);
		if (KeyNum == KEY_DOWN)
		{
			course->set_y += 1;//���ָ���һ
			if (allLine > MAX_LINE)
			{
				if (course->set_y > MAX_LINE)
				{
					course->set_y = MAX_LINE;
					course->page_skewing += 1;//ҳ��ָ��ƫ������һ
					if (course->page_skewing > (allLine - MAX_LINE))//����ҳ��ָ��ƫ����������
					{
						course->page_skewing = allLine - MAX_LINE;
					}
				}
			}
			else
			{
				if (course->set_y > allLine)
				{
					course->set_y = allLine;
				}
			}
		}
		else if (KeyNum == KEY_UP)
		{
			course->set_y -= 1;
			if (course->set_y < 1)
			{
				course->set_y = 1;
				if (course->page_skewing > 0)
				{
					course->page_skewing -= 1;//ҳ��ƫ������һ
				}
			}
		}
		else if (KeyNum == kEY_BANK)//����Ƿ��ؼ�
		{
			if (nowPage->fatherPage != NULL)//����и�ҳ��
			{
				nowPage = nowPage->fatherPage;//�ı�ҳ��
				Pop(&DataStack, course);//ͬʱȡ������ջ���������
			}
		}
	}
//--------------------------------��ʾ�ı�----------------------------------------
	void Show_Text(char location, char *name, ...)
	{
		va_list vp;
		int d = 0; float f = 0;
		char *p;
		char ap[BUFF_LENGTH] = { 0 };
		char data[10] = { 0 };//���ڴ�������
		if (!CanShow(location))return;//���ڿ���ʾ����ֱ���˳�
		va_start(vp, name);
		p = strstr(name, "%");
		if (p)
		{
			StringCopy(ap, name, p - name);//�õ�%ǰ���ֵ
			p++;
			switch (*p)
			{
			case 'd':
			{d = va_arg(vp, int);//�õ�����
			sprintf(data, "%d", d);//������ת�����ַ���
			break; }
			case 'f':
			{
				f = va_arg(vp, double);//�õ�����
				sprintf(data, "%.2f", f);//������ת�����ַ���
				break; }
			default:break;
			}
			strcat(ap, data);//���������ַ���
			OLED_ShowString(10, CountLine(location), ap);//��ʾ
		}
		else
		{
			OLED_ShowString(10, CountLine(location), name);//��ʾ
		}
		va_end(vp);
	}
//---------------------------------��ֵ�ı亯��-------------------------------------------
	void Change_Data(char location, int *data)
	{
		if ((course->page_skewing + course->set_y) == location)//�ж��Ƿ�ѡ�е�ǰ��
		{
			if (KeyNum == KEY_RIGHT)//�����ֵ��RIGHT�����ݼ�
			{
				*data += STEPNUM;//���ݼ�
			}
			if (KeyNum == kEY_LEFT)
			{
				*data -= STEPNUM;
			}
		}
	}
//-----------------------------ҳ��ı亯��--------------------------------------------
	void Change_Page(char location, MenuPage *Page)
	{
		if (course->page_skewing + course->set_y == location)//�ж��Ƿ�ѡ�е�ǰ��
		{
			if (KeyNum == kEY_OK)//��ȷ����
			{
				if (Page != NULL)
				{
					Push(&DataStack, *course);//��ջ
					nowPage = Page;//�ı�ҳ��
					course->page_skewing = 0;//����ʼ��
					course->set_y = 1;
				}
			}
		}
	}
//---------------------------------����ҳ��-----------------------------------------------
	void Set_Courese(int allLine)//����ҳ�沢�����ù���λ��,���Ϊ��ҳ�����е�Show_Text()������
	{
		int set = 0;
		float sa = 0;
		Get_key(allLine);//�õ���ֵ
		set = strlen(nowPage->page);//�õ�����ĳ���
		sa = (127 - (set-1) * 6) / 2;
		Draw_line(0, 60, sa - 6, 60);
		OLED_ShowString(sa - 6, 0, "<");
		OLED_ShowString(sa + set * 6, 0, ">");
		OLED_ShowString(sa, 0, nowPage->page);//���Ʊ���
		Draw_line(sa + set * 6 + 6, 60, 128, 60);
		Draw_line(8, 0, 8, 63);
		Draw_course(0, course->set_y);
	}

