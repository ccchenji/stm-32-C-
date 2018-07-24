实验器材:
	MiniSTM32F103开发板V3版本
	
实验目的:
	学习定时器的PWM功能
	
硬件资源:
	1,DS0(连接在PA8) 
	2,定时器1(TIM1),使用TIM1的通道1(CH1),开启部分重映射,将TIM1_CH1输出到PA8.
	从而实现PWM输出控制DS0亮度.
	
实验现象:
	本实验,DS0由暗到亮,再由亮到暗,再由暗到亮,依次循环.
	
注意事项:
	无.  


					正点原子@ALIENTEK
					2014-3-06
					广州市星翼电子科技有限公司
					电话：020-38271790
					传真：020-36773971
					购买：http://shop62103354.taobao.com
					http://shop62057469.taobao.com
					公司网站：www.alientek.com
					技术论坛：www.openedv.com
					
					
    ADC_RegularChannelConfig(ADC1,ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_7, 10, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2, 2, ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ADC1,ADC_Channel_3, 3, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_4, 4, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_6, 5, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_5, 11, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1, 6, ADC_SampleTime_239Cycles5);
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_9, 7, ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ADC1,ADC_Channel_10,7, ADC_SampleTime_239Cycles5);
	//ADC_RegularChannelConfig(ADC1,ADC_Channel_11,1, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_12,8, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_14,9, ADC_SampleTime_239Cycles5);