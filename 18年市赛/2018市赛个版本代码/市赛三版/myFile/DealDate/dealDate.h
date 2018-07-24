# ifndef _dealDate_H
# define _dealDate_H

typedef struct _node//数据节点
{
	 int nodeData;//储存的数据
	 int imDegree;//数据的重要等级
}Node;
typedef struct _lineData
{
   Node line1;//共有四个板子,四条数据线,每条都有其余基础值的差值,以及重要系数
	 Node line2;
	 Node line3;
	 Node line4;
}lineData;

typedef struct _forData//用于数据重要性的排序
{
	 int data;
	 int flag;
}forData;

extern lineData lineBaseData;//基础值

extern lineData lineStoneErr;//石头
extern lineData lineClothErr;//剪刀
extern lineData lineShearErr;//布

extern lineData lineOneErr;//1的差值
extern lineData lineTwoErr;//2的差值
extern lineData lineThreeErr;//3的差值
extern lineData lineFourErr;//4的差值
extern lineData lineFiveErr;//5的差值


void InitNode(lineData* data);//将节点初始化
void InitLine();//将数据线初始化
lineData giveData(lineData baseData,lineData data);//得到每条线的误差值
void GetData(int flag,lineData data);//得到训练的数据
void GetImtStone(lineData *data1,lineData data2,lineData data3);//将得到的剪刀石头布的数据进行处理
int returnErrData(int data,Node allData1,Node allData2,Node allData3);//得到一个线路的评估结果(石头剪刀布)
int returnHand(lineData data);

#endif

