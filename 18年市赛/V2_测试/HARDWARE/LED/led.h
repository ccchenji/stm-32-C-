#ifndef __LED_H
#define __LED_H	 

#include "sys.h"
#include "pwm.h"
#include "adc.h"
#include "move.h"
#include "scan.h"
#include "buzzer.h"
#include "SOLGUI_Include.h"

#define LED0 PAout(8)	// PA8
#define LED1 PDout(2)	// PD2	

#define KEY_1 SOLGUI_KEY_LEFT //LEFT
#define KEY_2 SOLGUI_KEY_DOWN //DOWN
#define KEY_3 SOLGUI_KEY_RIGHT //RIGHT
#define KEY_4 SOLGUI_KEY_OK //OK
#define KEY_5 SOLGUI_KEY_UP //UP
#define KEY_6 SOLGUI_KEY_BACK //BACK
#define BEEP PDout(7) // BEEP,?????

void BEEP_Init(void); //???
void KEY_Init(void);
uint8_t Get_Key(void);
void LED_Init(void);
		 				    
#endif
