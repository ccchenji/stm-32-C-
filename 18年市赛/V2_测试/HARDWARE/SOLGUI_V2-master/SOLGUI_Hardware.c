#include"SOLGUI_Type.h"
#include"SOLGUI_Config.h"
#include"SOLGUI_Hardware.h"

//*******************����Ļ����ͷ�ļ���*******************
#include "oled.h"


//##########################����Ҫ�û�ʵ�ֵĲ��֡�############################

void SOLGUI_Hardware_Init(void)
{
//=========���û�Ӳ����ʼ����ֲ����=======
	OLED_Init();

//========================================
}

void SOLGUI_Hardware_FillScreen(uint8_t GRAM[SCREEN_X_WIDTH][SCREEN_Y_PAGE])
{
//=========���û�Ӳ����Ļ��亯����ֲ����=======
	OLED_Fill(GRAM);
//========================================
}

void SOLGUI_Hardware_ClearScreen(void)
{
	OLED_Clear();
}



