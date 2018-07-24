#ifndef _menu_H
#define _menu_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include "stmflash.h"

#define PAGE_NULL NULL//无页面 
#define MAX_LINE 7//屏幕显示的最大的行数
#define BUFF_LENGTH 20//缓冲数组的长度

#define KEY_UP 1
#define KEY_DOWN 2
#define kEY_LEFT 3
#define KEY_RIGHT 4
#define kEY_OK 5
#define kEY_BANK 6


#define STEPNUM 0.01 //数据的当前步进值
#define STEPNUMF 1.00 

typedef struct Course//定义光标
{
	int all_Line;//总行数
	int set_y;//光标的y坐标
	int page_skewing;//页面偏移量
}Mycourse;
typedef struct Menus
{
	char *page;//当前页面的名称
	struct Menus *fatherPage;//父页面
	void(*nowPage) (void);//该页面的内容
}MenuPage;

#define _Menue(name,pageName,fatherPage,program)\
void _##name(){program}                         \
MenuPage name ={pageName,fatherPage,_##name};


void Menue_Show(void);//显示当前页面
void Draw_line(float X1, float Y1, float X2, float Y2);
void Init_Menue(MenuPage *page);//初始化菜单
void StringCopy(char *desition, char *source, char length);
int CountLine(int location);//计算当前应该显示的行
int CanShow(int location);//判断是否在可显示的行
void Show_Text(char location, char *name, ...);
void Set_Courese(int allLine);//显示标题
void Draw_Rectangle(char x, char y, char width, char height);
void Draw_Circle(float x, float y, float R);
void Draw_course(char x, char y);
void KeyNumGet(int key);
void Get_key(int allLine);
void Change_Data(char location, float *data, float StepNum);
void Change_Page(char location, MenuPage *Page);
void Clear_Data(char location, uint16_t *data);
int Save_Data(char location, float data1, float data2, float data3);
#endif
