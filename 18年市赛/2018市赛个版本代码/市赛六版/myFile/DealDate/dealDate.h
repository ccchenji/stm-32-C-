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

extern structData tBaseData;//����ֵ

extern structData tStoneErr;//ʯͷ�Ĳ�ֵ
extern structData tClothErr;//���Ĳ�ֵ
extern structData tShearErr;//�����Ĳ�ֵ

extern structData tOneErr;//1�Ĳ�ֵ
extern structData tTwoErr;//2�Ĳ�ֵ
extern structData tThreeErr;//3�Ĳ�ֵ
extern structData tFourErr;//4�Ĳ�ֵ
extern structData tFiveErr;//5�Ĳ�ֵ


extern int allStoneErr;//����ʯͷ�Ӻ͵Ĳ�ֵ
extern int allClothErr;//�������Ӻ͵Ĳ�ֵ
extern int allShearErr;//���������Ӻ͵Ĳ�ֵ

extern int allOneErr;
extern int allTwoErr;
extern int allThreeErr;
extern int allFourErr;
extern int allFiveErr;

void InitData(void);//�����ݳ�ʼ��
structData getData(structData baseData,structData data);//�õ�ÿһ·�����ֵ
void GetData(int flag,structData data);//�õ�ѵ��������
int handMode(structData data);
int numMode(structData data);
int forEnd(int flag1,int flag2);//�õ���Ϸ���
StructGame gameEnd(structData data);

#endif

