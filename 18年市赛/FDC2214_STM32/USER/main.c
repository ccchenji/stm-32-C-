#include "stm32f10x.h"
#include "USART_1.h"
#include "Delay.h"
#include "IIC.h"
#include "FDC2214.h"
#include <stdio.h>
#include "fliter.h"
#include "mpu_usart.h"

extern double Data_Output;
int main(void)
{
    uint32_t date0, date1, date2, date3;
    uint32_t fre0, fre1, fre2, fre3;
     
    Delay_Init();
    USART1_Init(500000);
    IIC_Init();
    FDC2214_Init();
   
    while(1)
    { 
			
       FDC2214_GetChannelData(FDC2214_Channel_0, &date0);
        FDC2214_GetChannelData(FDC2214_Channel_1, &date1);
        FDC2214_GetChannelData(FDC2214_Channel_2, &date2);
        FDC2214_GetChannelData(FDC2214_Channel_3, &date3);
        
        fre0 = FDC2214_CalculateFrequency(FDC2214_Channel_0, date0);
        fre1 = FDC2214_CalculateFrequency(FDC2214_Channel_1, date1);
        fre2 = FDC2214_CalculateFrequency(FDC2214_Channel_2, date2);
        fre3 = FDC2214_CalculateFrequency(FDC2214_Channel_3, date3);
//				printf("%d,%d,%d,%d\r\n", fre0, fre1, fre2, fre3);
				
        
        //Delay_ms(50);
			
			 Data_Output=but_filter(fre0);
			mpu6050_send_data(fre0, Data_Output,fre1);
		 
    }
}




