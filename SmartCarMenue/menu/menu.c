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
float P = 0;
float I = 0;
float D = 0;
//------------------------����ʾ�Ķ����ŵ�����--------------------------------
_Menue(firstPage, "SmartCar", PAGE_NULL,
	{
		Set_Courese(3);
		Show_Text(1,"PID:%f",P);
		Change_Data(1,&P);
		Show_Text(2,"I:%f",I);
		Change_Data(2,&I);
		Show_Text(3,"D:%f",D);
		Change_Data(3,&D);
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
	void Change_Data(char location, float *data)
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

