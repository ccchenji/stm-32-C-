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
int numMode(structData data)
{
	int i = 0, j = 0;
	int errData1 = tBaseData.data1 - data.data1;//�õ���ǰ1�ߵĲ�ֵ
	int errData2 = tBaseData.data2 - data.data2;//�õ���ǰ2�ߵĲ�ֵ
 	structData errDataAll[2][6];
	structData baseData;//�м����
	errDataAll[0][0].data1 = abs(errData1 - 0); errDataAll[0][0].data2 = 0;//�õ������ֵ�Ĳ�ֵ
	errDataAll[0][1].data1 = abs(errData1 - tOneErr.data1); errDataAll[0][1].data2 = 1;//�õ���1�Ĳ�ֵ
	errDataAll[0][2].data1 = abs(errData1 - tTwoErr.data1); errDataAll[0][2].data2 = 2;//�õ���2�Ĳ�ֵ
	errDataAll[0][3].data1 = abs(errData1 - tThreeErr.data1); errDataAll[0][3].data2 = 3;//�õ���3�Ĳ�ֵ
	errDataAll[0][4].data1 = abs(errData1 - tFourErr.data1); errDataAll[0][4].data2 = 4;//�õ���4�Ĳ�ֵ
	errDataAll[0][5].data1 = abs(errData1 - tFiveErr.data1); errDataAll[0][5].data2 = 5;//�õ���5�Ĳ�ֵ
	
	errDataAll[1][0].data1 = abs(errData2 - 0); errDataAll[1][0].data2 = 0;//�õ������ֵ�Ĳ�ֵ
	errDataAll[1][1].data1 = abs(errData2 - tOneErr.data2); errDataAll[1][1].data2 = 1;//�õ���1�Ĳ�ֵ
	errDataAll[1][2].data1 = abs(errData2 - tTwoErr.data2); errDataAll[1][2].data2 = 2;//�õ���2�Ĳ�ֵ
	errDataAll[1][3].data1 = abs(errData2 - tThreeErr.data2); errDataAll[1][3].data2 = 3;//�õ���3�Ĳ�ֵ
	errDataAll[1][4].data1 = abs(errData2 - tFourErr.data2); errDataAll[1][4].data2 = 4;//�õ���4�Ĳ�ֵ
	errDataAll[1][5].data1 = abs(errData2 - tFiveErr.data2); errDataAll[1][5].data2 = 5;//�õ���5�Ĳ�ֵ
	
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5 - i; j++)
		{
			if (errDataAll[0][j].data1 > errDataAll[0][j + 1].data1)
			{
				baseData.data1 = errDataAll[0][j + 1].data1;
				baseData.data2 = errDataAll[0][j + 1].data2;
				errDataAll[0][j + 1].data1 = errDataAll[0][j].data1;
				errDataAll[0][j + 1].data2 = errDataAll[0][j].data2;
				errDataAll[0][j].data1 = baseData.data1;
				errDataAll[0][j].data2 = baseData.data2;
			}
      if (errDataAll[1][j].data1 > errDataAll[1][j + 1].data1)
			{
				baseData.data1 = errDataAll[1][j + 1].data1;
				baseData.data2 = errDataAll[1][j + 1].data2;
				errDataAll[1][j + 1].data1 = errDataAll[1][j].data1;
				errDataAll[1][j + 1].data2 = errDataAll[1][j].data2;
				errDataAll[1][j].data1 = baseData.data1;
				errDataAll[1][j].data2 = baseData.data2;
			}
		}
	}
	if(errDataAll[1][0].data2==5)
	{
		 return 5;
	}
	return errDataAll[0][0].data2;
}
/*---------------------------------��Ϸģʽ-----------------------------------------*/

int forEnd(int flag1,int flag2)//�õ���Ϸ���
{
	 if(flag1==0||flag2==0)
	 {
		  return 0;
	 }
	 else
	 {
		  if(flag1==1)//�����1��ʯͷ
			{
				 if(flag2==1)
				 {
					  return 3;//ƽ��
				 } else if(flag2==2)
				 {
					  return 2;//2���ʤ
				 }else if(flag2==3)
				 {
					  return 1;//1���ʤ
				 }
			}else if(flag1==2)//��
			{
				 if(flag2==1)
				 {
					  return 1;//1���ʤ
				 }else if(flag2==2)
				 {
					  return 3;//ƽ��
				 }else if(flag2==3)
				 {
					  return 2;//2���ʤ
				 }
			}else if(flag1==3)//����
			{
				 if(flag2==1)
				 {
					  return 2;//2���ʤ
				 }else if(flag2==2)
				 {
					  return 1;//1���ʤ
				 }else if(flag2==3)
				 { 
					  return 3;//ƽ��
				 }
			}
	 }
	 return 0;
}

//���ص�����Ϸ���
//                0:�������ַ���
//                1:����1���ʤ
//                2:����2���ʤ
//                3:����ƽ��
StructGame gameEnd(structData data)
{
	int i = 0, j = 0;
	int errData1 = tBaseData.data1 - data.data1;//�õ���ǰ1�ߵĲ�ֵ
	int errData2 = tBaseData.data2 - data.data2;//�õ���ǰ2�ߵĲ�ֵ
	StructGame allGame;
 	structData errDataAll[2][4];
	structData baseData;//�м����
	errDataAll[0][0].data1 = abs(errData1 - 0); errDataAll[0][0].data2 = 0;//�õ������ֵ�Ĳ�ֵ
	errDataAll[0][1].data1 = abs(errData1 - tStoneErr.data1); errDataAll[0][1].data2 = 1;//�õ���ʯͷ�Ĳ�ֵ
	errDataAll[0][2].data1 = abs(errData1 - tClothErr.data1); errDataAll[0][2].data2 = 2;//�õ��벼�Ĳ�ֵ
	errDataAll[0][3].data1 = abs(errData1 - tShearErr.data1); errDataAll[0][3].data2 = 3;//�õ�������Ĳ�ֵ
	
	errDataAll[1][0].data1 = abs(errData2 - 0); errDataAll[1][0].data2 = 0;//�õ������ֵ�Ĳ�ֵ
	errDataAll[1][1].data1 = abs(errData2 - tStoneErr.data2); errDataAll[1][1].data2 = 1;//�õ���ʯͷ�Ĳ�ֵ
	errDataAll[1][2].data1 = abs(errData2 - tClothErr.data2); errDataAll[1][2].data2 = 2;//�õ��벼�Ĳ�ֵ
	errDataAll[1][3].data1 = abs(errData2 - tShearErr.data2); errDataAll[1][3].data2 = 3;//�õ�������Ĳ�ֵ
	
	for (i = 0; i < 3; i++)//ð������
	{
		for (j = 0; j < 3 - i; j++)
		{
			if (errDataAll[0][j].data1 > errDataAll[0][j + 1].data1)
			{
				baseData.data1 = errDataAll[0][j + 1].data1;
				baseData.data2 = errDataAll[0][j + 1].data2;
				errDataAll[0][j + 1].data1 = errDataAll[0][j].data1;
				errDataAll[0][j + 1].data2 = errDataAll[0][j].data2;
				errDataAll[0][j].data1 = baseData.data1;
				errDataAll[0][j].data2 = baseData.data2;
			}
      if (errDataAll[1][j].data1 > errDataAll[1][j + 1].data1)
			{
				baseData.data1 = errDataAll[1][j + 1].data1;
				baseData.data2 = errDataAll[1][j + 1].data2;
				errDataAll[1][j + 1].data1 = errDataAll[1][j].data1;
				errDataAll[1][j + 1].data2 = errDataAll[1][j].data2;
				errDataAll[1][j].data1 = baseData.data1;
				errDataAll[1][j].data2 = baseData.data2;
			}
		}
	}
	allGame.line1=errDataAll[0][0].data2;
	allGame.line2=errDataAll[1][0].data2;
	allGame.end=forEnd(errDataAll[0][0].data2,errDataAll[1][0].data2);
	return allGame;
}


