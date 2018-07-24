#include "menu.h"
#include "OLED.H"
#include "Queue.h"
#include "stack.h"
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
MenuPage studyPage;//ģʽ5

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
int nowNum=0;


int flag=0;

extern uint32_t date0;
extern uint32_t date1;
extern uint32_t date2;
extern uint32_t date3;


extern int baseData1;

extern int stoneErr;//ʯͷ
extern int clothErr;//��
extern int shearErr;//����

extern int oneErr;//1�Ĳ�ֵ
extern int twoErr;//2�Ĳ�ֵ
extern int threeErr;//3�Ĳ�ֵ
extern int fourErr;//4�Ĳ�ֵ
extern int fiveErr;//5�Ĳ�ֵ
//------------------------����ʾ�Ķ����ŵ�����--------------------------------
_Menue(firstPage, "MODE", PAGE_NULL,
	{
		Set_Courese(5);
		Show_Text(1,"MODEI");
		Change_Page(1,&mode1Page);
		Show_Text(2,"MODEII");
		Change_Page(2,&mode2Page);
		Show_Text(3,"MODEII");
	  Show_Text(4,"MODEIV");
		Show_Text(5,"STUDY");
		Change_Page(5,&studyPage);
	})
	
_Menue(mode1Page, "MODEI", &firstPage,
	{
		Set_Courese(2);
		Show_Text(1,"mode1Flag:%d",mode1Flag);
		Change_Data(1,&mode1Flag);
		if(mode1Flag>1)mode1Flag=1;else if(mode1Flag<0)mode1Flag=0;
		switch(mode1End)
		{
			case 0:end1Data="nothing";break;
			case 1:end1Data="stone";break;
			case 2:end1Data="cloth";break;
			case 3:end1Data="shear";break;
			default:
				      break;
		}
		Show_Text(2,end1Data);
	})
_Menue(mode2Page, "MODEII", &firstPage,
	{
		Set_Courese(2);
		Show_Text(1,"mode2Flag:%d",mode2Flag);
		Change_Data(1,&mode2Flag);
		if(mode2Flag>1)mode2Flag=1;else if(mode2Flag<0)mode2Flag=0;
		switch(mode2End)
		{
			case 0:nowNum=0;break;
			case 1:nowNum=1;break;
			case 2:nowNum=2;break;
			case 3:nowNum=3;break;
			case 4:nowNum=4;break;
			case 5:nowNum=5;break;
			default:
				      break;
		}
		Show_Text(2,"nowNum:%d",nowNum);
	})
_Menue(studyPage, "study", &firstPage,
	{
		Set_Courese(10);
		Show_Text(1,"baseData:%d",baseData1);
	  Show_Text(2,"stoneErr:%d",stoneErr);
		Show_Text(3,"clothErr:%d",clothErr);
		Show_Text(4,"shearErr:%d",shearErr);
		Show_Text(5,"oneErr:%d",oneErr);
		Show_Text(6,"twoErr:%d",twoErr);
		Show_Text(7,"threeErr:%d",threeErr);
		Show_Text(8,"fourErr:%d",fourErr);
		Show_Text(9,"fiveErr:%d",fiveErr);
		Show_Text(10,"flag:%d",flag);
		if(flag>9){flag=0;}else if(flag<0){flag=0;};
		Change_Data(10,&flag);
		switch(flag)
		{
			case 0:studyFlag=0;break;
			case 1:studyFlag=1;break;
			case 2:studyFlag=2;break;
			case 3:studyFlag=3;break;
			case 4:studyFlag=4;break;			
			case 5:studyFlag=5;break;
			case 6:studyFlag=6;break;
			case 7:studyFlag=7;break;
			case 8:studyFlag=8;break;
			case 9:studyFlag=9;break;
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

