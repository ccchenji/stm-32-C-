#include "AD.h"
/**************************ADC��ʼ������********************************/
void InitADC()
{
   ADC_CONTR=0XC8;//û180��ʱ������ת��һ�Σ�ѡP1^0����ΪAD��������
	 P1ASF=0X01;//P1^0����Ϊģ��ADC����ʹ�ã��ɼ�������ŵ����ݣ�
//	 EA=1;//�����ж�
//	 IE=0XB0;//��ADC�ж�
	 ADC_RES=0;//���ԭ��������
	 ADC_RESL=0;  
	 _nop_;
	 _nop_;
	 _nop_;
	 _nop_;
	 _nop_;  
}
/**************************�õ�ADC��ֵ**********************************/
int AD_get()
{
    static  unsigned int i=0;
	  static	double k=0;
    while(!(ADC_CONTR&0x10));   		//�ȴ�ת�����
	  i=ADC_RES;							//ȡ�߰�λ
	  i=i<<2;								
	  i=i|ADC_RESL;						//ȡ�Ͷ�λ
	  ADC_CONTR=0XC8;//��ʼ��
  	return i;
}