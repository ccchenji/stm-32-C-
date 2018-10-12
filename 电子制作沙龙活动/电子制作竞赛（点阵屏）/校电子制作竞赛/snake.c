#include "Snake.h"
#include "Picture.h"
sbit Key1=P2^1;//上
sbit Key2=P2^0;//左
sbit Key3=P3^2;//右
sbit Key4=P3^3;//下
extern int timer;
int seed=0;
int time=0;

short len=1; 

short x=1;
short y=1;

short ch =0;

short snake_x [10]={1};
short snake_y [10]={1};

short food_x=4;
short food_y=4;


short flag_x_go=1;
short flag_x_bank=0;
short flag_y_go=0;
short flag_y_bank=0; 
 
void My_Snake()
{
	   DrawPoint(food_x,food_y);
	   snake_run();
	   snake_nature();
		 if(live_or_die())
	    {
				 flag_x_go=1;
         flag_x_bank=0;
         flag_y_go=0;
         flag_y_bank=0; 
	    	 x=1;
         y=1;
         len=1;
		  }
}

//获得蛇的食物
void foods()
{
    int i=0;
	  srand(seed);
		food_x=rand()%8+1;
		food_y=rand()%8+1;
		DrawPoint(food_x,food_y);
  for(i=0;i<len;i++)
  {
  	  if((food_x==snake_x[i])&&(food_y==snake_y[i]))
  	  {
  	  	food_x=rand()%8+1;
		    food_y=rand()%8+1;
        i=-1;
	    }
  }
} 

//判断蛇是否死亡
int live_or_die()
{
	 short i=0;
	 if(len>5)
	 {
   for(i=1;i<len-1;i++)
   {
   	  if(((x==snake_x[i])&&(y==snake_y[i])))
   	  {
       return 1;
	    }
   }
   }
   if(x==0||x==9||y==0||y==9)
   {
       return 1;
   }
   return 0;
} 

//蛇的属性
void snake_nature()
{
   int i=0;
   if((x==food_x)&&(y==food_y))
   {
		  len++;
   	  foods();
   }
   snake_x[len]=x;
   snake_y[len]=y;
   for(i=0;i<len;i++)
   {
   	 snake_x[i]=snake_x[i+1];
   	 snake_y[i]=snake_y[i+1];
   }
   for(i=0;i<len;i++)
   {
		  DrawPoint(snake_x[i],snake_y[i]);
   }
}

//让蛇自己运动
void snake_run()
{
	 	 Get_flag();
	   if(time>=700)
		 {
	 	 if(flag_x_go==1)
	 	 {
	 	 	x+=1;
		 }
		 if(flag_x_bank==1)
		 {
	 	 	x-=1;
		 }
		 if(flag_y_go==1)
		 {
	 	 	y+=1;
		 }
		 if(flag_y_bank==1)
		 {
	 	 	y-=1;
		 }
		 time=0;
	  }

} 

void Get_flag()
{
	 if(Key1==0)
	 {
		 delay(1000);
		 if(Key1==0)
		 {
			 ch=80;
		 }
		 while(!Key1);
	 }else
	 if(Key2==0)
	 {
		 delay(1000);
		 if(Key2==0)
		 {
		   ch=77;  
		 } 
      while(!Key2);		 
	 }else
	 if(Key4==0)
	 {
		 delay(1000);
		 if(Key4==0)
		 {
			  ch=72;   
		 } 
		 while(!Key4);
	 }else
	 if(Key3==0)
	 {
		  delay(1000);
		 if(Key3==0)
		 {
			ch=75; 
		 }
     while(!Key3);
	 }
 switch (ch)
	 {
	   case 72:
	 		   if(flag_x_go==1||flag_x_bank==1)
	 		    {
	 		       flag_x_go=0;
	 		       flag_x_bank=0;
	 		   	   flag_y_go=0;
	 		       flag_y_bank=1;
			    }break;

	 	  case 80:
	 		   if(flag_x_go==1||flag_x_bank==1)
	 		    {
	 		       flag_x_go=0;
	 		       flag_x_bank=0;
	 		       flag_y_go=1;
	 		       flag_y_bank=0;
			    }break;
           
	 	   case 75:
         if(flag_y_go==1||flag_y_bank==1)
          {
             flag_x_go=0;
             flag_x_bank=1;
             flag_y_go=0;
             flag_y_bank=0;
				   }break;
	       
	     case 77:
	    	  if(flag_y_go==1||flag_y_bank==1)
	    	   {
	    	     flag_x_go=1;
             flag_x_bank=0;
             flag_y_go=0;
             flag_y_bank=0;
				   }break;
					 
	     default:
	    	    break;
	 }
}
//定时器0的定时器中断
void timer0() interrupt 1
{  
	static int i=0;
  TH0=(65536-1000)/256;	
	TL0=(65536-1000)%256;
	i++;
	time++;
	timer--;
	if(timer<=0)
	{
		 timer=0;
	}
	if(i>=100)
	{
		 seed++;
		 i=0;
		 if(seed>2000)
		 {
			  seed=0;
		 }
	}
}


