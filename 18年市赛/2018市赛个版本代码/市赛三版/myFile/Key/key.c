#include "key.h"
void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);//ʹ��GPIOBʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
  GPIO_Init(GPIOD, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8
	
}
int KEY_Scan()
{
	if (KEY1 == 0 || KEY2 == 0 || KEY3 == 0 || KEY4 == 0|| KEY5==0|| KEY6==0)
	{
		delay_ms(30);
		if (KEY1 == 0) return 3;//���
		if (KEY2 == 0) return 2;//�¼�
		if (KEY3 == 0) return 4;//�Ҽ�
		if (KEY4 == 0) return 5;//ȷ��
		if (KEY5 == 0) return 1;//�ϼ�
		if (KEY6 == 0) return 6;//����
	}
	return 0;
}











