#ifndef _IIC_H
#define _IIC_H

#include "stm32f10x.h"

//IO方向设置
#define SDA_IN()  {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=8<<12;}
#define SDA_OUT() {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=3<<12;}
//IO操作
#define IIC_SCL(n)  (n?GPIO_SetBits(GPIOC,GPIO_Pin_12):GPIO_ResetBits(GPIOC,GPIO_Pin_12)) //SCL PC12
#define IIC_SDA(n)  (n?GPIO_SetBits(GPIOC,GPIO_Pin_11):GPIO_ResetBits(GPIOC,GPIO_Pin_11)) //SDA PC11
#define READ_SDA    GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11)  //输入SDA

//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(uint8_t txd);			//IIC发送一个字节
uint8_t IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
uint8_t IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

uint8_t I2C_Write_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf);
uint8_t I2C_Read_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf);
uint8_t I2C_Write_Byte(uint8_t addr,uint8_t reg,uint8_t data);
uint8_t I2C_Read_Byte(uint8_t addr,uint8_t reg);
#endif

