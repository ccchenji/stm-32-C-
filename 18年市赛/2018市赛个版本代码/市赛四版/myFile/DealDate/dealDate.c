#include "dealDate.h"
#include "math.h"
structData tBaseData;//����ֵ

structData tStoneErr;//ʯͷ�Ĳ�ֵ
structData tClothErr;//���Ĳ�ֵ
structData tShearErr;//�����Ĳ�ֵ

structData tOneErr;//1�Ĳ�ֵ
structData tTwoErr;//2�Ĳ�ֵ
structData tThreeErr;//3�Ĳ�ֵ
structData tFourErr;//4�Ĳ�ֵ
structData tFiveErr;//5�Ĳ�ֵ


int allStoneErr=0;//����ʯͷ�Ӻ͵Ĳ�ֵ
int allClothErr=0;//�������Ӻ͵Ĳ�ֵ
int allShearErr=0;//���������Ӻ͵Ĳ�ֵ

int allOneErr=0;
int allTwoErr=0;
int allThreeErr=0;
int allFourErr=0;
int allFiveErr=0;

void InitData()//�����ݳ�ʼ��
{
   tBaseData.data1=tBaseData.data2=0;
	 tStoneErr.data1=tStoneErr.data2=0;
	 tClothErr.data1=tClothErr.data2=0;
	 tShearErr.data1=tShearErr.data2=0;
	 tOneErr.data1=tOneErr.data2=0;
	 tTwoErr.data1=tTwoErr.data2=0;
	 tThreeErr.data1=tThreeErr.data2=0;
	 tFourErr.data1=tFourErr.data2=0;
	 tFiveErr.data1=tFiveErr.data2=0;
}
structData getData(structData baseData,structData data)//�õ�ÿһ·�����ֵ
{
	 structData middleData;
	 middleData.data1=abs(baseData.data1-data.data1);
	 middleData.data2=abs(baseData.data2-data.data2);
	 return middleData;
}
void GetData(int flag,structData data)//�õ�ѵ��������
{
	 if(flag>0)
	 {
	    switch(flag)
			{
				case 1:tBaseData=data;break;
				case 2:tStoneErr=getData(tBaseData,data);break;
				case 3:tClothErr=getData(tBaseData,data);break;
				case 4:tShearErr=getData(tBaseData,data);break;
				case 5:tOneErr=getData(tBaseData,data);break;
			  case 6:tTwoErr=getData(tBaseData,data);break;
				case 7:tThreeErr=getData(tBaseData,data);break;
				case 8:tFourErr=getData(tBaseData,data);break;
				case 9:tFiveErr=getData(tBaseData,data);break;
				default:
				       break;
			}				
	 }
}
/*-----------------------�ж�ʯͷ������-----------------------------*/
int handMode(structData data)
{
	 structData errData;
	 int allErrData=0,i=0,j=0;
	 structData middleData[4];
	 structData tempData;//�м����
	
	 errData.data1=abs(tBaseData.data1-data.data1);
	 errData.data2=abs(tBaseData.data2-data.data2);
	
	 allErrData=errData.data1+errData.data2;//�õ��ܵ����
	 allStoneErr=tStoneErr.data1+tStoneErr.data2;//�õ�ʯͷ���ܵ����
	 allClothErr=tClothErr.data1+tClothErr.data2;//�õ������ܵ����
	 allShearErr=tShearErr.data1+tShearErr.data2;//�õ��������ܵ����
	
	 middleData[0].data1=abs(allErrData-0);middleData[0].data2=0;
	 middleData[1].data1=abs(allErrData-allStoneErr);middleData[1].data2=1;
	 middleData[2].data1=abs(allErrData-allClothErr);middleData[2].data2=2;
	 middleData[3].data1=abs(allErrData-allShearErr);middleData[3].data2=3;
	 for(i=0;i<3;i++)//ð����������
	 {
		  for(j=0;j<3-i;j++)
			{
				 if(middleData[j].data1>middleData[j+1].data1)
				 {
					  tempData.data1=middleData[j+1].data1;
					  tempData.data2=middleData[j+1].data2;
					  middleData[j+1].data1=middleData[j].data1;
					  middleData[j+1].data2=middleData[j].data2;
					  middleData[j].data1=tempData.data1;
					  middleData[j].data2=tempData.data2;
				 }
			}
	 }//---------->���˿����жϳ������������ֵ�����
	 if(middleData[0].data2==2||middleData[0].data2==0)
	 {
		  return middleData[0].data2;
	 }
	 else//---------->��һ���ж�ʯͷ�ͼ���������
	 {
		   if(abs(errData.data1-tShearErr.data1)<abs(errData.data1-tStoneErr.data1))//��ʱ˵���Ǽ���
			 {
				  return 3;
			 }
			 else
			 {
				  return 1;
			 }
	 }
}
/*---------------------------------�ж�12345----------------------------------*/
//�ж�12345ֻ��һ��ͨ������
int numMode(unsigned int data)
{
	int i = 0, j = 0;
	int errData = tBaseData.data1 - data;//�õ���ǰ�Ĳ�ֵ
	structData errDataAll[6];
	structData baseData;//�м����
	errDataAll[0].data1 = abs(errData - 0); errDataAll[0].data2 = 0;//�õ������ֵ�Ĳ�ֵ
	errDataAll[1].data1 = abs(errData - tOneErr.data1); errDataAll[1].data2 = 1;//�õ���1�Ĳ�ֵ
	errDataAll[2].data1 = abs(errData - tTwoErr.data1); errDataAll[2].data2 = 2;//�õ���2�Ĳ�ֵ
	errDataAll[3].data1 = abs(errData - tThreeErr.data1); errDataAll[3].data2 = 3;//�õ���3�Ĳ�ֵ
	errDataAll[4].data1 = abs(errData - tFourErr.data1); errDataAll[4].data2 = 4;//�õ���4�Ĳ�ֵ
	errDataAll[5].data1 = abs(errData - tFiveErr.data1); errDataAll[5].data2 = 5;//�õ���5�Ĳ�ֵ
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5 - i; j++)
		{
			if (errDataAll[j].data1 > errDataAll[j + 1].data1)
			{
				baseData.data1 = errDataAll[j + 1].data1;
				baseData.data2 = errDataAll[j + 1].data2;
				errDataAll[j + 1].data1 = errDataAll[j].data1;
				errDataAll[j + 1].data2 = errDataAll[j].data2;
				errDataAll[j].data1 = baseData.data1;
				errDataAll[j].data2 = baseData.data2;
			}
		}
	}
	return errDataAll[0].data2;
}



