#include "menu.h"
#include "OLED.H"
#include "Queue.h"
#include "stack.h"
#include "dealDate.h"
#include "map.h"
extern float Mydata;
Queue KeyQueue;//键值队列
                                    MyStack DataStack;//数据栈
char KeyNum = 0;//全局的键值
Mycourse cour = { 0,1 ,0 };//初始化光标
Mycourse *course = &cour;//定义全局光标并初始化
MenuPage *nowPage;//当前的页面
MenuPage firstPage;//页面一

MenuPage mode1Page;//模式1
MenuPage mode2Page;//模式2
MenuPage mode3Page;//模式3
MenuPage mode4Page;//模式4
MenuPage gamePage;//模式5

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
 *   (((__) (__)))   高山仰止，景行行止，虽不能至，心往向之
 */


extern int studyFlag;
extern int mode1Flag;
extern int mode1End;//模式1的结果标志位 
char *end1Data="nothing";

extern int mode2Flag;//模式2标志位
extern int mode2End;//模式2的结果标志位

extern int studyHandFlag;//学习手势
extern int studyNumFlag;//学习数字


extern int gameFlag;//游戏开始标志位
extern StructGame gameEndFlag;//游戏结果

int nowNum=0;



extern uint32_t date0;
extern uint32_t date1;
extern uint32_t date2;
extern uint32_t date3;


extern int learnTime;//学习时间
//------------------------想显示的东西放到这里--------------------------------
/*------------------------------模式选择--------------------------*/
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
/*-------------------------------判断手势--------------------------*/	
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
/*-----------------------------判断数字----------------------------*/
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
/*---------------------------学习手势---------------------------------*/
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
/*-------------------------学习数字---------------------------*/
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
/*---------------------------------猜拳游戏------------------------------------*/
_Menue(gamePage, "GAME", &firstPage,
	{
		Get_key(1);//得到键值
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
/*-----------------------画图函数------------------------------------*/
	void Draw_Picture(char x,char y,char width,char height,unsigned char BMP[])//水平扫描，从左向右
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
	void Change_Data(char location, int *data)
	{
		if ((course->page_skewing + course->set_y) == location)//判断是否选中当前行
		{
			if (KeyNum == KEY_RIGHT)//如果键值是RIGHT则数据加
			{
				*data += STEPNUM;//数据加
			}
			if (KeyNum == kEY_LEFT)
			{
				*data -= STEPNUM;
			}
		}
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
		sa = (127 - (set-1) * 6) / 2;
		Draw_line(0, 60, sa - 6, 60);
		OLED_ShowString(sa - 6, 0, "<");
		OLED_ShowString(sa + set * 6, 0, ">");
		OLED_ShowString(sa, 0, nowPage->page);//绘制标题
		Draw_line(sa + set * 6 + 6, 60, 128, 60);
		Draw_line(8, 0, 8, 63);
		Draw_course(0, course->set_y);
	}

