#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <conio.h>
#include "windows.h"
#include "time.h"
void gotoxy(int x, int y);
void HideCursor();
void snake_run();
void Get_flag();
void Get_map();
void foods();
void menu();
void snake_nature();
int live_or_die();
//蛇的长度 
int len = 1;
//蛇头的位置坐标 
int x = 6;
int y = 6;
//判断那个按键被按下 
char ch = '\0';
//蛇的位置坐标 
int snake_x[100] = { 6 };
int snake_y[100] = { 6 };
//食物的坐标 
int food_x = 25;
int food_y = 10;
//蛇自己行走的时间 
int timer = 0;
//蛇行走的方向标志位
short flag_x_go = 1;
short flag_x_bank = 0;
short flag_y_go = 0;
short flag_y_bank = 0;
//开始界面的标志位
short flag_menu = 0;
//切换界面的标志位
short flag_change = 0;
int main()
{
	//蛇的初始位置 
	gotoxy(x, y);
	printf("*");
	gotoxy(food_x, food_y);
	printf("*");
	//更新地图 
	Get_map();
	HideCursor();
	while (1)
	{
		if (flag_change == 0)
		{
			menu();
		}
		if (flag_change == 1)
		{
			snake_run();
			if (live_or_die())
			{
				//死亡后全部初始化 
				flag_change = 0;
				x = 6;
				y = 6;
				len = 1;
				getch();
				system("CLS");
				Get_map();
			}
			snake_nature();
			gotoxy(food_x, food_y);
			printf("*");
		}
		if (flag_change == 2)
		{
			break;
		}
	}
	system("CLS");
	printf("请提游戏意见给陈济轩");
	return 0;

}
//游戏开始界面
void menu()
{
	if (flag_menu == 0)
	{
		gotoxy(24, 14);
		printf("->GAME STAR");
		gotoxy(24, 15);
		printf("  GAME END");
	}
	else
	{
		gotoxy(24, 14);
		printf("  GAME STAR");
		gotoxy(24, 15);
		printf("->GAME END");
	}
	if (kbhit())
	{
		ch = getch();
		switch (ch)
		{
		case 13:
			if (flag_menu == 0)
			{
				flag_change = 1;
				system("CLS");
				Get_map();
			}
			if (flag_menu == 1)
			{
				flag_change = 2;
			}
			break;
		case 72:
			flag_menu = 0; break;
		case 80:
			flag_menu = 1; break;
		default: break;
		}
	}
}
//获得蛇的食物
void foods()
{
	int i = 0;
	srand((unsigned int)time(NULL));
	food_x = rand() % 48 + 6;
	food_y = rand() % 18 + 6;
	//防止食物出现在自己身上 
	for (i = 0; i < len; i++)
	{
		if ((food_x == snake_x[i]) && (food_y == snake_y[i]))
		{
			food_x = rand() % 48 + 6;
			food_y = rand() % 18 + 6;
			i = -1;
		}
	}
}
//判断蛇的死亡
int live_or_die()
{
	short i = 0;
	//蛇吃到自己的身体或撞到墙 
	for (i = 1; i < len - 1; i++)
	{
		if (((x == snake_x[i]) && (y == snake_y[i])))
		{
			system("CLS");
			Get_map();
			gotoxy(24, 14);
			printf("GAME OVER!!!");
			return 1;
		}
	}
	if (x == 5 || x == 54 || y == 5 || y == 24)
	{
		system("CLS");
		Get_map();
		gotoxy(24, 14);
		printf("GAME OVER!!!");
		return 1;
	}
	return 0;
}
//更新显示整条蛇 
void snake_nature()
{
	int i = 0;
	int x_end = 0;
	int y_end = 0;
	if ((x == food_x) && (y == food_y))
	{
		foods();
		len++;
	}
	snake_x[len] = x;
	snake_y[len] = y;
	x_end = snake_x[0];
	y_end = snake_y[0];
	gotoxy(x_end, y_end);
	printf(" ");
	for (i = 0; i < len; i++)
	{
		snake_x[i] = snake_x[i + 1];
		snake_y[i] = snake_y[i + 1];
	}
	for (i = 0; i < len; i++)
	{
		gotoxy(snake_x[len - 1 - i], snake_y[len - 1 - i]);
		printf("*");
	}
}

//让蛇自己行走 
void snake_run()
{
	while (1)
	{
		timer++;
		if (timer >= 90999000)
		{
			Get_flag();
			if (flag_x_go == 1)
			{
				x += 1;
			}
			if (flag_x_bank == 1)
			{
				x -= 1;
			}
			if (flag_y_go == 1)
			{
				y += 1;
			}
			if (flag_y_bank == 1)
			{
				y -= 1;
			}
			timer = 0;
			break;
		}
	}
}
//得到蛇的放向 
void Get_flag()
{
	if (kbhit())
	{
		getch();
		ch = getch();
		switch (ch)
		{
			//上 
		case 72:
			if (flag_x_go == 1 || flag_x_bank == 1)
			{
				flag_x_go = 0;
				flag_x_bank = 0;
				flag_y_go = 0;
				flag_y_bank = 1;
			}break;
			//下 
		case 80:
			if (flag_x_go == 1 || flag_x_bank == 1)
			{
				flag_x_go = 0;
				flag_x_bank = 0;
				flag_y_go = 1;
				flag_y_bank = 0;
			}break;
			//左 
		case 75:
			if (flag_y_go == 1 || flag_y_bank == 1)
			{
				flag_x_go = 0;
				flag_x_bank = 1;
				flag_y_go = 0;
				flag_y_bank = 0;
			}break;
			//右 
		case 77:
			if (flag_y_go == 1 || flag_y_bank == 1)
			{
				flag_x_go = 1;
				flag_x_bank = 0;
				flag_y_go = 0;
				flag_y_bank = 0;
			}break;
		default:
			break;
		}
	}
}
//得到地图 
void Get_map()
{
	int i = 0;
	int j = 0;
	for (i = 5; i < 25; i++)
	{
		for (j = 5; j < 55; j++)
		{
			if (i == 5 || i == 24 || j == 5 || j == 54)
			{
				gotoxy(j, i);
				printf(".");
			}
		}
	}
}
//设定光标的位置 
void gotoxy(int x, int y) //goto语句
{
	COORD pos;
	pos.X = x - 1;
	pos.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//隐藏光标 
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
