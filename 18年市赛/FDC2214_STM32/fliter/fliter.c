#include "fliter.h"

 double bz[3] = {0.097631,0.195262,0.097631};  //����
 double az[3] = {1,-0.942809,0.333333};  //��ĸ
double Data_Output; //������
	int flag=0;
double but_filter( double x)  //lenΪ�����������鳤�ȣ�xΪ������������ָ��
{
  double a=0;
  double b=0;
  double c;
	

	
	if(flag==0)
		{c=x;
		Data_Output=0;	
		}
	if(flag==1)
	{Data_Output=bz[0]*x+bz[1]*c-az[1]*a- az[2]*b;
	
	b=a;
	a=Data_Output;
  c=x;
		
}
  flag=1;
	
	
		


    return (Data_Output); 
}









