#include "menu.h"
#include "OLED.H"
#include "Queue.h"
#include "stack.h"
#include "PID.H"
#include "stmflash.h"

extern int Speed_Code;
extern float Mydata;
extern MyPID nowPID;
extern MyPID Speed_PID;
extern int num_code;
float Start_flag = 0;
float Maxdata = 3.3;//��ѹ���ֵ


Queue KeyQueue;//��ֵ����
MyStack DataStack;//����ջ
char KeyNum = 0;//ȫ�ֵļ�ֵ
Mycourse cour = { 0,1 ,0 };//��ʼ�����
Mycourse *course = &cour;//����ȫ�ֹ�겢��ʼ��
MenuPage *nowPage;//��ǰ��ҳ��
MenuPage fatherPage;//��ҳ��
MenuPage PidPage;//PIDҳ��
MenuPage FlashSave;
MenuPage FollowData;//�����������
MenuPage SpeedPage;//�ٶȻ�PID����

//------------------------����ʾ�Ķ����ŵ�����--------------------------------
_Menue(fatherPage, "ECP", PAGE_NULL,
	{
		Set_Courese(5);
		Show_Text(1,"ADC:%f",Mydata);
		Show_Text(2,"Position_PID");//λ�û�PID
		Change_Page(2,&PidPage);
		Show_Text(3, "Speed_PID");//�ٶȻ�PID
		Change_Page(3, &SpeedPage);
		Show_Text(4, "FollowData");
		Change_Page(4, &FollowData);
		Show_Text(5, "Speed_Code:%d", Speed_Code);//�õ��ٶ���Ϣ
	})
	_Menue(PidPage, "Position_PID", &fatherPage,
		{
			Set_Courese(6);
			Show_Text(1,"PID_Kp:    %f",nowPID.Kp);
			Change_Data(1,&nowPID.Kp,STEPNUM);
			Show_Text(2, "PID_Kd:   %f",nowPID.Kd);
			Change_Data(2, &nowPID.Kd, STEPNUM);
			Show_Text(3,"PID_Ki:    %f",nowPID.Ki);
			Change_Data(3, &nowPID.Ki, STEPNUM);
			Show_Text(4, "num_code:  %d",num_code);
			Clear_Data(4,&TIM4->CNT);
			Show_Text(5,"Start_flag  %f",Start_flag);
			Change_Data(5,&Start_flag, STEPNUMF);
			if (Start_flag > 1)Start_flag = 1; else if (Start_flag < 0)Start_flag = 0;//��־λ����
			Show_Text(6,"SaveToFlash");
			if (Save_Data(6, nowPID.Kp, nowPID.Kd, nowPID.Ki))Change_Page(6,&FlashSave);
		})
		_Menue(FlashSave, "SaveFlash", &PidPage,
			{
				Set_Courese(1);
				Show_Text(1, "Save   Ok");
			})
			_Menue(FollowData, "FollowData", &fatherPage,
				{
					Set_Courese(1);
					Show_Text(1, "Maxdata: %f", Maxdata);
					Change_Data(1, &Maxdata, 0.1);
					if (Maxdata > 3.3)Maxdata = 3.3; else if (Maxdata < 0)Maxdata = 0;
				})
				_Menue(SpeedPage, "Speed_PID", &fatherPage,
					{
						Set_Courese(5);
						Show_Text(1, "Speed_P:%f", Speed_PID.Kp);
						Change_Data(1,&Speed_PID.Kp,0.01);
						Show_Text(2, "Speed_d:%f", Speed_PID.Kd);
						Change_Data(2, &Speed_PID.Kd, 0.01);
						Show_Text(3, "Speed_I:%f", Speed_PID.Ki);
						Change_Data(3, &Speed_PID.Ki, 0.01);
						Show_Text(4, "num_code:  %d", num_code);
						Clear_Data(4, &TIM4->CNT);
						Show_Text(5, "Start_flag  %f", Start_flag);
						Change_Data(5, &Start_flag, STEPNUMF);
						if (Start_flag > 1)Start_flag = 1; else if (Start_flag < 0)Start_flag = 0;//��־λ����
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
					void Change_Data(char location, float *data, float StepNum)
					{
						if ((course->page_skewing + course->set_y) == location)//�ж��Ƿ�ѡ�е�ǰ��
						{
							if (KeyNum == KEY_RIGHT)//�����ֵ��RIGHT�����ݼ�
							{
								*data += StepNum;//���ݼ�
							}
							if (KeyNum == kEY_LEFT)
							{
								*data -= StepNum;
							}
						}
					}
					//------------------------------�������㺯��------------------------------------------
					void Clear_Data(char location, uint16_t *data)
					{
						if ((course->page_skewing + course->set_y) == location)
						{
							if (KeyNum == KEY_RIGHT)//�����ֵ��RIGHT�����ݼ�
							{
								*data = 0;
							}
						}
					}
					//-----------------------------�����ݴ���flash----------------------------------------
					int Save_Data(char location, float data1, float data2, float data3)
					{
						int i = 0;
						int a = 0;
						short data[6];
						union F_S
						{
							float f;
							short SData[2];
						}f1;
						if ((course->page_skewing + course->set_y) == location)
						{
							if (KeyNum == kEY_OK)//�����ֵ��RIGHT�����ݼ�
							{
								f1.f = data1;
								data[0] = f1.SData[0];
								data[1] = f1.SData[1];
								f1.f = data2;
								data[2] = f1.SData[0];
								data[3] = f1.SData[1];
								f1.f = data3;
								data[4] = f1.SData[0];
								data[5] = f1.SData[1];
								STMFLASH_Write(0X0801FC00, (u16 *)data, sizeof(data));
								return 1;
							}
						}
						return 0;
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
						sa = (127 - (set - 1) * 6) / 2;
						Draw_line(0, 60, sa - 6, 60);
						OLED_ShowString(sa - 6, 0, "<");
						OLED_ShowString(sa + set * 6, 0, ">");
						OLED_ShowString(sa, 0, nowPage->page);//���Ʊ���
						Draw_line(sa + set * 6 + 6, 60, 128, 60);
						Draw_line(8, 0, 8, 63);
						Draw_course(0, course->set_y);
					}

