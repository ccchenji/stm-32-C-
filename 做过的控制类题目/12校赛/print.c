#include "print.h"
void hal_uart_putchar(char i)  
{  
    ES = 0;  
    TI = 0; //��շ������ж������־λ  
    SBUF = i;  //�����ݷ���Ĵ�������  
    while(TI == 0);//�ȴ�������ϣ�������� TI == 1  
    TI = 0; //��շ������ж������־λ  
    ES = 1;  
} 
char putchar(char c)  
{  
    hal_uart_putchar(c);  
    return c;  
}