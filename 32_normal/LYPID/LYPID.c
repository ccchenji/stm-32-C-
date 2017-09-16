#include "LYPID.H"
#include "math.h"
u8 Disp[]={'0','1','2','3','4','5','6','7','8','9'};
u8 Disp_Digit[]={0,1,2,3,4,5,6,7,8,9};
u8 Disp_Save[15];
u8 len=0;
u8 a=0;
u8 b=0;
u8 c=0;
u8 d=0;
float K_Return=0;
/*****************字符转浮点数*********************/
float K_Change()
{
	if(USART_RX_STA&0x8000)
	{
		len=USART_RX_STA&0x0fff;
		K_Return=0;
		c=0;
		b=0;
		for(a=0;a<len;a++)
		{
			 if(USART_RX_BUF[a]=='.')
			 {
				  b=a+1;
			 }
			 else
			 {
				 Disp_Save[c]=USART_RX_BUF[a];
				 c++;
			 }
		}
			 for(a=0;a<c;a++)
			 {
				 for(d=0;d<10;d++)
				 {
					 if(Disp_Save[a]==Disp[d])
					 {
						  K_Return=K_Return+Disp_Digit[d]*pow(10,c-a-1);
						  break;
					 }
				 }
			 }
			 if(b>0)
			 {
			  K_Return=K_Return/pow(10,len-b);
			 }
		    printf("%f",K_Return);
		    USART_RX_STA=0;
		}
		return K_Return;
	}
/***************************浮点数转化成字符****************************/
//	 K_Change();
//   sprintf(buffer,"%f",K_Return);
//u8 buffer[22];

	