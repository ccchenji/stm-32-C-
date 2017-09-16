/***************
                
				1          2               3
                4          5               6
				7          8               9
**************/

int want_area = 0;  //want_area = 0 ~9
int now_area = 0;
int need_area = 0;

#define X   0
#define Y   1 
#include<stdio.h>
#include<math.h>
#include "timer.h"
#include "text.h"
extern short SET_DATE[13][2];
int set_area[9][2] = {0};
/*********************************************

				X     Y

			1   
			2
			3
			4  93    32
			5  94    103
			6  
			7
			8
			9  24    176

*****************************************/
int special_area[4][2] = {0};
int aim_area[4][2] = { 0 };
/***************************************
					X       Y
			T1    131       63
			T2
			T3    57        66
			T4    57        142
****************************************/

double square(int a, int b);

void find_way(int now ,int set)
{
	int mix = 0, i,a;
	
 //¸³Öµ
	for(i=0;i<9;i++)
	{
		for(a=0;a<2;a++)
		{
      set_area[i][a]=SET_DATE[i][a];
		}
	}
	for(i=0;i<4;i++)
	{
		 for(a=0;a<2;a++)
		 {
			special_area[i][a]=SET_DATE[i+9][a];
		 }
	}
	set = set - 1;
	
	
	if (square((set_area[set][X] - set_area[now-1][X]),(set_area[set][Y] - set_area[now-1][Y])) < 110)
	{
		aim_area[0][X] = set_area[set][X];
		aim_area[0][Y] = set_area[set][Y];
		need_area = 1;

		
	}
	else
	{
		if (now == 1 || now == 3 || now == 7 || now == 9)
		{
			switch (now)
			{
			case 1: aim_area[0][X] = special_area[0][X];
				aim_area[0][Y] = special_area[0][Y];
				break;
			case 3: aim_area[0][X] = special_area[1][X];
				aim_area[0][Y] = special_area[1][Y];
				break;
			case  7:aim_area[0][X] = special_area[2][X];
				aim_area[0][Y] = special_area[2][Y];
				break;
			case 9:aim_area[0][X] = special_area[3][X];
				aim_area[0][Y] = special_area[3][Y];
				break;
			}
			

			switch (now)
			{
			case 1:
				if (square(special_area[1][X] - set_area[set][X], special_area[1][Y] - set_area[set][Y]) <
					square(special_area[2][X] - set_area[set][X], special_area[2][Y] - set_area[set][Y]))
				{
					aim_area[1][X] = special_area[1][X];
					aim_area[1][Y] = special_area[1][Y];

				}
				else
				{

					aim_area[1][X] = special_area[2][X];
					aim_area[1][Y] = special_area[2][Y];
				}
				break;

			case 3:
				if (square(special_area[0][X] - set_area[set][X], special_area[0][Y] - set_area[set][Y]) <
					square(special_area[3][X] - set_area[set][X], special_area[3][Y] - set_area[set][Y]))
				{
					aim_area[1][X] = special_area[0][X];
					aim_area[1][Y] = special_area[0][Y];

				}
				else
				{

					aim_area[1][X] = special_area[3][X];
					aim_area[1][Y] = special_area[3][Y];
				}
				break;

			case 7:
				if (square(special_area[0][X] - set_area[set][X], special_area[0][Y] - set_area[set][Y]) <
					square(special_area[3][X] - set_area[set][X], special_area[3][Y] - set_area[set][Y]))
				{
					aim_area[1][X] = special_area[0][X];
					aim_area[1][Y] = special_area[0][Y];

				}
				else
				{

					aim_area[1][X] = special_area[3][X];
					aim_area[1][Y] = special_area[3][Y];
				}
				break;

			case 9:
				if (square(special_area[1][X] - set_area[set][X], special_area[1][Y] - set_area[set][Y]) <
					square(special_area[2][X] - set_area[set][X], special_area[2][Y] - set_area[set][Y]))
				{
					aim_area[1][X] = special_area[1][X];
					aim_area[1][Y] = special_area[1][Y];

				}
				else
				{

					aim_area[1][X] = special_area[2][X];
					aim_area[1][Y] = special_area[2][Y];
				}
				break;


			}
			if (square(set_area[set][X] - aim_area[1][X], set_area[set][Y] - aim_area[1][Y]) > 50)
			{
			
				mix = square(set_area[set][X] - special_area[0][X], set_area[set][Y] - special_area[0][Y]);
				aim_area[2][X] = special_area[0][X];
				aim_area[2][Y] = special_area[0][Y];
				for (i = 1; i < 4; i++)
				{
					if (square(set_area[set][X] - special_area[i][X], set_area[set][Y] - special_area[i][Y]) < mix)
					{
						mix = square(set_area[set][X] - special_area[i][X], set_area[set][Y] - special_area[i][Y]);
						aim_area[2][X] = special_area[i][X];
						aim_area[2][Y] = special_area[i][Y];
					}
				}

				aim_area[3][X] = set_area[set][X];
				aim_area[3][Y] = set_area[set][Y];

				need_area = 4;

             }
			else
			{
				aim_area[2][X] = set_area[set][X];
				aim_area[2][Y] = set_area[set][Y];
					need_area = 3;

			}
			


		}
		else if (now == 2 || now == 4 || now == 6 || now == 8)
		{
		
			switch (now)
			{
			case 2:if (square(special_area[0][X] - set_area[set][X], special_area[0][Y] - set_area[set][Y]) <
				square(special_area[1][X] - set_area[set][X], special_area[1][Y] - set_area[set][Y]))
			{
				aim_area[0][X] = special_area[0][X];
				aim_area[0][Y] = special_area[0][Y];
				aim_area[1][X] = special_area[2][X];
				aim_area[1][Y] = special_area[2][Y];

			}
				   else
				   {
					   aim_area[0][X] = special_area[1][X];
					   aim_area[0][Y] = special_area[1][Y];
					   aim_area[1][X] = special_area[3][X];
					   aim_area[1][Y] = special_area[3][Y];
				   
				   }
			
				break;
			
			case 4:if (square(special_area[0][X] - set_area[set][X], special_area[0][Y] - set_area[set][Y]) <
				square(special_area[2][X] - set_area[set][X], special_area[2][Y] - set_area[set][Y]))
			{
				aim_area[0][X] = special_area[0][X];
				aim_area[0][Y] = special_area[0][Y];
				aim_area[1][X] = special_area[1][X];
				aim_area[1][Y] = special_area[1][Y];


			}
				   else
				   {
					   aim_area[0][X] = special_area[2][X];
					   aim_area[0][Y] = special_area[2][Y];
					   aim_area[1][X] = special_area[3][X];
					   aim_area[1][Y] = special_area[3][Y];
				   }

				   break;
		
		case 6:if (square(special_area[1][X] - set_area[set][X], special_area[1][Y] - set_area[set][Y]) <
			       square(special_area[3][X] - set_area[set][X], special_area[3][Y] - set_area[set][Y]))
		{
			aim_area[0][X] = special_area[1][X];
			aim_area[0][Y] = special_area[1][Y];
			aim_area[1][X] = special_area[0][X];
			aim_area[1][Y] = special_area[0][Y];

		}
			   else
			   {
				   aim_area[0][X] = special_area[3][X];
				   aim_area[0][Y] = special_area[3][Y];
				   aim_area[1][X] = special_area[2][X];
				   aim_area[1][Y] = special_area[2][Y];
			   }

			   break;
	
		case 8:
			if (square(special_area[2][X] - set_area[set][X], special_area[2][Y] - set_area[set][Y]) <
		        square(special_area[3][X] - set_area[set][X], special_area[3][Y] - set_area[set][Y]))
	{
		aim_area[0][X] = special_area[2][X];
		aim_area[0][Y] = special_area[2][Y];
		aim_area[1][X] = special_area[0][X];
		aim_area[1][Y] = special_area[0][Y];

	}
		   else
		   {
			   aim_area[0][X] = special_area[3][X];
			   aim_area[0][Y] = special_area[3][Y];
			   aim_area[1][X] = special_area[1][X];
			   aim_area[1][Y] = special_area[1][Y];
		   }

		   break;
	}
		

			aim_area[2][X] = set_area[set][X];
			aim_area[2][Y] = set_area[set][Y];

			need_area = 3;
	
   }
  
 }
}
	
	  
	

double square(int a ,int b)
{
	double result;
	result =  sqrt(a*a + b*b);
	return result;
}

