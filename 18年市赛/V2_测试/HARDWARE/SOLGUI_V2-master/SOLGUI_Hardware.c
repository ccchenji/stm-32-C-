#include"SOLGUI_Type.h"
#include"SOLGUI_Config.h"
#include"SOLGUI_Hardware.h"

//*******************【屏幕驱动头文件】*******************
#include "oled.h"


//##########################【需要用户实现的部分】############################

void SOLGUI_Hardware_Init(void)
{
//=========【用户硬件初始化移植处】=======
	OLED_Init();

//========================================
}

void SOLGUI_Hardware_FillScreen(uint8_t GRAM[SCREEN_X_WIDTH][SCREEN_Y_PAGE])
{
//=========【用户硬件屏幕填充函数移植处】=======
	OLED_Fill(GRAM);
//========================================
}

void SOLGUI_Hardware_ClearScreen(void)
{
	OLED_Clear();
}



