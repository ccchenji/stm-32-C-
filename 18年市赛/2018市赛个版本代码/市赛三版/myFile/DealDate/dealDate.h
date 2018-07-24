# ifndef _dealDate_H
# define _dealDate_H

typedef struct _node//���ݽڵ�
{
	 int nodeData;//���������
	 int imDegree;//���ݵ���Ҫ�ȼ�
}Node;
typedef struct _lineData
{
   Node line1;//�����ĸ�����,����������,ÿ�������������ֵ�Ĳ�ֵ,�Լ���Ҫϵ��
	 Node line2;
	 Node line3;
	 Node line4;
}lineData;

typedef struct _forData//����������Ҫ�Ե�����
{
	 int data;
	 int flag;
}forData;

extern lineData lineBaseData;//����ֵ

extern lineData lineStoneErr;//ʯͷ
extern lineData lineClothErr;//����
extern lineData lineShearErr;//��

extern lineData lineOneErr;//1�Ĳ�ֵ
extern lineData lineTwoErr;//2�Ĳ�ֵ
extern lineData lineThreeErr;//3�Ĳ�ֵ
extern lineData lineFourErr;//4�Ĳ�ֵ
extern lineData lineFiveErr;//5�Ĳ�ֵ


void InitNode(lineData* data);//���ڵ��ʼ��
void InitLine();//�������߳�ʼ��
lineData giveData(lineData baseData,lineData data);//�õ�ÿ���ߵ����ֵ
void GetData(int flag,lineData data);//�õ�ѵ��������
void GetImtStone(lineData *data1,lineData data2,lineData data3);//���õ��ļ���ʯͷ�������ݽ��д���
int returnErrData(int data,Node allData1,Node allData2,Node allData3);//�õ�һ����·���������(ʯͷ������)
int returnHand(lineData data);

#endif

