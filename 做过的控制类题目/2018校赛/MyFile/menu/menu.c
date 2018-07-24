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
float Maxdata = 3.3;//电压最大值


Queue KeyQueue;//键值队列
MyStack DataStack;//数据栈
char KeyNum = 0;//全局的键值
Mycourse cour = { 0,1 ,0 };//初始化光标
Mycourse *course = &cour;//定义全局光标并初始化
MenuPage *nowPage;//当前的页面
MenuPage fatherPage;//父页面
MenuPage PidPage;//PID页面
MenuPage FlashSave;
MenuPage FollowData;//跟随参数设置
MenuPage SpeedPage;//速度环PID设置

//------------------------想显示的东西放到这里--------------------------------
_Menue(fatherPage, "ECP", PAGE_NULL,
	{
		Set_Courese(5);
		Show_Text(1,"ADC:%f",Mydata);
		Show_Text(2,"Position_PID");//位置环PID
		Change_Page(2,&PidPage);
		Show_Text(3, "Speed_PID");//速度环PID
		Change_Page(3, &SpeedPage);
		Show_Text(4, "FollowData");
		Change_Page(4, &FollowData);
		Show_Text(5, "Speed_Code:%d", Speed_Code);//得到速度信息
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
			if (Start_flag > 1)Start_flag = 1; else if (Start_flag < 0)Start_flag = 0;//标志位清零
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
						if (Start_flag > 1)Start_flag = 1; else if (Start_flag < 0)Start_flag = 0;//标志位清零
					})
					//-------------------------菜单显示函数-------------------------------------
						void Menue_Show()//显示当前页面
					{
						OLED_Fill();
						nowPage->nowPage();
						OLED_Refresh_Gram();
					}
					//-------------------------菜单初始化函数-----------------------------------
					void Init_Menue(MenuPage *page)
					{
						OLED_Init();//初始化LED
						OLED_Clear();//对LED请屏
						KeyQueue.first = 0;//初始化键值队列
						KeyQueue.last = 0;
						DataStack.top = -1;//初始化数据栈
						nowPage = page;//得到初始化页面
					}
					//-------------------------将按键的键值存入队列-----------------------------
					void KeyNumGet(int key)
					{
						IQueue(&KeyQueue, key);
					}
					void StringCopy(char *desition, char *source, char length)//copy一个字符串中的一定长度的数据到另一字符串
					{
						int i = 0;
						for (i = 0; i < length; i++)
						{
							*(desition++) = *(source++);
						}
					}
					//------------------------计算当前应该显示的行------------------------------
					int CountLine(int location)
					{
						return location - course->page_skewing;
					}
					//------------------------判断是否在可显示的行------------------------------
					int CanShow(int location)
					{
						int cm = location - course->page_skewing;
						return cm > 0 && cm < MAX_LINE + 1;
					}
					//------------------------画线函数-----------------------------------------
					void Draw_line(float X1, float Y1, float X2, float Y2)
					{
						int i = 0;
						if ((X2 - X1) != 0)//判断斜率是否存在
						{
							float k = (Y2 - Y1) / (X2 - X1);//得到直线的斜率
							float d = Y1 - k * X1;//得到与Y轴的夹角
							unsigned char length = abs((int)(X1 - X2)) + 1;//得到X轴方向绘制的长度
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
					//-------------------------------画矩形-----------------------------------------
					void Draw_Rectangle(char x, char y, char width, char height)
					{
						Draw_line(x, y, x + width, y);
						Draw_line(x, y, x, y + height);
						Draw_line(x, y + height, x + width, y + height);
						Draw_line(x + width, y, x + width, y + height);
					}
					//---------------------------------画圆-----------------------------------------
					void Draw_Circle(float x, float y, float R)
					{
						float angle = 0;//初始角度
						for (angle = 0; angle < 360; angle += 1)
						{
							OLED_DrawPoint(R*sin(angle*3.14 / 180) + x, y + R * cos(angle*3.14 / 180), 1);
						}
					}
					//---------------------------------画光标--------------------------------------
					void Draw_course(char x, char y)
					{
						if (y > 7)
						{
							y = 7;
						}
						OLED_ShowString(x, y, ">");
					}
					//--------------------------------得到键值-------------------------------------
					void Get_key(int allLine)
					{
						KeyNum = OQueue(&KeyQueue);
						if (KeyNum == KEY_DOWN)
						{
							course->set_y += 1;//光标指针加一
							if (allLine > MAX_LINE)
							{
								if (course->set_y > MAX_LINE)
								{
									course->set_y = MAX_LINE;
									course->page_skewing += 1;//页面指针偏移量加一
									if (course->page_skewing > (allLine - MAX_LINE))//限制页面指针偏移量的增加
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
									course->page_skewing -= 1;//页面偏移量减一
								}
							}
						}
						else if (KeyNum == kEY_BANK)//如果是返回键
						{
							if (nowPage->fatherPage != NULL)//如果有父页面
							{
								nowPage = nowPage->fatherPage;//改变页面
								Pop(&DataStack, course);//同时取出数据栈里面的数据
							}
						}
					}
					//--------------------------------显示文本----------------------------------------
					void Show_Text(char location, char *name, ...)
					{
						va_list vp;
						int d = 0; float f = 0;
						char *p;
						char ap[BUFF_LENGTH] = { 0 };
						char data[10] = { 0 };//用于储存数据
						if (!CanShow(location))return;//不在可显示的行直接退出
						va_start(vp, name);
						p = strstr(name, "%");
						if (p)
						{
							StringCopy(ap, name, p - name);//得到%前面的值
							p++;
							switch (*p)
							{
							case 'd':
							{d = va_arg(vp, int);//得到数据
							sprintf(data, "%d", d);//将数据转换成字符串
							break; }
							case 'f':
							{
								f = va_arg(vp, double);//得到数据
								sprintf(data, "%.2f", f);//讲数据转换成字符串
								break; }
							default:break;
							}
							strcat(ap, data);//连接两个字符串
							OLED_ShowString(10, CountLine(location), ap);//显示
						}
						else
						{
							OLED_ShowString(10, CountLine(location), name);//显示
						}
						va_end(vp);
					}
					//---------------------------------数值改变函数-------------------------------------------
					void Change_Data(char location, float *data, float StepNum)
					{
						if ((course->page_skewing + course->set_y) == location)//判断是否选中当前行
						{
							if (KeyNum == KEY_RIGHT)//如果键值是RIGHT则数据加
							{
								*data += StepNum;//数据加
							}
							if (KeyNum == kEY_LEFT)
							{
								*data -= StepNum;
							}
						}
					}
					//------------------------------数据清零函数------------------------------------------
					void Clear_Data(char location, uint16_t *data)
					{
						if ((course->page_skewing + course->set_y) == location)
						{
							if (KeyNum == KEY_RIGHT)//如果键值是RIGHT则数据加
							{
								*data = 0;
							}
						}
					}
					//-----------------------------将数据存入flash----------------------------------------
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
							if (KeyNum == kEY_OK)//如果键值是RIGHT则数据加
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
					//-----------------------------页面改变函数--------------------------------------------
					void Change_Page(char location, MenuPage *Page)
					{
						if (course->page_skewing + course->set_y == location)//判断是否选中当前行
						{
							if (KeyNum == kEY_OK)//是确定键
							{
								if (Page != NULL)
								{
									Push(&DataStack, *course);//进栈
									nowPage = Page;//改变页面
									course->page_skewing = 0;//光标初始化
									course->set_y = 1;
								}
							}
						}
					}
					//---------------------------------绘制页面-----------------------------------------------
					void Set_Courese(int allLine)//绘制页面并且设置光标的位置,入口为该页面所有的Show_Text()的行数
					{
						int set = 0;
						float sa = 0;
						Get_key(allLine);//得到键值
						set = strlen(nowPage->page);//得到标题的长度
						sa = (127 - (set - 1) * 6) / 2;
						Draw_line(0, 60, sa - 6, 60);
						OLED_ShowString(sa - 6, 0, "<");
						OLED_ShowString(sa + set * 6, 0, ">");
						OLED_ShowString(sa, 0, nowPage->page);//绘制标题
						Draw_line(sa + set * 6 + 6, 60, 128, 60);
						Draw_line(8, 0, 8, 63);
						Draw_course(0, course->set_y);
					}

