# ifndef _dealDate_H
# define _dealDate_H
typedef struct _data
{
	 int data1;
	 int data2;
}structData;

typedef struct _game
{
	 int line1;
	 int line2;
	 int end;
}StructGame;

extern structData tBaseData;//基础值

extern structData tStoneErr;//石头的差值
extern structData tClothErr;//布的差值
extern structData tShearErr;//剪刀的差值

extern structData tOneErr;//1的差值
extern structData tTwoErr;//2的差值
extern structData tThreeErr;//3的差值
extern structData tFourErr;//4的差值
extern structData tFiveErr;//5的差值


extern int allStoneErr;//两个石头加和的差值
extern int allClothErr;//两个布加和的差值
extern int allShearErr;//两个剪刀加和的差值

extern int allOneErr;
extern int allTwoErr;
extern int allThreeErr;
extern int allFourErr;
extern int allFiveErr;

void InitData(void);//将数据初始化
structData getData(structData baseData,structData data);//得到每一路的误差值
void GetData(int flag,structData data);//得到训练的数据
int handMode(structData data);
int numMode(structData data);
int forEnd(int flag1,int flag2);//得到游戏结果
StructGame gameEnd(structData data);

#endif

