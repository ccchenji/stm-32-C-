#ifndef __FDC2214_H__
#define __FDC2214_H__

#include "main.h"
#include "MyIIC.h"
#include "stm32f1xx_hal.h"

#define NEW_LIB_SOFT
//#define SOFT_IIC

#define SWAP16(data)    (uint32_t)((((uint16_t)(data) & (0xFF<<0 ))<<8)      \
                          | (((uint32_t)(data) & (0xFF<<8))>>8)            \
                        )

#ifdef NEW_LIB_SOFT
//IIC??
#define FDC2214_Addr                 (0x2A)
//???
#define FDC2214_DATA_CH0             (0x00)
#define FDC2214_DATA_LSB_CH0         (0x01)
#define FDC2214_DATA_CH1             (0x02)
#define FDC2214_DATA_LSB_CH1         (0x03)
#define FDC2214_DATA_CH2             (0x04)
#define FDC2214_DATA_LSB_CH2         (0x05)
#define FDC2214_DATA_CH3             (0x06)
#define FDC2214_DATA_LSB_CH3         (0x07)
#define FDC2214_RCOUNT_CH0           (0x08)
#define FDC2214_RCOUNT_CH1           (0x09)
#define FDC2214_RCOUNT_CH2           (0x0A)
#define FDC2214_RCOUNT_CH3           (0x0B)
#define FDC2214_SETTLECOUNT_CH0      (0x10)
#define FDC2214_SETTLECOUNT_CH1      (0x11)
#define FDC2214_SETTLECOUNT_CH2      (0x12)
#define FDC2214_SETTLECOUNT_CH3      (0x13)
#define FDC2214_CLOCK_DIVIDERS_CH0   (0x14)
#define FDC2214_CLOCK_DIVIDERS_CH1   (0x15)
#define FDC2214_CLOCK_DIVIDERS_CH2   (0x16)
#define FDC2214_CLOCK_DIVIDERS_CH3   (0x17)
#define FDC2214_STATUS               (0x18)
#define FDC2214_ERROR_CONFIG         (0x19)
#define FDC2214_CONFIG               (0x1A)
#define FDC2214_MUX_CONFIG           (0x1B)
#define FDC2214_RESET_DEV            (0x1C)
#define FDC2214_DRIVE_CURRENT_CH0    (0x1E)
#define FDC2214_DRIVE_CURRENT_CH1    (0x1F)
#define FDC2214_DRIVE_CURRENT_CH2    (0x20)
#define FDC2214_DRIVE_CURRENT_CH3    (0x21)
#define FDC2214_MANUFACTURER_ID      (0x7E)
#define FDC2214_DEVICE_ID            (0x7F)
//??ID
#define FDC2214_ID                   (0x3055)

//???
typedef enum
{
    FDC2214_Channel_0 = 0x00, //??0
    FDC2214_Channel_1 = 0x01, //??1
    FDC2214_Channel_2 = 0x02, //??2
    FDC2214_Channel_3 = 0x03  //??3
}FDC2214_channel_t;

//??????????
typedef enum
{
    FDC2214_Channel_Sequence_0_1      = 0x00, //??0?1
    FDC2214_Channel_Sequence_0_1_2    = 0x01, //??0?1?2
    FDC2214_Channel_Sequence_0_1_2_3  = 0x02, //??0?1?2?3
}FDC2214_channel_sequence_t;

//???????
typedef enum
{
    FDC2214_Bandwidth_1M   = 0x01, //1MHz??
    FDC2214_Bandwidth_3_3M = 0x04, //3.3MHz??
    FDC2214_Bandwidth_10M  = 0x05, //10MHz??
    FDC2214_Bandwidth_33M  = 0x07  //33MHz??
}FDC2214_filter_bandwidth_t;

//?????????
typedef enum
{
    FDC2214_Drive_Current_0_016 = 0x00, //0.016mA
    FDC2214_Drive_Current_0_018 = 0x01, //0.018mA
    FDC2214_Drive_Current_0_021 = 0x02, //0.021mA
    FDC2214_Drive_Current_0_025 = 0x03, //0.025mA
    FDC2214_Drive_Current_0_028 = 0x04, //0.028mA
    FDC2214_Drive_Current_0_033 = 0x05, //0.033mA
    FDC2214_Drive_Current_0_038 = 0x06, //0.038mA
    FDC2214_Drive_Current_0_044 = 0x07, //0.044mA
    FDC2214_Drive_Current_0_052 = 0x08, //0.052mA
    FDC2214_Drive_Current_0_060 = 0x09, //0.060mA
    FDC2214_Drive_Current_0_069 = 0x0A, //0.069mA
    FDC2214_Drive_Current_0_081 = 0x0B, //0.081mA
    FDC2214_Drive_Current_0_093 = 0x0C, //0.093mA
    FDC2214_Drive_Current_0_108 = 0x0D, //0.108mA
    FDC2214_Drive_Current_0_126 = 0x0E, //0.126mA
    FDC2214_Drive_Current_0_146 = 0x0F, //0.146mA
    FDC2214_Drive_Current_0_169 = 0x10, //0.169mA
    FDC2214_Drive_Current_0_196 = 0x11, //0.196mA
    FDC2214_Drive_Current_0_228 = 0x12, //0.228mA
    FDC2214_Drive_Current_0_264 = 0x13, //0.264mA
    FDC2214_Drive_Current_0_307 = 0x14, //0.307mA
    FDC2214_Drive_Current_0_356 = 0x15, //0.356mA
    FDC2214_Drive_Current_0_413 = 0x16, //0.413mA
    FDC2214_Drive_Current_0_479 = 0x17, //0.479mA
    FDC2214_Drive_Current_0_555 = 0x18, //0.555mA
    FDC2214_Drive_Current_0_644 = 0x19, //0.644mA
    FDC2214_Drive_Current_0_747 = 0x1A, //0.747mA
    FDC2214_Drive_Current_0_867 = 0x1B, //0.867mA
    FDC2214_Drive_Current_1_006 = 0x1C, //1.006mA
    FDC2214_Drive_Current_1_167 = 0x1D, //1.167mA
    FDC2214_Drive_Current_1_354 = 0x1E, //1.354mA
    FDC2214_Drive_Current_1_571 = 0x1F  //1.571mA
}FDC2214_drive_current_t;

void FDC2214_Write16(uint8_t Slve_Addr, uint8_t reg, uint16_t data);
uint16_t FDC2214_Read16(uint8_t Slve_Addr, uint8_t reg);
uint8_t FDC2214_GetChannelData(FDC2214_channel_t channel, uint32_t *data);
void FDC2214_SetRcount(FDC2214_channel_t channel, uint16_t rcount);
void FDC2214_SetSettleCount(FDC2214_channel_t channel, uint16_t count);
void FDC2214_SetChannelClock(FDC2214_channel_t channel, uint8_t frequency_select, uint16_t divider);
void FDC2214_SetINTB(uint8_t mode);
void FDC2214_SetActiveChannel(FDC2214_channel_t channel);
void FDC2214_SetSleepMode(uint8_t mode);
void FDC2214_SetCurrentMode(uint8_t mode);
void FDC2214_SetClockSource(uint8_t src);
void FDC2214_SetHighCurrentMode(uint8_t mode);
void FDC2214_SetMUX_CONFIG(uint8_t autoscan, FDC2214_channel_sequence_t channels, FDC2214_filter_bandwidth_t bandwidth);
void FDC2214_Reset(void);
void FDC2214_SetDriveCurrent(FDC2214_channel_t channel, FDC2214_drive_current_t current);
double FDC2214_CalculateFrequency(FDC2214_channel_t channel, uint32_t datax);
double FDC2214_CalculateCapacitance(double frequency, float inductance, float capacitance);
uint8_t FDC2214_Init(void);


#endif



#ifdef SOFT_IIC
// chances are its 32 bit so assume that
typedef volatile uint32_t PortReg;
typedef uint32_t PortMask;


#define FDC2214_I2C_ADDR_0   0x2A
#define FDC2214_I2C_ADDR_1   0x2B
// Address is 0x2A (default) or 0x2B (if ADDR is high)

//bitmasks
#define FDC2214_CH0_UNREADCONV 0x0008         //denotes unread CH0 reading in STATUS register
#define FDC2214_CH1_UNREADCONV 0x0004         //denotes unread CH1 reading in STATUS register
#define FDC2214_CH2_UNREADCONV 0x0002         //denotes unread CH2 reading in STATUS register
#define FDC2214_CH3_UNREADCONV 0x0001         //denotes unread CH3 reading in STATUS register


//registers
#define FDC2214_DEVICE_ID           		0x7F
#define FDC2214_MUX_CONFIG          		0x1B
#define FDC2214_CONFIG              		0x1A
#define FDC2214_RCOUNT_CH0          		0x08
#define FDC2214_RCOUNT_CH1          		0x09
#define FDC2214_RCOUNT_CH2          		0x0A
#define FDC2214_RCOUNT_CH3          		0x0B
#define FDC2214_OFFSET_CH0		          	0x0C
#define FDC2214_OFFSET_CH1          		0x0D
#define FDC2214_OFFSET_CH2    			    0x0E
#define FDC2214_OFFSET_CH3         			0x0F
#define FDC2214_SETTLECOUNT_CH0     		0x10
#define FDC2214_SETTLECOUNT_CH1     		0x11
#define FDC2214_SETTLECOUNT_CH2     		0x12
#define FDC2214_SETTLECOUNT_CH3     		0x13
#define FDC2214_CLOCK_DIVIDERS_CH0  		0x14
#define FDC2214_CLOCK_DIVIDERS_CH1  		0x15
#define FDC2214_CLOCK_DIVIDERS_CH2  		0x16
#define FDC2214_CLOCK_DIVIDERS_CH3  		0x17
#define FDC2214_STATUS              		0x18
#define FDC2214_DATA_CH0_MSB	            0x00
#define FDC2214_DATA_CH0_LSB    		    0x01
#define FDC2214_DATA_CH1_MSB	            0x02
#define FDC2214_DATA_CH1_LSB    		    0x03
#define FDC2214_DATA_CH2_MSB	            0x04
#define FDC2214_DATA_CH2_LSB    		    0x05
#define FDC2214_DATA_CH3_MSB	            0x06
#define FDC2214_DATA_CH3_LSB    		    0x07
#define FDC2214_DRIVE_CH0           		0x1E
#define FDC2214_DRIVE_CH1           		0x1F
#define FDC2214_DRIVE_CH2           		0x20
#define FDC2214_DRIVE_CH3           		0x21

// mask for 28bit data to filter out flag bits
#define FDC2214_DATA_CHx_MASK_DATA         	0x0FFF  
#define FDC2214_DATA_CHx_MASK_ERRAW        	0x1000  
#define FDC2214_DATA_CHx_MASK_ERRWD        	0x2000  


// FDC2214 configuration params have two bytes, msb and lsb here refer to bytes, not bits : )
typedef struct 
{
    char c_addr;
    char c_param_msb;
    char c_param_lsb;
} cfg_param_t;

uint8_t FDC_Read8(uint16_t address);
uint32_t FDC_Read32(uint8_t address);
uint16_t FDC_Read16(uint8_t address);
void FDC_Write8(uint16_t address, uint8_t data);
void FDC_Write16(uint16_t address, uint16_t data);
unsigned long FDC_GetReading28(uint8_t channel);
unsigned long FDC_GetReading16(uint8_t channel);
void FDC_LoadSettings(uint8_t chanMask, uint8_t autoscanSeq, uint8_t deglitchValue);
char FDC_Init(uint8_t chanMask, uint8_t autoscanSeq, uint8_t deglitchValue);
#endif


#ifdef HARD_IIC

#define FDC2214_SLAVE_ADDR_L			0x2A
#define FDC2214_SLAVE_ADDR_H			0x2B

#define FDC2214_SLAVE_ADDR_L_D		0x54

/***********REGISTERS*********/
/*****************************/
#define	DATA_MSB_CH0_REG				0x00
#define DATA_LSB_CH0_REG				0x01
#define DATA_MSB_CH1_REG				0x02
#define DATA_LSB_CH1_REG				0x03
#define DATA_MSB_CH2_REG				0x04
#define DATA_LSB_CH2_REG				0x05
#define DATA_MSB_CH3_REG				0x06
#define DATA_LSB_CH3_REG				0x07
#define RCOUNT_CH0_REG					0x08
#define RCOUNT_CH1_REG					0x09
#define RCOUNT_CH2_REG					0x0A
#define RCOUNT_CH3_REG					0x0B
#define OFFSET_CH0_REG					0x0C
#define OFFSET_CH1_REG					0x0D
#define OFFSET_CH2_REG					0x0E
#define OFFSET_CH3_REG					0x0F
#define SETTLECOUNT_CH0_REG				0x10
#define SETTLECOUNT_CH1_REG				0x11
#define SETTLECOUNT_CH2_REG				0x12
#define SETTLECOUNT_CH3_REG				0x13
#define CLOCK_DIVIDERS_CH0_REG			0x14
#define CLOCK_DIVIDERS_CH1_REG			0x15
#define CLOCK_DIVIDERS_CH2_REG			0x16
#define CLOCK_DIVIDERS_CH3_REG			0x17
#define STATUS_REG						0x18
#define ERROR_CONFIG_REG				0x19
#define CONFIG_REG						0x1A
#define MUX_CONFIG_REG					0x1B
#define RESET_DEV_REG					0x1C
#define DRIVE_CURRENT_CH0_REG			0x1E
#define DRIVE_CURRENT_CH1_REG			0x1F
#define DRIVE_CURRENT_CH2_REG			0x20
#define DRIVE_CURRENT_CH3_REG			0x21
#define MAN_ID_REG						0x7E
#define DEV_ID_REG						0x7F

/**************DATA REGISTERs**************/
/******************************************/
#define CH0_ERR_WD						0x2000
#define CH0_ERR_AW						0x1000
#define DATA_MSB_CH0					0x0FFF
#define DATA_LSB_CH0					0xFFFF

#define CH1_ERR_WD						0x2000
#define CH1_ERR_AW						0x1000
#define DATA_MSB_CH1					0x0FFF
#define DATA_LSB_CH1					0xFFFF

#define CH2_ERR_WD						0x2000
#define CH2_ERR_AW						0x1000
#define DATA_MSB_CH2					0x0FFF
#define DATA_LSB_CH2					0xFFFF

#define CH3_ERR_WD						0x2000
#define CH3_ERR_AW						0x1000
#define DATA_MSB_CH3					0x0FFF
#define DATA_LSB_CH3					0xFFFF


/**************RCOUNT_CHx**********************/
/**********************************************/
#define CH0_RCOUNT						0xFFFF
#define CH1_RCOUNT						0xFFFF
#define CH2_RCOUNT						0xFFFF
#define CH3_RCOUNT						0xFFFF

/**************OFFSET_CHx**********************/
/**********************************************/
#define CH0_OFFSET						0xFFFF
#define CH1_OFFSET						0xFFFF
#define CH2_OFFSET						0xFFFF
#define CH3_OFFSET						0xFFFF


/***************STATUS REGISTER****************/
/**********************************************/
#define ERR_CHAN_0						0x0000
#define ERR_CHAN_1						0x1000
#define ERR_CHAN_2						0x2000
#define ERR_CHAN_3						0x3000
#define ERR_WD							0x0800
#define ERR_AHW							0x0400
#define ERR_ALW							0x0200
#define DRDY							0x0040
#define CH0_UNREADCONV					0x0008
#define CH1_UNREADCONV					0x0004
#define CH2_UNREADCONV					0x0002
#define CH3_UNREADCONV					0x0001

/***************ERROR CONFIG REGISTER**********/
/**********************************************/
#define WD_ERR2OUT						0x2000
#define AH_WARN2OUT						0x1000
#define AL_WARN2OUT						0x0800
#define WD_ERR2INT						0x0020
#define DRDY_2INT						0x0001


/***************CONFIG REGISTER****************/
/**********************************************/
#define ACTIVE_CHAN_0					0x0000
#define ACTIVE_CHAN_1					0x4000
#define ACTIVE_CHAN_2					0x8000
#define ACTIVE_CHAN_3					0xC000
#define SLEEP_MODE_EN					0x2000
#define SENSOR_ACTIVATE_SEL				0x0800
#define REF_CLK_SRC						0x0200
#define INTB_DIS						0x0080
#define HIGH_CURRENT_DRV				0x0040

/***************MUX CONFIG REGISTER************/
/**********************************************/
#define AUTOSCAN_EN						0x8000
#define RR_SEQUENCE0					0x0000
#define RR_SEQUENCE1					0x2000
#define RR_SEQUENCE2					0x4000
#define RR_SEQUENCE3					0x5000	// should be 0x6000 ?
#define DEGLITCH_1MHZ					0x0001
#define DEGLITCH_3P3MHZ					0x0004
#define DEGLITCH_10MHZ					0x0005
#define DEGLITCH_33MHZ					0x0007

/***************RESET DEV REGISTER*************/
/**********************************************/
#define RESET_DEV						0x8000
#define OUTPUT_GAIN_1					0x0000
#define OUTPUT_GAIN_4					0x0200
#define OUTPUT_GAIN_8					0x0400
#define OUTPUT_GAIN_16					0x0500

/***********CURRENT DRIVE SETTINGS************/
/*********************************************/
#define IDRIVE_0P016					0x0000
#define IDRIVE_0P018					0x0800
#define IDRIVE_0P021					0x1000
#define IDRIVE_0P025					0x1800
#define IDRIVE_0P028					0x2000
#define IDRIVE_0P033					0x2800
#define IDRIVE_0P038					0x3000
#define IDRIVE_0P044					0x3800
#define IDRIVE_0P052					0x4000
#define IDRIVE_0P060					0x4800
#define IDRIVE_0P069					0x5000
#define IDRIVE_0P081					0x5800
#define IDRIVE_0P093					0x6000
#define IDRIVE_0P108					0x6800
#define IDRIVE_0P126					0x7000
#define IDRIVE_0P146					0x7800
#define IDRIVE_0P169					0x8000
#define IDRIVE_0P196					0x8800
#define IDRIVE_0P228					0x9000
#define IDRIVE_0P264					0x9800
#define IDRIVE_0P307					0xA000
#define IDRIVE_0P356					0xA800
#define IDRIVE_0P413					0xB000
#define IDRIVE_0P479					0xB800
#define IDRIVE_0P555					0xC000
#define IDRIVE_0P644					0xC800
#define IDRIVE_0P747					0xD000
#define IDRIVE_0P867					0xD800
#define IDRIVE_1P006					0xE000
#define IDRIVE_1P167					0xE800
#define IDRIVE_1P354					0xF000
#define IDRIVE_1P571					0xF800


void FDC2214_init(void);
void FDC2214_checkDevice(void);
void FDC2214_clockSetup(void);
void FDC2214_configINTB(void);
void FDC2214_enableINTB(void);
void FDC2214_disableINTB(void);
void FDC2214_proxSensorEnable(void);
void FDC2214_allChannelsEnable(void);
uint32_t FDC2214_readMeasProxSensor(void);
uint32_t FDC2214_readMeasButton1(void);
uint32_t FDC2214_readMeasButton2(void);
void FDC2214_clearDRDY(void);
void FDC2214_sleep(void);
void FDC2214_wake(void);

#endif

#endif
