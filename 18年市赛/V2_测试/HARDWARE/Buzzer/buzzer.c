#include "buzzer.h"
#include "delay.h"

 /***************  ����LED�õ���I/O�� *******************/

void BUZZER_GPIO_Config(void)	
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE); // ʹ��PC�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	//ѡ���Ӧ������
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);  //��ʼ��PC�˿�
  GPIO_ResetBits(GPIOD, GPIO_Pin_3);	 // �ر�����LED
}

void BUZZER(u8 a)
{
	if (a)	
	{
		GPIO_SetBits(GPIOD,GPIO_Pin_4);
	}
	else		
		GPIO_ResetBits(GPIOD,GPIO_Pin_4);
	

}
void  song(u8 x)
{
	if(x>100) x=100;
	GPIO_SetBits(GPIOD,GPIO_Pin_4);
	delay_ms(x);
	GPIO_ResetBits(GPIOD,GPIO_Pin_4);
	delay_ms(100-x);
}
