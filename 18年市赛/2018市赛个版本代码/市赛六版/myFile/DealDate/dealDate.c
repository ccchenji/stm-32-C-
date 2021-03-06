#include "dealDate.h"
#include "math.h"
structData tBaseData;//基础值

structData tStoneErr;//石头的差值
structData tClothErr;//布的差值
structData tShearErr;//剪刀的差值

structData tOneErr;//1的差值
structData tTwoErr;//2的差值
structData tThreeErr;//3的差值
structData tFourErr;//4的差值
structData tFiveErr;//5的差值


int allStoneErr=0;//两个石头加和的差值
int allClothErr=0;//两个布加和的差值
int allShearErr=0;//两个剪刀加和的差值

int allOneErr=0;
int allTwoErr=0;
int allThreeErr=0;
int allFourErr=0;
int allFiveErr=0;

void InitData()//将数据初始化
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
structData getData(structData baseData,structData data)//得到每一路的误差值
{
	 structData middleData;
	 middleData.data1=abs(baseData.data1-data.data1);
	 middleData.data2=abs(baseData.data2-data.data2);
	 return middleData;
}
void GetData(int flag,structData data)//得到训练的数据
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
/*-----------------------判断石头剪刀布-----------------------------*/
int handMode(structData data)
{
	 structData errData;
	 int allErrData=0,i=0,j=0;
	 structData middleData[4];
	 structData tempData;//中间变量
	
	 errData.data1=abs(tBaseData.data1-data.data1);
	 errData.data2=abs(tBaseData.data2-data.data2);
	
	 allErrData=errData.data1+errData.data2;//得到总的误差
	 allStoneErr=tStoneErr.data1+tStoneErr.data2;//得到石头的总的误差
	 allClothErr=tClothErr.data1+tClothErr.data2;//得到布的总的误差
	 allShearErr=tShearErr.data1+tShearErr.data2;//得到剪刀的总的误差
	
	 middleData[0].data1=abs(allErrData-0);middleData[0].data2=0;
	 middleData[1].data1=abs(allErrData-allStoneErr);middleData[1].data2=1;
	 middleData[2].data1=abs(allErrData-allClothErr);middleData[2].data2=2;
	 middleData[3].data1=abs(allErrData-allShearErr);middleData[3].data2=3;
	 for(i=0;i<3;i++)//冒泡排序升序
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
	 }//---------->到此可以判断出布和其他两种的区别
	 if(middleData[0].data2==2||middleData[0].data2==0)
	 {
		  return middleData[0].data2;
	 }
	 else//---------->进一步判断石头和剪刀的区别
	 {
		   if(abs(errData.data1-tShearErr.data1)<abs(errData.data1-tStoneErr.data1))//此时说明是剪刀
			 {
				  return 3;
			 }
			 else
			 {
				  return 1;
			 }
	 }
}
/*---------------------------------判断12345----------------------------------*/
//判断12345只用一个通道就行
int numMode(structData data)
{
	int i = 0, j = 0;
	int errData1 = tBaseData.data1 - data.data1;//得到当前1线的差值
	int errData2 = tBaseData.data2 - data.data2;//得到当前2线的差值
 	structData errDataAll[2][6];
	structData baseData;//中间变量
	errDataAll[0][0].data1 = abs(errData1 - 0); errDataAll[0][0].data2 = 0;//得到与基础值的差值
	errDataAll[0][1].data1 = abs(errData1 - tOneErr.data1); errDataAll[0][1].data2 = 1;//得到与1的差值
	errDataAll[0][2].data1 = abs(errData1 - tTwoErr.data1); errDataAll[0][2].data2 = 2;//得到与2的差值
	errDataAll[0][3].data1 = abs(errData1 - tThreeErr.data1); errDataAll[0][3].data2 = 3;//得到与3的差值
	errDataAll[0][4].data1 = abs(errData1 - tFourErr.data1); errDataAll[0][4].data2 = 4;//得到与4的差值
	errDataAll[0][5].data1 = abs(errData1 - tFiveErr.data1); errDataAll[0][5].data2 = 5;//得到与5的差值
	
	errDataAll[1][0].data1 = abs(errData2 - 0); errDataAll[1][0].data2 = 0;//得到与基础值的差值
	errDataAll[1][1].data1 = abs(errData2 - tOneErr.data2); errDataAll[1][1].data2 = 1;//得到与1的差值
	errDataAll[1][2].data1 = abs(errData2 - tTwoErr.data2); errDataAll[1][2].data2 = 2;//得到与2的差值
	errDataAll[1][3].data1 = abs(errData2 - tThreeErr.data2); errDataAll[1][3].data2 = 3;//得到与3的差值
	errDataAll[1][4].data1 = abs(errData2 - tFourErr.data2); errDataAll[1][4].data2 = 4;//得到与4的差值
	errDataAll[1][5].data1 = abs(errData2 - tFiveErr.data2); errDataAll[1][5].data2 = 5;//得到与5的差值
	
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
/*---------------------------------游戏模式-----------------------------------------*/

int forEnd(int flag1,int flag2)//得到游戏结果
{
	 if(flag1==0||flag2==0)
	 {
		  return 0;
	 }
	 else
	 {
		  if(flag1==1)//如果线1是石头
			{
				 if(flag2==1)
				 {
					  return 3;//平局
				 } else if(flag2==2)
				 {
					  return 2;//2板获胜
				 }else if(flag2==3)
				 {
					  return 1;//1板获胜
				 }
			}else if(flag1==2)//布
			{
				 if(flag2==1)
				 {
					  return 1;//1板获胜
				 }else if(flag2==2)
				 {
					  return 3;//平局
				 }else if(flag2==3)
				 {
					  return 2;//2板获胜
				 }
			}else if(flag1==3)//剪刀
			{
				 if(flag2==1)
				 {
					  return 2;//2板获胜
				 }else if(flag2==2)
				 {
					  return 1;//1板获胜
				 }else if(flag2==3)
				 { 
					  return 3;//平局
				 }
			}
	 }
	 return 0;
}

//返回的是游戏结果
//                0:代表无手放上
//                1:代表1板获胜
//                2:代表2板获胜
//                3:代表平局
StructGame gameEnd(structData data)
{
	int i = 0, j = 0;
	int errData1 = tBaseData.data1 - data.data1;//得到当前1线的差值
	int errData2 = tBaseData.data2 - data.data2;//得到当前2线的差值
	StructGame allGame;
 	structData errDataAll[2][4];
	structData baseData;//中间变量
	errDataAll[0][0].data1 = abs(errData1 - 0); errDataAll[0][0].data2 = 0;//得到与基础值的差值
	errDataAll[0][1].data1 = abs(errData1 - tStoneErr.data1); errDataAll[0][1].data2 = 1;//得到与石头的差值
	errDataAll[0][2].data1 = abs(errData1 - tClothErr.data1); errDataAll[0][2].data2 = 2;//得到与布的差值
	errDataAll[0][3].data1 = abs(errData1 - tShearErr.data1); errDataAll[0][3].data2 = 3;//得到与剪刀的差值
	
	errDataAll[1][0].data1 = abs(errData2 - 0); errDataAll[1][0].data2 = 0;//得到与基础值的差值
	errDataAll[1][1].data1 = abs(errData2 - tStoneErr.data2); errDataAll[1][1].data2 = 1;//得到与石头的差值
	errDataAll[1][2].data1 = abs(errData2 - tClothErr.data2); errDataAll[1][2].data2 = 2;//得到与布的差值
	errDataAll[1][3].data1 = abs(errData2 - tShearErr.data2); errDataAll[1][3].data2 = 3;//得到与剪刀的差值
	
	for (i = 0; i < 3; i++)//冒泡排序法
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


