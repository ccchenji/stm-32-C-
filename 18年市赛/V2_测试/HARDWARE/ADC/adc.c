 #include "adc.h"
 #include "delay.h"
 #include "stm32f10x_dma.h"
__IO uint32_t ADC1_Buff[10];	   																   

void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC |RCC_APB2Periph_ADC1	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M                     
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_1|GPIO_Pin_7|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	ADC_DeInit(ADC1);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 14;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   
  	ADC_RegularChannelConfig(ADC1,ADC_Channel_0, 10, ADC_SampleTime_239Cycles5);//A0
 	ADC_RegularChannelConfig(ADC1,ADC_Channel_1, 9, ADC_SampleTime_239Cycles5);//A1
 	ADC_RegularChannelConfig(ADC1,ADC_Channel_2, 8, ADC_SampleTime_239Cycles5);//A2
  	ADC_RegularChannelConfig(ADC1,ADC_Channel_3, 7, ADC_SampleTime_239Cycles5);//A3
	ADC_RegularChannelConfig(ADC1,ADC_Channel_4, 6, ADC_SampleTime_239Cycles5);//A4
	ADC_RegularChannelConfig(ADC1,ADC_Channel_5, 5, ADC_SampleTime_239Cycles5);//A5
	ADC_RegularChannelConfig(ADC1,ADC_Channel_6, 4, ADC_SampleTime_239Cycles5);//A6
	ADC_RegularChannelConfig(ADC1,ADC_Channel_7, 3, ADC_SampleTime_239Cycles5);//A7
    ADC_RegularChannelConfig(ADC1,ADC_Channel_10,14, ADC_SampleTime_239Cycles5);//C0
	ADC_RegularChannelConfig(ADC1,ADC_Channel_11,13, ADC_SampleTime_239Cycles5);//C1
	ADC_RegularChannelConfig(ADC1,ADC_Channel_12,12, ADC_SampleTime_239Cycles5);//C2
	ADC_RegularChannelConfig(ADC1,ADC_Channel_13,11, ADC_SampleTime_239Cycles5);//C3
	ADC_RegularChannelConfig(ADC1,ADC_Channel_14,2, ADC_SampleTime_239Cycles5);//C4
	ADC_RegularChannelConfig(ADC1,ADC_Channel_15,1, ADC_SampleTime_239Cycles5);//C5
  	ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	ADC_StartCalibration(ADC1);	 //����ADУ׼
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������

}				  



























