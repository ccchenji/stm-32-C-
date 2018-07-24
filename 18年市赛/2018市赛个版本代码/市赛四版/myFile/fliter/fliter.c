#include "fliter.h"

double bz[3] = {0.166667,0.5,0.166667};  //·Ö×Ó
double az[3] = { 1 ,-0.942809,0};  //·ÖÄ¸
double Data_Output; //Êä³öÊı¾
int flag1=0;
double but_filter( double x)  //lenÎªÊäÈëÊı¾İÊı×é³¤¶È£¬xÎªÊäÈëÊı¾İÊı×éÖ¸Õë
{
  double a=0;
  double b=0;
  double c;
	

	
	if(flag1==0)
		{c=x;
		Data_Output=0;	
		}
	if(flag1==1)
	{Data_Output=bz[0]*x+bz[1]*c-az[1]*a- az[2]*b;
	
	b=a;
	a=Data_Output;
  c=x;
		
}
  flag1=1;
	
	
		


    return (Data_Output); 
}

