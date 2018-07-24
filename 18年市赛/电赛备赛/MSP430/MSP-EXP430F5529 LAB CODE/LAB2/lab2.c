//***************************************************************************//
//                                                                           //
//                         MSP-EXP430F5529 LAB CODE                          //
//                                                                           //
//                              lab2 - Cap App                               //
//                                                                           //
//***************************************************************************//
/*******************************************************************************
 *
 *  Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/
#include <stdint.h>
#include "msp430.h"
#include "HAL_PMM.h"
#include "HAL_UCS.h"
#include "HAL_Board.h"
#include "HAL_Buttons.h"
#include "HAL_Dogs102x6.h"
#include "HAL_Menu.h"
#include "HAL_Wheel.h"
#include "Clock.h"
#include "LPM.h"
#include "Random.h"
#include "PMM.h"
#include "Demo_Cube.h"
#include "CTS_Layer.h"
#include "stdlib.h"
#include "lab2.h"

static const char *const capMenuText[] = {
    "==LAB2:Cap App===",
    "1. CapLED ",
    "2. CapDemo ",
    "3. Simon",
};
char *itoa(int, char *, int);

// Forward Declared Function
void CapLED(void);
void CapDemo(void);
void simon(void);

/***************************************************************************//**
 * @brief  The menu of lab2.
 * @param  none
 * @return none
 ******************************************************************************/

void lab2(void)
{
	   uint8_t selection = 0;

	    buttonsPressed = 0;

	    Dogs102x6_clearScreen();

	    Dogs102x6_stringDraw(7, 0, "*S1=Enter S2=Esc*", DOGS102x6_DRAW_NORMAL);
	    selection = Menu_active((char **)capMenuText, 3);
	    if (buttonsPressed & BUTTON_S2);
	    else
	       switch (selection)
	        {
                case 1: CapLED(); break;           //����������ʾʵ�����
                case 2: CapDemo(); break;          //������������ͼ��ʾʵ�����
                case 3: simon(); break;            //Simon��Ϸʵ�����
	            default: break;
	        }
}

/***************************************************************************//**
 * @brief  CapLED.
 * @param  none
 * @return none
 ******************************************************************************/

void CapLED(void)
{
    uint8_t sliderPosition = 0;

    Board_ledOff(LED_ALL);                           //�ر�����LED
    Dogs102x6_clearScreen();
    buttonsPressed = 0;

    Dogs102x6_stringDraw(1, 0, " Slide Finger on ", DOGS102x6_DRAW_NORMAL);
    Dogs102x6_stringDraw(2, 0, "   Touch Pads    ", DOGS102x6_DRAW_NORMAL);

    TI_CAPT_Init_Baseline(&slider);                 //����������ʼ��

    while (!(buttonsPressed & BUTTON_S2))           //S2���������˳�����
    {
        sliderPosition = TI_CAPT_Slider(&slider);

        sliderPosition = (sliderPosition + 10) / 20;    //�õ���������λ��
        //���� ���ݴ�������λ�õ�����ӦLED
        switch (sliderPosition)
        {
            case 0: Board_ledOff(LED4 + LED5 + LED6 + LED7 + LED8);
                break;
            case 1: Board_ledOn(LED4);
                Board_ledOff(LED5 + LED6 + LED7 + LED8);
                break;
            case 2: Board_ledOn(LED4 + LED5);
                Board_ledOff(LED6 + LED7 + LED8);
                break;
            case 3: Board_ledOn(LED4 + LED5 + LED6);
                Board_ledOff(LED7 + LED8);
                break;
            case 4: Board_ledOn(LED4 + LED5 + LED6 + LED7);
                Board_ledOff(LED8);
                break;
            case 5: Board_ledOn(LED4 + LED5 + LED6 + LED7 + LED8);
                break;
            case (255 / 17):
                break;
        }
    }

    Board_ledOff(LED_ALL);
    Dogs102x6_clearScreen();
    buttonsPressed = 0;
}

/***************************************************************************//**
 * @brief  Allows user to select USB apps
 * @param  none
 * @return none
 ******************************************************************************/

void CapDemo(void)
{
    uint8_t quit = 0, spacing = 0, height = 0, height1 = 0, i;
    uint16_t deltaCount[5];

    Dogs102x6_clearScreen();

    buttonsPressed = 0;

    TI_CAPT_Init_Baseline(&slider);          //����������ʼ��
    buttonDebounce = 0;

    Dogs102x6_stringDraw(0, 0, "== Touch  Demo ==", DOGS102x6_DRAW_NORMAL);

    //menu active until selection is made
    while (!quit)
    {
        TI_CAPT_Custom(&slider, deltaCount);  //�������ݴ������仯

        // 5 = No. of sensors
        for (i = 0; i < 5; i++)
        {
            spacing = 20 * i + 10;

            if (deltaCount[i] < 4000)
                height = 63 - deltaCount[i] / 60;   //���õ�i�鴫�������ݵõ��������θ߶�
            else
                height = 10;

            // �����еĸ߶�
            if (height < 10)
                height = 10;

            // ÿ�������ؿ�������������ʾLCD�Ͼ���ͼ���еĵ�1��3��5��7��9��
            Dogs102x6_verticalLineDraw(63, height, spacing - 1, DOGS102x6_DRAW_NORMAL);
            Dogs102x6_verticalLineDraw(63, height, spacing, DOGS102x6_DRAW_NORMAL);
            Dogs102x6_verticalLineDraw(63, height, spacing + 1, DOGS102x6_DRAW_NORMAL);

            __delay_cycles(1000);


            Dogs102x6_verticalLineDraw(height, 8, spacing, DOGS102x6_DRAW_INVERT);
            Dogs102x6_verticalLineDraw(height, 8, spacing - 1, DOGS102x6_DRAW_INVERT);
            Dogs102x6_verticalLineDraw(height, 8, spacing + 1, DOGS102x6_DRAW_INVERT);

            if (i < 4)
            {
                //for the "in between" heights
                if (deltaCount[i + 1] < 2400)
                    height1 = 63 - deltaCount[i + 1] / 40;
                else
                    height1 = 10;

                // Limit the height of the columns
                if (height + height1 < 10)
                    height1 = 10;
                // ÿ�������ؿ�������������ʾLCD�Ͼ���ͼ���еĵ�2��4��6��8��
                Dogs102x6_verticalLineDraw(63, (height + height1) / 2, (spacing + 10),
                                           DOGS102x6_DRAW_NORMAL);
                Dogs102x6_verticalLineDraw(63, (height + height1) / 2, (spacing + 11),
                                           DOGS102x6_DRAW_NORMAL);
                Dogs102x6_verticalLineDraw(63, (height + height1) / 2, (spacing + 9),
                                           DOGS102x6_DRAW_NORMAL);

                __delay_cycles(1000);

                Dogs102x6_verticalLineDraw((height + height1) / 2, 8, (spacing + 11),
                                           DOGS102x6_DRAW_INVERT);
                Dogs102x6_verticalLineDraw((height + height1) / 2, 8, (spacing + 10),
                                           DOGS102x6_DRAW_INVERT);
                Dogs102x6_verticalLineDraw((height + height1) / 2, 8, (spacing + 9),
                                           DOGS102x6_DRAW_INVERT);
            }
        }

        if ((buttonsPressed & BUTTON_S2))
            quit = 1;
    }

    Board_ledOff(LED_ALL);
    Dogs102x6_clearScreen();
    buttonDebounce = 1;
    buttonsPressed = 0;
}
// Simon Game
void simon(void)
{
    uint8_t turn = 0, quit = 0, i;
    struct Element *user;

    char turndisp[2];
    //array of Simon moves
    uint8_t lights[20];

    Dogs102x6_clearScreen();
    Dogs102x6_stringDraw(0, 0, "   Simon Says:   ", DOGS102x6_DRAW_NORMAL);

    buttonsPressed = 0;

    // Initialize Cap Touch
    TI_CAPT_Init_Baseline(&slider);       //��ʼ����������

    //initialize Simon's moves
    for (i = 0; i < 20; i++) lights[i] = 0;

    // Seed the random number generator with the current UCS FLL settings + i
    srand(UCSCTL0 + i);                  //���������������

    //menu active until selection is made
    while (!quit)
    {
        turn = turn + 1;                //ÿ�ɹ�һ�Σ�����������һ

        Dogs102x6_stringDraw(1, 0, "     MY TURN!    ", DOGS102x6_DRAW_NORMAL);
        __delay_cycles(11000000);
        //�����������������ϵͳ�������LED
        for (i = 0; i < turn; i++)
        {
            //random number from 0-4, add to Simon array
            if (i >= (turn - 1)) lights[i] = rand() % 5;

            // Overall delay between button blinks
            __delay_cycles(8000000);

            //display Simon array according to values 0-4
            if (lights[i] == 0)
            {
                Board_ledOn(LED4);
                //display so lights are slow enough for user to see
                __delay_cycles(11000000);
                //turn of LED after display
                Board_ledOff(LED4);
            }
            if (lights[i] == 1)
            {
                Board_ledOn(LED5);
                __delay_cycles(11000000);
                Board_ledOff(LED5);
            }
            if (lights[i] == 2)
            {
                Board_ledOn(LED6);
                __delay_cycles(11000000);
                Board_ledOff(LED6);
            }
            if (lights[i] == 3)
            {
                Board_ledOn(LED7);
                __delay_cycles(11000000);
                Board_ledOff(LED7);
            }
            if (lights[i] == 4)
            {
                Board_ledOn(LED8);
                __delay_cycles(11000000);
                Board_ledOff(LED8);
            }
        }

        Dogs102x6_stringDraw(1, 0, "   YOUR TURN!    ", DOGS102x6_DRAW_NORMAL);
        //����ϵͳ����LED��˳�򣬴�����Ӧ������������������ӦLED
        for (i = 0; i < turn; i++)
        {
            // wait for any user input
            while ((user = (struct Element *)TI_CAPT_Buttons(&slider)) == 0) ;  //�ȴ����ݰ���������
            // �ر�����LED
            Board_ledOff(LED4);
            Board_ledOff(LED5);
            Board_ledOff(LED6);
            Board_ledOff(LED7);
            Board_ledOff(LED8);

            // ����������������ϵͳSimon������Ƚ�
            if (lights[i] == 0)
            {
                // �����ȷ��������ӦLED���ӳٺ�ر�
                if (user == (struct Element *)&element0)
                {
                    Board_ledOn(LED4);
                    // display so lights are slow enough for user to see
                    __delay_cycles(7000000);
                    // turn of LED after display
                    Board_ledOff(LED4);
                }
                // ��������˳�
                else
                {
                    quit = 1;
                }
            }
            else if (lights[i] == 1)
            {
                if (user == (struct Element *)&element1)
                {
                    Board_ledOn(LED5);
                    // display so lights are slow enough for user to see
                    __delay_cycles(7000000);
                    // turn of LED after display
                    Board_ledOff(LED5);
                }
                else
                {
                    quit = 1;
                }
            }
            else if (lights[i] == 2)
            {
                if (user == (struct Element *)&element2)
                {
                    Board_ledOn(LED6);
                    // display so lights are slow enough for user to see
                    __delay_cycles(7000000);
                    // turn of LED after display
                    Board_ledOff(LED6);
                }
                else
                {
                    quit = 1;
                }
            }
            else if (lights[i] == 3)
            {
                if (user == (struct Element *)&element3)
                {
                    Board_ledOn(LED7);
                    // display so lights are slow enough for user to see
                    __delay_cycles(7000000);
                    // turn of LED after display
                    Board_ledOff(LED7);
                }
                else
                {
                    quit = 1;
                }
            }
            else if (lights[i] == 4)
            {
                if (user == (struct Element *)&element4)
                {
                    Board_ledOn(LED8);
                    // display so lights are slow enough for user to see
                    __delay_cycles(7000000);
                    // turn of LED after display
                    Board_ledOff(LED8);
                }
                else
                {
                    quit = 1;
                }
            }
            while ((struct Element *)TI_CAPT_Buttons(&slider) == user) ;

            // �������ֱ���˳�
            if (quit)
                break;
        }
        //��һ�����бȽ��У����������������µ�˳����ϵͳSimon������е�˳����ͬ������ʾ"GOOD JOB!"
        if (!quit){
            // good job if theyre right
            Dogs102x6_stringDraw(1, 0, "    GOOD JOB!   ", DOGS102x6_DRAW_NORMAL);
            __delay_cycles(24000000);
        }
    }
    // ���������ʾ"WRONG!"
    Dogs102x6_stringDraw(1, 0, "       WRONG!    ", DOGS102x6_DRAW_NORMAL);
    __delay_cycles(24000000);

    //��ʾ�ɹ�����
    Dogs102x6_stringDraw(6, 0, "YOU LASTED       ", DOGS102x6_DRAW_NORMAL);
    //character from integer for number of turns
    itoa(turn, turndisp, 10);
    Dogs102x6_stringDrawXY(66, 48, turndisp, DOGS102x6_DRAW_NORMAL);
    if (turn > 1) Dogs102x6_stringDraw(7, 0, "TURNS            ", DOGS102x6_DRAW_NORMAL);
    else Dogs102x6_stringDraw(7, 0, "TURN            ", DOGS102x6_DRAW_NORMAL);
    __delay_cycles(54000000);

    Board_ledOff(LED_ALL);
    Dogs102x6_clearScreen();
    buttonDebounce = 1;
}


