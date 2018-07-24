#include "dealDate.h"
#include "math.h"
lineData lineBaseData;//基础值

lineData lineStoneErr;//石头
lineData lineClothErr;//布
lineData lineShearErr;//剪刀

lineData lineOneErr;//1的差值
lineData lineTwoErr;//2的差值
lineData lineThreeErr;//3的差值
lineData lineFourErr;//4的差值
lineData lineFiveErr;//5的差值

void InitNode(lineData* data)//将节点初始化
{
	 data->line1.imDegree=0;
	 data->line1.nodeData=0;
	 data->line2.imDegree=0;
	 data->line2.nodeData=0;
	 data->line3.imDegree=0;
	 data->line3.nodeData=0;
	 data->line4.imDegree=0;
	 data->line4.nodeData=0;	
}
void InitLine()//将数据线初始化
{
	 InitNode(&lineBaseData);
	 InitNode(&lineStoneErr);
	 InitNode(&lineClothErr);
	 InitNode(&lineShearErr);
	 InitNode(&lineOneErr);
	 InitNode(&lineTwoErr);
	 InitNode(&lineThreeErr);
	 InitNode(&lineFourErr);
	 InitNode(&lineFiveErr);
}
lineData giveData(lineData baseData,lineData data)//得到每条线的误差值
{
	 lineData middleData;
	 middleData.line1.nodeData=baseData.line1.nodeData-data.line1.nodeData;
	 middleData.line2.nodeData=baseData.line2.nodeData-data.line2.nodeData;
	 middleData.line3.nodeData=baseData.line3.nodeData-data.line3.nodeData;
	 middleData.line4.nodeData=baseData.line4.nodeData-data.line4.nodeData;
	 middleData.line1.imDegree=0;
	 middleData.line2.imDegree=0;
	 middleData.line3.imDegree=0;
	 middleData.line4.imDegree=0;
	 return middleData;
}
void GetData(int flag,lineData data)//得到训练的数据
{
	 if(flag>0)
	 {
	    switch(flag)
			{
				case 1:lineBaseData=data;break;
				case 2:lineStoneErr=giveData(lineBaseData,data);break;
				case 3:lineClothErr=giveData(lineBaseData,data);break;
				case 4:lineShearErr=giveData(lineBaseData,data);break;
				case 5:lineOneErr=giveData(lineBaseData,data);break;
				case 6:lineTwoErr=giveData(lineBaseData,data);break;
				case 7:lineThreeErr=giveData(lineBaseData,data);break;
			  case 8:lineFourErr=giveData(lineBaseData,data);break;
				case 9:lineFiveErr=giveData(lineBaseData,data);break;
				default:
				       break;
			}				
	 }
}
void GetImtStone(lineData *data1,lineData data2,lineData data3)//将得到的石头剪刀布的数据进行处理
{
	 int i=0,j=0;
	 forData data[4];
	 forData middleData;
   data[0].data=abs(data1->line1.nodeData-data2.line1.nodeData)+abs(data1->line1.nodeData-data3.line1.nodeData);
	 data[0].flag=1;
	 data[1].data=abs(data1->line2.nodeData-data2.line2.nodeData)+abs(data1->line1.nodeData-data3.line2.nodeData);
	 data[1].flag=2;
	 data[2].data=abs(data1->line3.nodeData-data2.line3.nodeData)+abs(data1->line1.nodeData-data3.line3.nodeData);
	 data[2].flag=3;
	 data[3].data=abs(data1->line4.nodeData-data2.line4.nodeData)+abs(data1->line1.nodeData-data3.line4.nodeData);
	 data[3].flag=4;
	 for(i=0;i<3;i++)//冒泡排序升序
	 {
		  for(j=0;j<3-i;j++)
			{
				 if(data[j].data>data[j+1].data)
				 {
					  middleData.data=data[j+1].data;
					  middleData.flag=data[j+1].flag;
					  data[j+1].data=data[j].data;
					  data[j+1].flag=data[j].flag;
					  data[j].data=middleData.data;
					  data[j].flag=middleData.flag;
				 }
			}
	 }
	 for(i=0;i<4;i++)//给出数据的重要性评估,越大说明越准确
	 {
		 switch(data[i].flag)
		 {
			 case 1:data1->line1.imDegree=i+1;break;
			 case 2:data1->line2.imDegree=i+1;break;
			 case 3:data1->line3.imDegree=i+1;break;
			 case 4:data1->line4.imDegree=i+1;break;
			 default:
				      break;
		 }
	 }
}
int returnErrData(int data,Node allData1,Node allData2,Node allData3)//得到一个线路的评估结果(石头剪刀布)
{
	 int i=0,j=0;
	 forData dataErr[4];
	 forData middleDate; 
	 dataErr[0].data=abs(data-0);dataErr[0].flag=0;//得到和基础值的差值
	 dataErr[1].data=abs(data-allData1.nodeData);dataErr[1].flag=1;//得到石头和基础值的差值
	 dataErr[2].data=abs(data-allData2.nodeData);dataErr[2].flag=2;//得到和布的差值
	 dataErr[3].data=abs(data-allData3.nodeData);dataErr[3].flag=3;//得到和剪刀的差值
	 for(i=0;i<3;i++)//冒泡排序得到最接近的值
	 {
		 for(j=0;j<3-i;j++)
		 {
			  if(dataErr[j].data>dataErr[j+1].data)
				{
					 middleDate.data=dataErr[j+1].data;
					 middleDate.flag=dataErr[j+1].flag;
					 dataErr[j+1].data=dataErr[j].data;
					 dataErr[j+1].flag=dataErr[j].flag;
					 dataErr[j].data=middleDate.data;
					 dataErr[j].flag=middleDate.flag;
				}
		 }
	 }
	 return dataErr[0].flag;
}

/*---------------------------评估结果---------------------------------------*/
//0 :nothing
//1 :石头
//2 :布
//3 :剪刀
int returnHand(lineData data)
{
	 int i=0;
	 lineData middleData;
	 int endDate[4];
	 float isStone=0,isCloth=0,isShear=0;//个个结果的比例
/*---------------------------得到和基础值的误差值------------------------------*/
	 middleData.line1.nodeData=lineBaseData.line1.nodeData-data.line1.nodeData;
	 middleData.line2.nodeData=lineBaseData.line2.nodeData-data.line2.nodeData;
	 middleData.line3.nodeData=lineBaseData.line3.nodeData-data.line3.nodeData;
	 middleData.line4.nodeData=lineBaseData.line4.nodeData-data.line4.nodeData;	 
	 endDate[0]=returnErrData(middleData.line1.nodeData,lineStoneErr.line1,lineClothErr.line1,lineShearErr.line1);//通过线1得到的结果
	 endDate[1]=returnErrData(middleData.line2.nodeData,lineStoneErr.line2,lineClothErr.line2,lineShearErr.line2);//通过线2得到的结果
	 endDate[2]=returnErrData(middleData.line3.nodeData,lineStoneErr.line3,lineClothErr.line3,lineShearErr.line3);//通过线3得到的结果
	 endDate[3]=returnErrData(middleData.line4.nodeData,lineStoneErr.line4,lineClothErr.line4,lineShearErr.line4);//通过线4得到的结果
	 if(endDate[0]==0&&endDate[1]==0&&endDate[2]==0&&endDate[3]==0)
	 {
		  return 0;//如果全为零则说明没有手放上去
	 }
	 if(endDate[0]==1)//得到线一上的数据评估
	 {
		  isStone+=lineStoneErr.line1.imDegree/10;
	 }else if(endDate[0]==2)
	 {
		  isCloth+=lineClothErr.line1.imDegree/10;
	 }else if(endDate[0]==3)
	 {
		  isShear+=lineShearErr.line1.imDegree/10;
	 }
	 
	 
	 
	 if(endDate[1]==1)//得到线二上的数据评估
	 {
		  isStone+=lineStoneErr.line2.imDegree/10;
	 }else if(endDate[1]==2)
	 {
		  isCloth+=lineClothErr.line2.imDegree/10;
	 }else if(endDate[1]==3)
	 {
		  isShear+=lineShearErr.line2.imDegree/10;
	 }
	 	 	 
	 if(endDate[2]==1)//得到线三上的数据评估
	 {
		  isStone+=lineStoneErr.line3.imDegree/10;
	 }else if(endDate[2]==2)
	 {
		  isCloth+=lineClothErr.line3.imDegree/10;
	 }else if(endDate[2]==3)
	 {
		  isShear+=lineShearErr.line3.imDegree/10;
	 }
	 
	 if(endDate[3]==1)//得到线四上的数据评估
	 {
		  isStone+=lineStoneErr.line4.imDegree/10;
	 }else if(endDate[3]==2)
	 {
		  isCloth+=lineClothErr.line4.imDegree/10;
	 }else if(endDate[3]==3)
	 {
		  isShear+=lineShearErr.line4.imDegree/10;
	 }
	 if(isStone>isCloth)
	 {
		  if(isStone>isShear)
			{
				 return 1;
			}
			else
			{
				 return 3;
			}
	 }
	 else
	 {
		  if(isCloth>isShear)
			{
				return 2;
			}
			else
			{
				return 3;
			}
	 }
}






