#ifndef __REPORT_H	
#define __REPORT_H	
#include "delay.h"
#include "sys.h"
void usart1_send_char(u8 c);
void usart1_niming_report(u8 fun,u8*data,u8 len);
void I_send_data(short aacyc,short Angle_balance);
#endif


