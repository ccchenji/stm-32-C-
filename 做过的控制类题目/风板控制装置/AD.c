#include "AD.h"
/**************************ADC��ʼ������********************************/
void InitADC()
{
     ADC_CONTR=0X88;//ÿ180��ʱ������ת��һ�Σ�ѡP1^0����ΪAD��������
	 P1ASF=0X01;//P1^0����Ϊģ��ADC����ʹ��
//	 EA=1;//�����ж�
	// IE=0XB2;//��ADC�ж�
	 ADC_RES=0;//���ԭ��������
	 ADC_RESL=0;  
	 _nop_;_nop_;_nop_;_nop_;
}
float AD_get()
{
    static unsigned int i=0;
	static double k=0;
   	while(!(ADC_CONTR&0x10));   		//�ȴ�ת�����
	i=ADC_RES;
	i=i<<2;
	i=i|ADC_RESL;
	//k=i*5.0/1024.0;
	k=i;
	ADC_CONTR=0XC8;
	return k;
}
     






