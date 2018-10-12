#include "print.h"
void hal_uart_putchar(char i)  
{  
    ES = 0;  
    TI = 0; //清空发送完中断请求标志位  
    SBUF = i;  //将数据放入寄存器发送  
    while(TI == 0);//等待发送完毕，发送完毕 TI == 1  
    TI = 0; //清空发送完中断请求标志位  
    ES = 1;  
} 
char putchar(char c)  
{  
    hal_uart_putchar(c);  
    return c;  
}