/**
* @brief       FDC2214 Driver 
* @harfware    stm32f1 
* @version     V1.0
* @date        19-June-2018
* @author      Junqi Liu
* 
*/

#include "FDC2214.h"

//新驱动宏
#define PI 3.14159265358979323846
#define ClockFrequency   40000000 //时钟频率

uint8_t CHx_FIN_SEL[4];
double fREFx[4]; 


extern I2C_HandleTypeDef hi2c1;

#ifdef NEW_LIB_SOFT   //整理后驱动

/*!
 *  @brief      IIC写FDC2214
 *  @param      Slve_Addr     器件地址
 *  @param      reg           寄存器
 *  @param      data          数据
 *  @since      v1.0
 *  Sample usage:       FDC2214_Write16(FDC2214_Addr, FDC2214_CONFIG, 0xFFFF);
 */
void FDC2214_Write16(uint8_t Slve_Addr, uint8_t reg, uint16_t data)
{
    MyIIC_Start();
    MyIIC_SendByte(Slve_Addr << 1);
    MyIIC_WaitAck();
    MyIIC_SendByte(reg);
    MyIIC_WaitAck();
    MyIIC_SendByte(data >> 8);
    MyIIC_WaitAck();
    MyIIC_SendByte(data & 0xFF);
    MyIIC_WaitAck();
    MyIIC_Stop();
}

/*!
 *  @brief      IIC读FDC2214
 *  @param      Slve_Addr     器件地址
 *  @param      reg           寄存器
 *  @return     寄存器值
 *  @since      v1.0
 *  Sample usage:       FDC2214_Read16(FDC2214_Addr, FDC2214_CONFIG);
 */
uint16_t FDC2214_Read16(uint8_t Slve_Addr, uint8_t reg)
{
    uint16_t temp;

    MyIIC_Start();
    MyIIC_SendByte(Slve_Addr << 1);
    MyIIC_WaitAck();
    MyIIC_SendByte(reg);
    MyIIC_WaitAck();
    MyIIC_Start();
    MyIIC_SendByte((Slve_Addr << 1) | 0x01);
    MyIIC_WaitAck();
    temp = (uint16_t)(MyIIC_ReadByte(1) << 8);
    temp |= MyIIC_ReadByte(0);
    MyIIC_Stop();
    
    return temp;
}

/*!
 *  @brief      读取FDC2214一个通道的转换值
 *  @param      channel     通道
 *  @param      *data       读取的数据
 *  @return     0：失败；1：成功
 *  @since      v1.0
 *  Sample usage:       FDC2214_GetChannelData(FDC2214_Channel_0, &CH0_DATA);
 */
uint8_t FDC2214_GetChannelData(FDC2214_channel_t channel, uint32_t *data)
{
    int16_t timeout = 100;
    uint8_t dateReg_H;
    uint8_t dateReg_L;
    uint8_t bitUnreadConv;
    uint16_t status;
    uint32_t dataRead;

    status = FDC2214_Read16(FDC2214_Addr, FDC2214_STATUS);//读取状态寄存器的值

    switch(channel)
    {
        case FDC2214_Channel_0:
            dateReg_H = FDC2214_DATA_CH0;
            dateReg_L = FDC2214_DATA_LSB_CH0;
            bitUnreadConv = 0x0008;
        break;

        case FDC2214_Channel_1:
            dateReg_H = FDC2214_DATA_CH1;
            dateReg_L = FDC2214_DATA_LSB_CH1;
            bitUnreadConv = 0x0004;
        break;

        case FDC2214_Channel_2:
            dateReg_H = FDC2214_DATA_CH2;
            dateReg_L = FDC2214_DATA_LSB_CH2;
            bitUnreadConv = 0x0002;
        break;

        case FDC2214_Channel_3:
            dateReg_H = FDC2214_DATA_CH3;
            dateReg_L = FDC2214_DATA_LSB_CH3;
            bitUnreadConv = 0x0001;
        break;
    }

    while(timeout && !(status & bitUnreadConv))//检查是否有未读数据
    {
        status = FDC2214_Read16(FDC2214_Addr, FDC2214_STATUS);
        timeout--;
    }
    if(timeout)
    {
        dataRead = (uint32_t)(FDC2214_Read16(FDC2214_Addr, dateReg_H) << 16);
        dataRead |= FDC2214_Read16(FDC2214_Addr, dateReg_L);
        *data = dataRead;

        return 1;
    }
    else
    {
        //超时
        return 0;
    }
}

/*!
 *  @brief      设置FDC2214一个通道的转换时间，转换时间(tCx)=(CHx_RCOUNT?16) / fREFx。
 *  @param      channel     通道
 *  @param      rcount      CHx_RCOUNT
 *  @since      v1.0
 *  Sample usage:       FDC2214_SetRcount(FDC2214_Channel_0, 0x0FFF);
 */
void FDC2214_SetRcount(FDC2214_channel_t channel, uint16_t rcount)
{
    if(rcount <= 0x00FF) return;

    switch(channel)
    {
        case FDC2214_Channel_0:
            FDC2214_Write16(FDC2214_Addr, FDC2214_RCOUNT_CH0, rcount);
        break;

        case FDC2214_Channel_1:
            FDC2214_Write16(FDC2214_Addr, FDC2214_RCOUNT_CH1, rcount);
        break;

        case FDC2214_Channel_2:
            FDC2214_Write16(FDC2214_Addr, FDC2214_RCOUNT_CH2, rcount);
        break;

        case FDC2214_Channel_3:
            FDC2214_Write16(FDC2214_Addr, FDC2214_RCOUNT_CH3, rcount);
        break;
    }
}

/*!
 *  @brief      设置FDC2214一个通道的建立时间，使LC传感器可以在通道x开始转换之前稳定下来，建立时间(tSx) = (CHx_SETTLECOUNT?16) ÷ fREFx。
                CHx_SETTLECOUNT = 0x00, 0x01时(tSx) = 32 ÷ fREFx。
 *  @param      channel     通道
 *  @param      count       CHx_SETTLECOUNT
 *  @since      v1.0
 *  @note       CHx_SETTLECOUNT > Vpk × fREFx × C × π^2 / (32 × IDRIVEX)
 *  Sample usage:       FDC2214_SetSettleCount(FDC2214_Channel_0, 0x00FF);
 */
void FDC2214_SetSettleCount(FDC2214_channel_t channel, uint16_t count)
{
    switch(channel)
    {
        case FDC2214_Channel_0:
            FDC2214_Write16(FDC2214_Addr, FDC2214_SETTLECOUNT_CH0, count);
        break;

        case FDC2214_Channel_1:
            FDC2214_Write16(FDC2214_Addr, FDC2214_SETTLECOUNT_CH1, count);
        break;

        case FDC2214_Channel_2:
            FDC2214_Write16(FDC2214_Addr, FDC2214_SETTLECOUNT_CH2, count);
        break;

        case FDC2214_Channel_3:
            FDC2214_Write16(FDC2214_Addr, FDC2214_SETTLECOUNT_CH3, count);
        break;
    }
}

/*!
 *  @brief      设置FDC2214一个通道的的时钟频率,
                差分传感器配置：
                0x01 -- 传感器频率0.01MHz和8.75MHz
                0x02 -- 传感器频率5MHz和10MHz
                单端传感器配置：
                0x01 -- 传感器频率0.01MHz和10MHz
 *  @param      channel               通道
 *  @param      frequency_select      时钟选择
 *  @param      divider               分频器，fREFx = fCLK / CHx_FREF_DIVIDER，
 *  @note       fREFx is > 4 × fSENSOR(外部LC振荡器频率)
 *  @since      v1.0
 *  Sample usage:       FDC2214_SetChannelClock(FDC2214_Channel_0, 0x01, 0xFF);
 */
void FDC2214_SetChannelClock(FDC2214_channel_t channel, uint8_t frequency_select, uint16_t divider)
{
    uint16_t temp = 0;

    temp = (uint16_t)(frequency_select << 12) | (divider & 0x03FF);

    CHx_FIN_SEL[channel] = frequency_select;//记录时钟选择
    fREFx[channel] = (double)ClockFrequency / divider;//记录时钟频率

    switch(channel)
    {
        case FDC2214_Channel_0:
            FDC2214_Write16(FDC2214_Addr, FDC2214_CLOCK_DIVIDERS_CH0, temp);
        break;

        case FDC2214_Channel_1:
            FDC2214_Write16(FDC2214_Addr, FDC2214_CLOCK_DIVIDERS_CH1, temp);
        break;

        case FDC2214_Channel_2:
            FDC2214_Write16(FDC2214_Addr, FDC2214_CLOCK_DIVIDERS_CH2, temp);
        break;

        case FDC2214_Channel_3:
            FDC2214_Write16(FDC2214_Addr, FDC2214_CLOCK_DIVIDERS_CH3, temp);
        break;
    }
}

/*!
 *  @brief      配置INTB引脚中断功能
 *  @param      mode      1：开中断；0：关中断
 *  @since      v1.0
 *  Sample usage:       FDC2214_SetDriveCurrent(FDC2214_Channel_0, FDC2214_Drive_Current_0_025);
 */
void FDC2214_SetINTB(uint8_t mode)
{
    uint16_t temp = 0;

    temp = FDC2214_Read16(FDC2214_Addr, FDC2214_CONFIG);
    temp &= 0xFF7F;
    if(mode)
        temp |= 0x0080;
    FDC2214_Write16(FDC2214_Addr, FDC2214_CONFIG, temp);

    temp = FDC2214_Read16(FDC2214_Addr, FDC2214_ERROR_CONFIG);
    temp &= 0xFFFE;
    if(mode)
        temp |= 0x0001;
    FDC2214_Write16(FDC2214_Addr, FDC2214_ERROR_CONFIG, temp);
}

/*!
 *  @brief      激活FDC2214的一个通道，单通道模式
 *  @param      channel     通道
 *  @since      v1.0
 *  Sample usage:       FDC2214_SetActiveChannel(FDC2214_Channel_0);
 */
void FDC2214_SetActiveChannel(FDC2214_channel_t channel)
{
    uint16_t temp = 0;
    temp = FDC2214_Read16(FDC2214_Addr, FDC2214_CONFIG);
    temp &= 0x3FFF;
    temp |= (uint16_t)(channel << 14);

    FDC2214_Write16(FDC2214_Addr, FDC2214_CONFIG, temp);
}

/*!
 *  @brief      设置FDC2214的工作模式：正常、睡眠。
 *  @param      mode     0：正常工作；1：睡激活模式选择。眠
 *  @since      v1.0
 *  Sample usage:       FDC2214_SetSleepMode(0);
 */
void FDC2214_SetSleepMode(uint8_t mode)
{
    uint16_t temp = 0;
    temp = FDC2214_Read16(FDC2214_Addr, FDC2214_CONFIG);
    temp &= 0xDFFF;
    if(mode)
        temp |= 0x2000;

    FDC2214_Write16(FDC2214_Addr, FDC2214_CONFIG, temp);
}

/*!
 *  @brief      FDC2214激活模式选择。
 *  @param      mode     0：全电流激活模式；1：低功率激活模式
 *  @since      v1.0
 *  Sample usage:       FDC2214_SetCurrentMode(1);
 */
void FDC2214_SetCurrentMode(uint8_t mode)
{
    uint16_t temp = 0;
    temp = FDC2214_Read16(FDC2214_Addr, FDC2214_CONFIG);
    temp &= 0xF7FF;
    if(mode)
        temp |= 0x800;

    FDC2214_Write16(FDC2214_Addr, FDC2214_CONFIG, temp);
}

/*!
 *  @brief      设置FDC2214时钟源
 *  @param      src     0：内部时钟源；1：外部时钟源
 *  @since      v1.0
 *  Sample usage:       FDC2214_SetClockSource(1);
 */
void FDC2214_SetClockSource(uint8_t src)
{
    uint16_t temp = 0;
    temp = FDC2214_Read16(FDC2214_Addr, FDC2214_CONFIG);
    temp &= 0xFDFF;
    if(src)
        temp |= 0x200;

    FDC2214_Write16(FDC2214_Addr, FDC2214_CONFIG, temp);
}

/*!
 *  @brief      高电流传感器驱动，只适用于单通道模式。
 *  @param      mode     0：正常（最大1.5mA）；1：高电流传感器驱动（>1.5mA）
 *  @since      v1.0
 *  Sample usage:       FDC2214_SetHighCurrentMode(0);
 */
void FDC2214_SetHighCurrentMode(uint8_t mode)
{
    uint16_t temp = 0;
    temp = FDC2214_Read16(FDC2214_Addr, FDC2214_CONFIG);
    temp &= 0xFFBF;
    if(mode)
        temp |= 0x40;

    FDC2214_Write16(FDC2214_Addr, FDC2214_CONFIG, temp);
}

/*!
 *  @brief      设置FDC2214的MUX CONFIG寄存器
 *  @param      autoscan      自动扫描模式 0：关闭，1：打开
 *  @param      channels      自动扫描通道
 *  @param      bandwidth     数字滤波器带宽，大于外部LC振荡器频率
 *  @since      v1.0
 *  Sample usage:       FDC2214_SetMUX_CONFIG(1, FDC2214_Channel_Sequence_0_1_2, FDC2214_Bandwidth_10M);
 */
void FDC2214_SetMUX_CONFIG(uint8_t autoscan, FDC2214_channel_sequence_t channels, FDC2214_filter_bandwidth_t bandwidth)
{
    uint16_t temp = 0;

    if(autoscan)
    {
        temp = (uint16_t)(autoscan << 15) | (channels << 13) | 0x0208 | bandwidth;
    }
    else
    {
        temp = 0x0208 | bandwidth;
    }

    FDC2214_Write16(FDC2214_Addr, FDC2214_MUX_CONFIG, temp);
}

/*!
 *  @brief      传感器复位
 *  @since      v1.0
 *  Sample usage:       FDC2214_Reset();
 */
void FDC2214_Reset(void)
{
    FDC2214_Write16(FDC2214_Addr, FDC2214_RESET_DEV, 0x8000);
}

/*!
 *  @brief      设置FDC2214的一个通道传感器驱动电流，确保振荡幅度在1.2V和1.8V之间。
 *  @param      channel      通道
 *  @param      current      电流大小
 *  @since      v1.0
 *  Sample usage:       FDC2214_SetDriveCurrent(FDC2214_Channel_0, FDC2214_Drive_Current_0_025);
 */
void FDC2214_SetDriveCurrent(FDC2214_channel_t channel, FDC2214_drive_current_t current)
{
    uint16_t temp = 0;
    temp = (uint16_t)(current << 11);

    switch(channel)
    {
        case FDC2214_Channel_0:
            FDC2214_Write16(FDC2214_Addr, FDC2214_DRIVE_CURRENT_CH0, temp);
        break;

        case FDC2214_Channel_1:
            FDC2214_Write16(FDC2214_Addr, FDC2214_DRIVE_CURRENT_CH1, temp);
        break;

        case FDC2214_Channel_2:
            FDC2214_Write16(FDC2214_Addr, FDC2214_DRIVE_CURRENT_CH2, temp);
        break;

        case FDC2214_Channel_3:
            FDC2214_Write16(FDC2214_Addr, FDC2214_DRIVE_CURRENT_CH3, temp);
        break;
    }
}

/*!
 *  @brief      计算频率
 *  @param      channel      通道
 *  @param      datax        读取的转换值
 *  @return     频率，单位Hz
 *  @since      v1.0
 *  Sample usage:       FDC2214_CalculateFrequency(FDC2214_Channel_0, 0xFF);
 */
double FDC2214_CalculateFrequency(FDC2214_channel_t channel, uint32_t datax)
{
    double frequency = 0.0;

    frequency = (double)(CHx_FIN_SEL[channel] * fREFx[channel] * datax) / 268435456.0;//2^28

    return frequency;
}

/*!
 *  @brief      计算外部电容大小
 *  @param      frequency      频率大小，单位Hz
 *  @param      inductance     板载电感大小，单位uH
 *  @param      capacitance    板载电容大小，单位pF
 *  @return     外部电容大小，单位pF
 *  @since      v1.0
 *  Sample usage:       FDC2214_CalculateCapacitance(FDC2214_Channel_0, 6000000, 18, 33);
 */
double FDC2214_CalculateCapacitance(double frequency, float inductance, float capacitance)
{
    double cap = 0.0;

    cap = (double)(1.0 / (inductance * (2 * PI * frequency) * (2 * PI * frequency)));

    return cap;
}

/*!
 *  @brief      FDC2214初始化函数
 *  @return     1：成功；0：失败
 *  @since      v1.0
 *  Sample usage:       FDC2214_Init();
 */
uint8_t FDC2214_Init(void)
{
    uint16_t deviceID = 0;
    deviceID = FDC2214_Read16(FDC2214_Addr, FDC2214_DEVICE_ID);//读器件ID
    if(deviceID == FDC2214_ID)
    {
        FDC2214_Reset();
        FDC2214_SetRcount(FDC2214_Channel_0, 5000);//2000us 转换周期
        FDC2214_SetRcount(FDC2214_Channel_1, 5000);//2000us 转换周期
        FDC2214_SetRcount(FDC2214_Channel_2, 5000);//2000us 转换周期
        FDC2214_SetRcount(FDC2214_Channel_3, 5000);//2000us 转换周期
        FDC2214_SetSettleCount(FDC2214_Channel_0, 200);//200 cycles 等待时间
        FDC2214_SetSettleCount(FDC2214_Channel_1, 200);//200 cycles 等待时间
        FDC2214_SetSettleCount(FDC2214_Channel_2, 200);//200 cycles 等待时间
        FDC2214_SetSettleCount(FDC2214_Channel_3, 200);//200 cycles 等待时间
        FDC2214_SetChannelClock(FDC2214_Channel_0, 2, 1);//设置时钟分频，1分频，40MHz
        FDC2214_SetChannelClock(FDC2214_Channel_1, 2, 1);//设置时钟分频，1分频，40MHz
        FDC2214_SetChannelClock(FDC2214_Channel_2, 2, 1);//设置时钟分频，1分频，40MHz
        FDC2214_SetChannelClock(FDC2214_Channel_3, 2, 1);//设置时钟分频，1分频，40MHz
        FDC2214_SetINTB(1);//开启INTB中断
        //FDC2214_SetActiveChannel(FDC2214_Channel_0);//开启通道2
        FDC2214_SetCurrentMode(1);//低功率激活模式
        FDC2214_SetClockSource(1);//外部时钟源
        FDC2214_SetHighCurrentMode(0);//正常电流传感器驱动
        FDC2214_SetMUX_CONFIG(1, FDC2214_Channel_Sequence_0_1_2_3, FDC2214_Bandwidth_10M);//关闭自动扫描，10MHz带宽
        FDC2214_SetDriveCurrent(FDC2214_Channel_0, FDC2214_Drive_Current_0_081);//通道0驱动电流0.081mA
        FDC2214_SetDriveCurrent(FDC2214_Channel_1, FDC2214_Drive_Current_0_081);//通道1驱动电流0.081mA
        FDC2214_SetDriveCurrent(FDC2214_Channel_2, FDC2214_Drive_Current_0_081);//通道2驱动电流0.081mA
        FDC2214_SetDriveCurrent(FDC2214_Channel_3, FDC2214_Drive_Current_0_081);//通道3驱动电流0.081mA
        FDC2214_SetSleepMode(0);//退出睡眠状态，开始工作
        return 1;
    }

    return 0;
}


#endif




#ifdef SOFT_IIC
/**
*  @brief      FDC Read 1 byte 
*  @param      uint16_t address  
*  @return     uint8_t data;
*  @note	   	 根据数据手册，首先发送7位从设备地址，再发送8位寄存器地址，
然后发送从设备地址，然后读出两字节
发送设备地址+读写控制bit（0 = w， 1 = r) bit7 先传
*/
uint8_t FDC_Read8(uint16_t address) 
{
		uint8_t data;
		
		MyIIC_Start();
		MyIIC_SendByte(FDC2214_I2C_ADDR_0<<1);  //设备地址
		MyIIC_WaitAck();  //这里没有处理
		
		MyIIC_SendByte(address>>8);  //寄存器地址
		MyIIC_WaitAck();  //这里没有处理
	
		MyIIC_SendByte(address);  //寄存器地址
		MyIIC_WaitAck();  //这里没有处理
		
		MyIIC_Stop();
		
		MyIIC_Start();
		MyIIC_SendByte((FDC2214_I2C_ADDR_0<<1)+1);  //设备地址
		MyIIC_WaitAck();  
		
		data = MyIIC_ReadByte(0);

		
		MyIIC_Stop();
		return data;
}

/**
*  @brief      FDC Read 4 byte 
*  @param      uint8_t address  
*  @return     uint16_t data
*  @note	   	 根据数据手册，首先发送7位从设备地址，再发送8位寄存器地址，
然后发送从设备地址，然后读出两字节
发送设备地址+读写控制bit（0 = w， 1 = r) bit7 先传
*/
uint32_t FDC_Read32(uint8_t address) 
{
		uint32_t retVal = 0;
		uint16_t data;
		
		MyIIC_Start();
		MyIIC_SendByte(FDC2214_I2C_ADDR_0<<1);  //设备地址
		MyIIC_WaitAck();  //这里没有处理
		
		MyIIC_SendByte(address);  //寄存器地址
		MyIIC_WaitAck();  //这里没有处理
	
		MyIIC_Stop();
		
		MyIIC_Start();
		MyIIC_SendByte((FDC2214_I2C_ADDR_0<<1)+1);  //设备地址
		MyIIC_WaitAck();  
		
		data = MyIIC_ReadByte(1);
		retVal |= (uint32_t)data << 24; 
		data = MyIIC_ReadByte(1);
		retVal |= (uint32_t)data << 16; 
		data = MyIIC_ReadByte(1);
		retVal |= (uint32_t)data << 8; 
		data = MyIIC_ReadByte(0);
		retVal |= data;		
		
		MyIIC_Stop();
		return retVal;
}

/**
*  @brief      FDC Read 2 byte 
*  @param      uint8_t address  
*  @return     uint16_t data
*  @note	   	 根据数据手册，首先发送7位从设备地址，再发送8位寄存器地址，
然后发送从设备地址，然后读出两字节
发送设备地址+读写控制bit（0 = w， 1 = r) bit7 先传
*/
uint16_t FDC_Read16(uint8_t address) 
{
		uint16_t data;
		//while(1){
		MyIIC_Start();
		MyIIC_SendByte(FDC2214_I2C_ADDR_0<<1);  //设备地址  54
		MyIIC_WaitAck();  //这里没有处理
					
		
		MyIIC_SendByte(address);  //寄存器地址
		MyIIC_WaitAck();  //这里没有处理
	
		//MyIIC_Stop();
		
		MyIIC_Start();
		MyIIC_SendByte((FDC2214_I2C_ADDR_0<<1)+1);  //设备地址
		MyIIC_WaitAck();  
		//	}
		data = MyIIC_ReadByte(1);
		data <<= 8;
		data |= MyIIC_ReadByte(0);
		
		MyIIC_Stop();
		return data;
}

/**
*  @brief      write 1 byte to FDC 
*  @param      uint16_t address, uint8_t data
*  @return     none
*  @note	   	 
*/
void FDC_Write8(uint16_t address, uint8_t data)  
{
    MyIIC_Start();
		MyIIC_SendByte(FDC2214_I2C_ADDR_0<<1);  //设备地址
	  MyIIC_WaitAck();  //这里没有处理
	  
		MyIIC_SendByte(address>>8);  //寄存器地址
	  MyIIC_WaitAck();  //这里没有处理
		MyIIC_SendByte(address);  //寄存器地址
	  MyIIC_WaitAck();  //这里没有处理
	  
		MyIIC_SendByte(data);  //寄存器地址
	  MyIIC_WaitAck();  //这里没有处理
    
		MyIIC_Stop();
}

/**
*  @brief      write 2 bytes to FDC 
*  @param      uint16_t address, uint16_t data
*  @return     none
*  @note	   	 
*/
void FDC_Write16(uint16_t address, uint16_t data)  
{
    MyIIC_Start();
		MyIIC_SendByte(FDC2214_I2C_ADDR_0<<1);  //设备地址
	  MyIIC_WaitAck();  //这里没有处理
	  
		MyIIC_SendByte(address & 0xFF);  //寄存器地址
	  MyIIC_WaitAck();  //这里没有处理
	  
		MyIIC_SendByte(data>>8);  //寄存器地址
	  MyIIC_WaitAck();  //这里没有处理
	
		MyIIC_SendByte(data);  //寄存器地址
	  MyIIC_WaitAck();  //这里没有处理
    
		MyIIC_Stop();
}


// Gets 28bit reading for FDC2212 and FDC2214
// Takes in channel number, gives out the formatted 28 bit reading.
unsigned long FDC_GetReading28(uint8_t channel) {
    int timeout = 100;
    unsigned long reading = 0;
    //long long fsensor = 0;
    int status = FDC_Read16(FDC2214_STATUS);
    uint8_t addressMSB;
	uint8_t addressLSB;
	uint8_t bitUnreadConv;
	switch (channel){
		case (0):
			addressMSB = FDC2214_DATA_CH0_MSB;
			addressLSB = FDC2214_DATA_CH0_LSB;
			bitUnreadConv = FDC2214_CH0_UNREADCONV;
		break;
		case (1):
			addressMSB = FDC2214_DATA_CH1_MSB;
			addressLSB = FDC2214_DATA_CH1_LSB;
			bitUnreadConv = FDC2214_CH1_UNREADCONV;
		break;
		case (2):
			addressMSB = FDC2214_DATA_CH1_MSB;
			addressLSB = FDC2214_DATA_CH1_LSB;
			bitUnreadConv = FDC2214_CH1_UNREADCONV;
		break;
		case (3):
			addressMSB = FDC2214_DATA_CH1_MSB;
			addressLSB = FDC2214_DATA_CH1_LSB;
			bitUnreadConv = FDC2214_CH1_UNREADCONV;
		break;
		default: return 0;
	}
	
	while (timeout && !(status & FDC2214_CH0_UNREADCONV)) {
        status = FDC_Read16(FDC2214_STATUS);
        timeout--;
    }
    if (timeout == 100) {
// #####################################################################################################
// There was this weird double read, as "first readout could be stale" in Nelsons file. 
// I have not confirmed the existence of this silicon bug.
// I suspect that it might be due to crappy breadboard or rats nest wiring or lack of signal integrity for other reason
// 
// On the other hand, I have done far too little testing to be sure, so I am leaving that bit in for now.
//	
// #####################################################################################################
		//could be stale grab another //could it really it? ?????
        //read the 28 bit result
        reading = (uint32_t)(FDC_Read16(addressMSB) & FDC2214_DATA_CHx_MASK_DATA) << 16;
        reading |= FDC_Read16(addressLSB);
        while (timeout && !(status & FDC2214_CH0_UNREADCONV)) {
            status = FDC_Read16(FDC2214_STATUS);
            timeout--;
        }
    }
    if (timeout) {
        //read the 28 bit result
        reading = (uint32_t)(FDC_Read16(addressMSB) & FDC2214_DATA_CHx_MASK_DATA) << 16;
        reading |= FDC_Read16(addressLSB);
        return reading;
    } else {
		// Could not get data, chip readynes flag timeout
        return 0;
    }
}

// Gets 16bit reading for FDC2112 and FDC2114
// Takes in channel number, gives out the formatted 28 bit reading.
unsigned long FDC_GetReading16(uint8_t channel) {
    int timeout = 100;
    unsigned long reading = 0;
    //long long fsensor = 0;
    int status = FDC_Read16(FDC2214_STATUS);
    uint8_t addressMSB;
	uint8_t bitUnreadConv;
	switch (channel){
		case (0):
			addressMSB = FDC2214_DATA_CH0_MSB;
			bitUnreadConv = FDC2214_CH0_UNREADCONV;
		break;
		case (1):
			addressMSB = FDC2214_DATA_CH1_MSB;
			bitUnreadConv = FDC2214_CH1_UNREADCONV;
		break;
		case (2):
			addressMSB = FDC2214_DATA_CH1_MSB;
			bitUnreadConv = FDC2214_CH1_UNREADCONV;
		break;
		case (3):
			addressMSB = FDC2214_DATA_CH1_MSB;
			bitUnreadConv = FDC2214_CH1_UNREADCONV;
		break;
		default: return 0;
	}
	
	while (timeout && !(status & FDC2214_CH0_UNREADCONV)) {
        status = FDC_Read16(FDC2214_STATUS);
        timeout--;
    }
    if (timeout == 100) {
// #####################################################################################################
// There was this weird double read, as "first readout could be stale" in Nelsons file. 
// I have not confirmed the existence of this silicon bug.
// I suspect that it might be due to crappy breadboard or rats nest wiring or lack of signal integrity for other reason
// 
// On the other hand, I have done far too little testing to be sure, so I am leaving that bit in for now.
//	
// #####################################################################################################
		//could be stale grab another //could it really it? ?????
        //read the 28 bit result
        reading = (uint32_t)(FDC_Read16(addressMSB) & FDC2214_DATA_CHx_MASK_DATA) << 16;
        while (timeout && !(status & FDC2214_CH0_UNREADCONV)) {
            status = FDC_Read16(FDC2214_STATUS);
            timeout--;
        }
    }
    if (timeout) {
        //read the 16 bit result
        reading = (uint32_t)(FDC_Read16(addressMSB) & FDC2214_DATA_CHx_MASK_DATA) << 16;
        return reading;
    } else {
		// Could not get data, chip readynes flag timeout
		return 0;
    }
}


void FDC_LoadSettings(uint8_t chanMask, uint8_t autoscanSeq, uint8_t deglitchValue) {

	//Configuration register
	//	Active channel Select: b00 = ch0; b01 = ch1; b10 = ch2; b11 = ch3;
	//  |Sleep Mode: 0 - device active; 1 - device in sleep;
	//  ||Reserved, reserved, set to 1
	//  |||Sensor Activation Mode: 0 - drive sensor with full current. 1 - drive sensor with current set by DRIVE_CURRENT_CHn 
	//  ||||Reserved, set to 1
	//  |||||Reference clock: 0 - use internal; 1 - use external clock
	//  ||||||Reserved, set to 0
	//  |||||||Disable interrupt. 0 - interrupt output on INTB pin; 1 - no interrupt output
	//  ||||||||High current sensor mode: 0 - 1.5mA max. 1 - > 1.5mA, not available if Autoscan is enabled
	//  |||||||||     Reserved, set to 000001
	//  |||||||||     |
	// CCS1A1R0IH000000 -> 0001 1110 1000 0001 -> 0x1E81
	FDC_Write16(FDC2214_CONFIG, 0x1E81);  //set config

	//If channel 1 selected, init it..
	if (chanMask & 0x01) {

		//settle count maximized, slow application
		FDC_Write16(FDC2214_SETTLECOUNT_CH0, 0x64);

		//rcount maximized for highest accuracy
		FDC_Write16(FDC2214_RCOUNT_CH0, 0xFFFF);

		//no offset
		FDC_Write16(FDC2214_OFFSET_CH0, 0x0000);
		
		// Set clock dividers
		//  Reserved
		//  | Sensor Frequency Select. b01 = /1 = sensor freq 0.01 to 8.75MHz; b10 = /2 = sensor freq 0.01 to 10 or 5 to 10 MHz
		//  | | Reserved
		//  | | |         Reference divider. Must be > 1. fref = fclk / this register`
		//  | | |         |
		// 00FF00RRRRRRRRRR -> 0010000000000001 -> 0x2001
		FDC_Write16(FDC2214_CLOCK_DIVIDERS_CH0, 0x2001);
		//set drive register
		FDC_Write16(FDC2214_DRIVE_CH0, 0xF800);
	}
	// Init chan2, if selected by channel init mask
	if (chanMask & 0x02) {
		FDC_Write16(FDC2214_SETTLECOUNT_CH1, 0x64);
		FDC_Write16(FDC2214_RCOUNT_CH1, 0xFFFF);
		FDC_Write16(FDC2214_OFFSET_CH1, 0x0000);
		FDC_Write16(FDC2214_CLOCK_DIVIDERS_CH1, 0x2001);
		FDC_Write16(FDC2214_DRIVE_CH1, 0xF800);	
	}	
	if (chanMask & 0x04) {
		FDC_Write16(FDC2214_SETTLECOUNT_CH1, 0x64);
		FDC_Write16(FDC2214_RCOUNT_CH1, 0xFFFF);
		FDC_Write16(FDC2214_OFFSET_CH1, 0x0000);
		FDC_Write16(FDC2214_CLOCK_DIVIDERS_CH1, 0x2001);
		FDC_Write16(FDC2214_DRIVE_CH1, 0xF800);	
	}	
	if (chanMask & 0x08) {
		FDC_Write16(FDC2214_SETTLECOUNT_CH1, 0x64);
		FDC_Write16(FDC2214_RCOUNT_CH1, 0xFFFF);
		FDC_Write16(FDC2214_OFFSET_CH1, 0x0000);
		FDC_Write16(FDC2214_CLOCK_DIVIDERS_CH1, 0x2001);
		FDC_Write16(FDC2214_DRIVE_CH1, 0xF800);	
	}	
	// Autoscan: 0 = single channel, selected by CONFIG.ACTIVE_CHAN
	// | Autoscan sequence. b00 for chan 1-2, b01 for chan 1-2-3, b02 for chan 1-2-3-4
	// | |         Reserved - must be b0001000001
	// | |         |  Deglitch frequency. b001 for 1 MHz, b100 for 3.3 MHz, b101 for 10 Mhz, b111 for 33 MHz
	// | |         |  |
    // ARR0001000001DDD -> b0000 0010 0000 1000 -> h0208
	uint16_t muxVal = 0x0208 | ((uint16_t)autoscanSeq << 13) | deglitchValue;
	//
    FDC_Write16(FDC2214_MUX_CONFIG, muxVal);  //set mux config for channels
}
/**
*  @brief      FDC init
*  @param      uint8_t chanMask, uint8_t autoscanSeq, uint8_t deglitchValue
*  @return     none
*  @note	   
*/
char FDC_Init(uint8_t chanMask, uint8_t autoscanSeq, uint8_t deglitchValue)
{
		//MyIIC_InitGPIO();		/* 配置GPIO */	
	//FDC_Read16(FDC2214_DEVICE_ID);
	//HAL_Delay(1);
	FDC_Read16(FDC2214_DEVICE_ID);
	while(1)
	{
		
	}
		
		int devId = FDC_Read16(FDC2214_DEVICE_ID);
		if (devId != 0x3054) {
    if (devId != 0x3055) {
            //two valid device ids for FDC2214 0x3054 and 0x3055
            return 0;
        }
    }
		
		FDC_LoadSettings(chanMask, autoscanSeq, deglitchValue);
		return 1;
}
#endif

#ifdef HARD_IIC
/**
  * @brief  Write an amount of data in blocking mode to a specific memory address
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface
  * @param  MemAddress Internal memory address
  * @param  MemAddSize Size of internal memory address
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
	
	uint16_t PROXIMITY_REFCOUNT=40000;
	uint16_t BUTTON_REFCOUNT=1000;
	uint16_t PROXIMITY_SETTLECOUNT=100;
	uint16_t BUTTON_SETTLECOUNT=100;

void FDC2214_init(void)
{
//    FDC2214_checkDevice();
	FDC2214_sleep();
//	  FDC2214_configINTB();
	FDC2214_clockSetup();
	HAL_Delay(1);
	FDC2214_allChannelsEnable();
	HAL_Delay(1);
	FDC2214_wake();
}

void FDC2214_checkDevice(void)
{
    uint8_t val[1] = {0};
    uint8_t readBackVal[2] = {0};
    uint16_t data = 0;
		HAL_I2C_Mem_Read(&hi2c1, FDC2214_SLAVE_ADDR_L_D, (uint16_t)DEV_ID_REG, 1, &val[0], 1, 1000);
		HAL_I2C_Mem_Read(&hi2c1, FDC2214_SLAVE_ADDR_L_D, (uint16_t)MAN_ID_REG, 1, &readBackVal[0], 1, 1000);
    data = ((uint16_t) (readBackVal[0] << 8) | readBackVal[1]);
}


void FDC2214_clockSetup(void)
{
	uint16_t PROXIMITY_REFCOUNTe;
	PROXIMITY_REFCOUNTe = SWAP16(PROXIMITY_REFCOUNT);
	uint16_t BUTTON_REFCOUNTe;
	BUTTON_REFCOUNTe = SWAP16(BUTTON_REFCOUNT);

	//uint16_t PROXIMITY_SETTLECOUNTe=100;
	//uint16_t BUTTON_SETTLECOUNTe=100;
		
		//REF COUNT
		HAL_I2C_Mem_Write(&hi2c1, FDC2214_SLAVE_ADDR_L_D, RCOUNT_CH0_REG, I2C_MEMADD_SIZE_8BIT, (uint8_t *)(&PROXIMITY_REFCOUNTe), 2, 1000);
		HAL_I2C_Mem_Write(&hi2c1, FDC2214_SLAVE_ADDR_L_D, RCOUNT_CH1_REG, I2C_MEMADD_SIZE_8BIT, (uint8_t *)(&BUTTON_REFCOUNTe)		, 2, 1000);
		HAL_I2C_Mem_Write(&hi2c1, FDC2214_SLAVE_ADDR_L_D, RCOUNT_CH2_REG, I2C_MEMADD_SIZE_8BIT, (uint8_t *)(&BUTTON_REFCOUNTe)		, 2, 1000);
	//	i2c_writeWord(FDC2214_SLAVE_ADDR_L, RCOUNT_CH0_REG, PROXIMITY_REFCOUNT);
	//	i2c_writeWord(FDC2214_SLAVE_ADDR_L, RCOUNT_CH1_REG, BUTTON_REFCOUNT);
	//	i2c_writeWord(FDC2214_SLAVE_ADDR_L, RCOUNT_CH2_REG, BUTTON_REFCOUNT);

	//Settle Count
	HAL_I2C_Mem_Write(&hi2c1, FDC2214_SLAVE_ADDR_L_D, SETTLECOUNT_CH0_REG, I2C_MEMADD_SIZE_8BIT, (uint8_t *)(&PROXIMITY_REFCOUNTe), 2, 1000);
	HAL_I2C_Mem_Write(&hi2c1, FDC2214_SLAVE_ADDR_L_D, SETTLECOUNT_CH1_REG, I2C_MEMADD_SIZE_8BIT, (uint8_t *)(&BUTTON_REFCOUNTe)		, 2, 1000);
	HAL_I2C_Mem_Write(&hi2c1, FDC2214_SLAVE_ADDR_L_D, SETTLECOUNT_CH2_REG, I2C_MEMADD_SIZE_8BIT, (uint8_t *)(&BUTTON_REFCOUNTe)		, 2, 1000);
	//	i2c_writeWord(FDC2214_SLAVE_ADDR_L, SETTLECOUNT_CH0_REG, PROXIMITY_SETTLECOUNT);
	//	i2c_writeWord(FDC2214_SLAVE_ADDR_L, SETTLECOUNT_CH1_REG, BUTTON_SETTLECOUNT);
	//	i2c_writeWord(FDC2214_SLAVE_ADDR_L, SETTLECOUNT_CH2_REG, BUTTON_SETTLECOUNT);
}

void FDC2214_configINTB(void)
{
	//GPIO_setAsInputPin(GPIO_PORT_P3, GPIO_PIN1);
}

void FDC2214_enableINTB(void)
{

	//	uint8_t readBackVal[2] = {0};
	//	uint16_t data = 0;

	//	//Enable GPIO interrupt pin
	//	GPIO_enableInterrupt(GPIO_PORT_P3, GPIO_PIN1);
	//	GPIO_selectInterruptEdge(GPIO_PORT_P3, GPIO_PIN1, GPIO_HIGH_TO_LOW_TRANSITION);

	//	//Select INTB pin enable on FDC2214
	//	i2c_readWord(FDC2214_SLAVE_ADDR_L, CONFIG_REG, &readBackVal[0]);
	//	data = (readBackVal[0] << 8) | readBackVal[1];
	//	data = data & ~(INTB_DIS);
	//	i2c_writeWord(FDC2214_SLAVE_ADDR_L, CONFIG_REG, data);

	//	//Configure ERROR_CONFIG for DRDY_2INT
	//	i2c_readWord(FDC2214_SLAVE_ADDR_L, ERROR_CONFIG_REG, &readBackVal[0]);
	//	data = (readBackVal[0] << 8) | readBackVal[1];
	//	data = data | DRDY_2INT;
	//	i2c_writeWord(FDC2214_SLAVE_ADDR_L, ERROR_CONFIG_REG, data);
}

void FDC2214_disableINTB(void)
{
//	GPIO_disableInterrupt(GPIO_PORT_P3, GPIO_PIN1);
}

void FDC2214_proxSensorEnable(void)
{
	//Primary proximity sensor on CH0
	//Need to wake up device after this function call

	uint16_t configData = 0;
	uint16_t configDatae;
	uint16_t muxConfigData = 0;
	uint16_t muxConfigDatae;
	uint16_t OP = IDRIVE_0P052;
	uint8_t OPA[2] = {0};
	OPA[1] =(uint8_t) OP;
	OPA[0] = (uint8_t)(OP>>8);

	//Select single channel measurement and configure
	configData = (ACTIVE_CHAN_0 | SENSOR_ACTIVATE_SEL | REF_CLK_SRC | SLEEP_MODE_EN
					& ~(INTB_DIS | HIGH_CURRENT_DRV));
	configData = (configData | (1<<12) | (1<<10) | (1<<0));		//Set reserve bits to 1 per datasheet
	configDatae = SWAP16(configData);
	HAL_I2C_Mem_Write(&hi2c1, FDC2214_SLAVE_ADDR_L_D, CONFIG_REG, I2C_MEMADD_SIZE_8BIT,(uint8_t *)(&configDatae), 2, 1000);
	//i2c_writeWord(FDC2214_SLAVE_ADDR_L, CONFIG_REG, configData);

	//Select measurement sequence
	muxConfigData = (DEGLITCH_10MHZ & ~(AUTOSCAN_EN | RR_SEQUENCE0));
	muxConfigData = (muxConfigData | (1<<9) | (1<<3));	//set reserve bits to 1 per datasheet
	muxConfigDatae = SWAP16(muxConfigData);
	HAL_I2C_Mem_Write(&hi2c1, FDC2214_SLAVE_ADDR_L_D, MUX_CONFIG_REG, I2C_MEMADD_SIZE_8BIT, (uint8_t *)(&muxConfigDatae), 2, 1000);
	//i2c_writeWord(FDC2214_SLAVE_ADDR_L, MUX_CONFIG_REG, muxConfigData);

	//Adjust IDRIVE for better sensitivity
	HAL_I2C_Mem_Write(&hi2c1, FDC2214_SLAVE_ADDR_L_D, DRIVE_CURRENT_CH0_REG, I2C_MEMADD_SIZE_8BIT, OPA, 2, 1000);
	//i2c_writeWord(FDC2214_SLAVE_ADDR_L, DRIVE_CURRENT_CH0_REG, IDRIVE_0P052);

}

void FDC2214_allChannelsEnable(void)
{
	//Prox = CH0, B1 = CH1, B2 = CH2
	//Need to wake up device after this function call

	uint16_t configData = 0;
	uint16_t configDatae;
	uint16_t muxConfigData = 0;
	uint16_t muxConfigDatae;
	
	uint16_t OP = IDRIVE_0P069;
	uint8_t OPA[2] = {0};
	OPA[1] =(uint8_t) OP;
	OPA[0] = (uint8_t)(OP>>8);
	uint16_t OP1 = IDRIVE_0P081;
	uint8_t OPA1[2] = {0};
	OPA1[1] =(uint8_t) OP1;
	OPA1[0] = (uint8_t)(OP1>>8);

	//Select single channel measurement and configure
	configData = (SLEEP_MODE_EN | SENSOR_ACTIVATE_SEL | REF_CLK_SRC
					& ~(INTB_DIS | HIGH_CURRENT_DRV));
	configData = (configData | (1<<12) | (1<<10));		//Set reserve bits to 1 per datasheet

	
	//i2c_writeWord(FDC2214_SLAVE_ADDR_L, CONFIG_REG, configData);
	configDatae = SWAP16(configData);
	HAL_I2C_Mem_Write(&hi2c1, FDC2214_SLAVE_ADDR_L_D, CONFIG_REG, I2C_MEMADD_SIZE_8BIT, (uint8_t *)(&configDatae), 2, 1000);
	//Select measurement sequence
	muxConfigData = (AUTOSCAN_EN | RR_SEQUENCE1 | DEGLITCH_10MHZ);
	muxConfigData = (muxConfigData | (1<<9) | (1<<3));	//set reserve bits to 1 per datasheet

	//i2c_writeWord(FDC2214_SLAVE_ADDR_L, MUX_CONFIG_REG, muxConfigData);
	muxConfigDatae = SWAP16(muxConfigData);
	HAL_I2C_Mem_Write(&hi2c1, FDC2214_SLAVE_ADDR_L_D, MUX_CONFIG_REG, I2C_MEMADD_SIZE_8BIT, (uint8_t *)(&muxConfigDatae), 2, 1000);
	//Adjust drive current for better sensitivity
	HAL_I2C_Mem_Write(&hi2c1, FDC2214_SLAVE_ADDR_L_D, DRIVE_CURRENT_CH0_REG, I2C_MEMADD_SIZE_8BIT, OPA, 2, 1000);
	HAL_I2C_Mem_Write(&hi2c1, FDC2214_SLAVE_ADDR_L_D, DRIVE_CURRENT_CH1_REG, I2C_MEMADD_SIZE_8BIT, OPA1, 2, 1000);
	HAL_I2C_Mem_Write(&hi2c1, FDC2214_SLAVE_ADDR_L_D, DRIVE_CURRENT_CH2_REG, I2C_MEMADD_SIZE_8BIT, OPA1, 2, 1000);
	//	i2c_writeWord(FDC2214_SLAVE_ADDR_L, DRIVE_CURRENT_CH0_REG, IDRIVE_0P069);
	//	i2c_writeWord(FDC2214_SLAVE_ADDR_L, DRIVE_CURRENT_CH1_REG, IDRIVE_0P081);
	//	i2c_writeWord(FDC2214_SLAVE_ADDR_L, DRIVE_CURRENT_CH2_REG, IDRIVE_0P081);
}

uint32_t FDC2214_readMeasProxSensor(void)
{
	uint8_t readBackVal[2] = {0};
	uint16_t dataMSB = 0;
	uint16_t dataLSB = 0;

	//CH0 measurement
	HAL_I2C_Mem_Read(&hi2c1, FDC2214_SLAVE_ADDR_L_D, (uint16_t)DATA_MSB_CH0_REG, 1, &readBackVal[0], 2, 1000);
	//i2c_readWord(FDC2214_SLAVE_ADDR_L, DATA_MSB_CH0_REG, &readBackVal[0]);	//MSB
	dataMSB = (((uint16_t) (readBackVal[0] << 8)) | readBackVal[1]) & ~(0xF000);			//Mask the upper 4 bits
	
	HAL_I2C_Mem_Read(&hi2c1, FDC2214_SLAVE_ADDR_L_D, (uint16_t)DATA_LSB_CH0_REG, 1, &readBackVal[0], 2, 1000);
	//i2c_readWord(FDC2214_SLAVE_ADDR_L, DATA_LSB_CH0_REG, &readBackVal[0]);	//LSB
	dataLSB = (((uint16_t) readBackVal[0] << 8)) | readBackVal[1];			//Mask the upper 4 bits

	return ( (((uint32_t) dataMSB) << 16) | dataLSB);
}

uint32_t FDC2214_readMeasButton1(void)
{
	uint8_t readBackVal[2] = {0};
	uint16_t dataMSB = 0;
	uint16_t dataLSB = 0;

	//CH0 measurement (Button 1)
	HAL_I2C_Mem_Read(&hi2c1, FDC2214_SLAVE_ADDR_L_D, (uint16_t)DATA_MSB_CH1_REG, 1, &readBackVal[0], 2, 1000);
	//i2c_readWord(FDC2214_SLAVE_ADDR_L, DATA_MSB_CH1_REG, &readBackVal[0]);	//MSB
	dataMSB = (((uint16_t) (readBackVal[0] << 8)) | readBackVal[1]) & ~(0xF000);			//Mask the upper 4 bits
	HAL_I2C_Mem_Read(&hi2c1, FDC2214_SLAVE_ADDR_L_D, (uint16_t)DATA_LSB_CH1_REG, 1, &readBackVal[0], 2, 1000);
	//i2c_readWord(FDC2214_SLAVE_ADDR_L, DATA_LSB_CH1_REG, &readBackVal[0]);	//LSB
	dataLSB = (((uint16_t) readBackVal[0] << 8)) | readBackVal[1];						//Mask the upper 4 bits

	return ((((uint32_t) dataMSB) << 16) | dataLSB);
}

/**
  * @brief  Read an amount of data in blocking mode from a specific memory address
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface
  * @param  MemAddress Internal memory address
  * @param  MemAddSize Size of internal memory address
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @param  Timeout Timeout duration
  * @retval HAL status
  */

uint32_t FDC2214_readMeasButton2(void)
{
	uint8_t readBackVal[2] = {0};
	uint16_t dataMSB = 0;
	uint16_t dataLSB = 0;

	//CH1 measurement (Button 2)
	HAL_I2C_Mem_Read(&hi2c1, FDC2214_SLAVE_ADDR_L_D, (uint16_t)DATA_MSB_CH2_REG, 1, &readBackVal[0], 2, 1000);
	//i2c_readWord(FDC2214_SLAVE_ADDR_L, DATA_MSB_CH2_REG, &readBackVal[0]);	//MSB
	dataMSB = (((uint16_t) (readBackVal[0] << 8)) | readBackVal[1]) & ~(0xF000);			//Mask the upper 4 bits
	HAL_I2C_Mem_Read(&hi2c1, FDC2214_SLAVE_ADDR_L_D, (uint16_t)DATA_LSB_CH2_REG, 1, &readBackVal[0], 2, 1000);
	//i2c_readWord(FDC2214_SLAVE_ADDR_L, DATA_LSB_CH2_REG, &readBackVal[0]);	//LSB
	dataLSB = (((uint16_t) readBackVal[0] << 8)) | readBackVal[1];						//Mask the upper 4 bits

	return ((((uint32_t) dataMSB) << 16) | dataLSB);
}

void FDC2214_clearDRDY(void)
{
	//Clearing the DRDY bit when INTB interrupt occurs by reading STATUS reg
	uint8_t readBackVal[2] = {0};
	HAL_I2C_Mem_Read(&hi2c1, FDC2214_SLAVE_ADDR_L_D, (uint16_t)STATUS_REG, 1, &readBackVal[0], 2, 1000);
	//i2c_readWord(FDC2214_SLAVE_ADDR_L, STATUS_REG, &readBackVal[0]);
}

void FDC2214_sleep(void)
{
	uint8_t readBackVal[2] = {0};
	uint16_t data = 0;
	
	uint16_t datae;
	//Only change SLEEP MODE BIT
	HAL_I2C_Mem_Read(&hi2c1, FDC2214_SLAVE_ADDR_L_D, (uint16_t)CONFIG_REG, 1, &readBackVal[0], 2, 1000);
	//i2c_readWord(FDC2214_SLAVE_ADDR_L, CONFIG_REG, &readBackVal[0]);
	data = (readBackVal[0] << 8) | readBackVal[1];

	data = (data | SLEEP_MODE_EN);		//ENABLE SLEEP MODE
  datae = SWAP16(data);
	HAL_I2C_Mem_Write(&hi2c1, FDC2214_SLAVE_ADDR_L_D, CONFIG_REG, I2C_MEMADD_SIZE_8BIT, (uint8_t *)(&datae), 2, 1000);
	//i2c_writeWord(FDC2214_SLAVE_ADDR_L, CONFIG_REG, data);
}

void FDC2214_wake(void)
{
	uint8_t readBackVal[2] = {0};
	uint16_t data = 0;

	uint16_t datae;
	//Only change SLEEP MODE BIT
	HAL_I2C_Mem_Read(&hi2c1, FDC2214_SLAVE_ADDR_L_D, (uint16_t)CONFIG_REG, 1,readBackVal, 2, 1000);
	//i2c_readWord(FDC2214_SLAVE_ADDR_L, CONFIG_REG, &readBackVal[0]);
	data = (readBackVal[0] << 8) | readBackVal[1];

	data = (data & (~SLEEP_MODE_EN));	//DISABLE SLEEP MODE
	datae = SWAP16(data);
	HAL_I2C_Mem_Write(&hi2c1, FDC2214_SLAVE_ADDR_L_D, CONFIG_REG, I2C_MEMADD_SIZE_8BIT, (uint8_t *)(&datae), 2, 1000);   
	//i2c_writeWord(FDC2214_SLAVE_ADDR_L, CONFIG_REG, data);
}

#endif
