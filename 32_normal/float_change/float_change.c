#include "float_change.h"
#include "math.h"
char Disp[]={'0','1','2','3','4','5','6','7','8','9'};
unsigned char Disp_save[10]={0};
//���㸡������С��λ��
int float_d(float area)
{
   int n=6;
   long temp=(int)(area*1000000);
   for(n=6;n>0;n--)
   {
        if(0!=temp%10)break;
         temp=temp/10;
   }
   return n; 
}

//���㸡�������������ֵ�λ��
int float_i(float area)
{
   int n=0;
   long temp=(int)area;
   do
   {
   	  n++;
   	  temp/=10;
   }while(temp>0); 
   return n;
}


float float_change(float area)
{
	int digit;    
	int n=0; 
	int a=0;
	float c=0;
	int zxsum=0;
    int zhenshu=0;//�������ֵ�λ��
    int xiaoshu=0;//С�����ֵ�λ��  
    for(n=0;n<10;n++)//���������� 
     {
      Disp_save[n]='\0';
	   }  	
    zhenshu=float_i(area);
    xiaoshu=float_d(area);
    zxsum=zhenshu+xiaoshu;
    c=pow(10,xiaoshu);//��ֹ�������͵�ת�����µ����ݶ�ʧ
    digit=(int)(area*c);
    for(n=0;n<zxsum;n++)
    {
        a=pow(10,zxsum-1-n);
        if(n==zhenshu)
        {
          Disp_save[n]='.';
		}
        if(n>=zhenshu)
       {
        Disp_save[n+1] = Disp[digit/a];
       }
       else
       {
       	 Disp_save[n] = Disp[digit/a];
	   }
        digit=digit-(digit/a)*a;
	}
	return 0;
} 
