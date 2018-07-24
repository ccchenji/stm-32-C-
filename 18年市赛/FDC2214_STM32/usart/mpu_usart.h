#ifndef __MPU_USART_H_ 
#define __MPU_USART_H_
#include "stm32f10x.h"

//#include "sys.h"
#include "stm32f10x.h"
void usart1_send_char(u8 c);
void usart1_niming_report(u8 fun,u8*data,u8 len);
void mpu6050_send_data(float pitch,float roll,float yaw);
void usart1_report_imu(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz,short roll,short pitch,short yaw);
void MPU6050_GestureTypeDefInit(void);
void get_date(void);
void mpu_Init(void);
void send_data(short pitch,short roll,short pid1,short pid2,short gyroy,short gyroz);
#endif








