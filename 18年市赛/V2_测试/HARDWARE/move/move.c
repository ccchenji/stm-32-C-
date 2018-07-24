#include<move.h>
u32 GROUP=0 ; //1ÎªÒ»¶Ó£¬0Îª¶þ¶Ó
u32 a=600,b=0,c=720,d=540;
void duojiz(u16 dz)  //
	
{
  
	TIM_SetCompare3(TIM4,dz);//B8   500 xia    
	//TIM_SetCompare4(TIM4,b);//B9

}
void duojiy(u16 dy)  //
{
  
	TIM_SetCompare4(TIM4,dy);//B8     520 xia
	//TIM_SetCompare4(TIM4,b);//B9

}
void duojiup(void)
{
if (GROUP==1)
   {duojiz(620);
   duojiy(620);  }//Ò»¶Ó
else
  {duojiz(125);
  duojiy(125); }

}
void doorup(void)
{
TIM_SetCompare2(TIM4,300);

}
void duojidown(void)
{
if (GROUP==1)
  {duojiz(350);
  duojiy(350); } //Ò»¶Ó
else
  {duojiz(490);
	duojiy(490);}

}
void doordown(void)
{
TIM_SetCompare2(TIM4,597);

}
void allahead(u32 allah)  //
{
  TIM_SetCompare1(TIM1,b);//B6             x/1800
	TIM_SetCompare2(TIM1,allah);//B7
	TIM_SetCompare3(TIM1,allah);//B8
	TIM_SetCompare4(TIM1,b);//B9

}
void ahead(u32 ah)   //?±µà?ù?è
{
  TIM_SetCompare1(TIM1,b);//B6    c=720   zuo
	TIM_SetCompare2(TIM1,ah);//B7
	TIM_SetCompare3(TIM1,ah);//B8           you
	TIM_SetCompare4(TIM1,b);//B9

}
void  stop(void)
{
  TIM_SetCompare1(TIM1,0);//B6
	TIM_SetCompare2(TIM1,0);//B7
	TIM_SetCompare3(TIM1,0);//B8
	TIM_SetCompare4(TIM1,0);//B9
}

void back1(void)
{  
	TIM_SetCompare1(TIM1,a);//B6
	TIM_SetCompare2(TIM1,b);//B7
	TIM_SetCompare3(TIM1,b);//B8
	TIM_SetCompare4(TIM1,a);//B9
	delay_ms(1500);
}
void back2(void)
{  
	TIM_SetCompare1(TIM1,a);//B6
	TIM_SetCompare2(TIM1,b);//B7
	TIM_SetCompare3(TIM1,b);//B8
	TIM_SetCompare4(TIM1,a);//B9
	delay_ms(500);
}
void back(u32 zuo,u32  you)
{  
	TIM_SetCompare1(TIM1,zuo);//B6
	TIM_SetCompare2(TIM1,b);//B7     540
	TIM_SetCompare3(TIM1,b);//B8    600
	TIM_SetCompare4(TIM1,you);//B9
	//delay_ms(1500);
}

void diaotou(u32 d)
{ 
	
  TIM_SetCompare1(TIM1,d);//B6
	TIM_SetCompare2(TIM1,b);//B7
	TIM_SetCompare3(TIM1,d);//B8
	TIM_SetCompare4(TIM1,b);//B9
	//delay_ms(1500);

}
void diaotoul(void)  // zuo
{ 
  TIM_SetCompare1(TIM1,d); //B6
	TIM_SetCompare2(TIM1,b); //B7  d=540
	TIM_SetCompare3(TIM1,d); //B8
	TIM_SetCompare4(TIM1,b); //B9
  

}
void diaotour(void)
{ 
  TIM_SetCompare1(TIM1,b);//B6
	TIM_SetCompare2(TIM1,d);//B7  d=540
	TIM_SetCompare3(TIM1,b);//B8
	TIM_SetCompare4(TIM1,d);//B9
  

}
		
void right(u32 r)
{
	 TIM_SetCompare1(TIM1,b);//B6
	TIM_SetCompare2(TIM1,r);//B7
	TIM_SetCompare3(TIM1,b);//B8
	TIM_SetCompare4(TIM1,r);//B9

}
	
void left(u32 l)
{
	 TIM_SetCompare1(TIM1,l);//B6   a=720
	TIM_SetCompare2(TIM1,b);//B7     b=180
	TIM_SetCompare3(TIM1,l);//B8
	TIM_SetCompare4(TIM1,b);//B9
}	

