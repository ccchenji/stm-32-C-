 #include "adc.h"
 #include "delay.h"
 #include "stm32f10x_dma.h"
__IO uint32_t ADC1_Buff[10];	   																   

void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC |RCC_APB2Periph_ADC1	, ENABLE );	  //使能ADC1通道时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M                     
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_1|GPIO_Pin_7|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	ADC_DeInit(ADC1);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 14;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   
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
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	ADC_ResetCalibration(ADC1);	//使能复位校准  
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	ADC_StartCalibration(ADC1);	 //开启AD校准
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能

}				  



























