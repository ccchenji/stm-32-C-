//1.限幅滤波
//方法：根据经验判断，确定两次采样允许的最大偏差值（设为LIMIT）每次检测到新值时判断：
//        如果本次值与上次值之差 <= LIMIT,则本次值有效如果本次值与上次值之差 > LIMIT,则本次值无效,放弃本次值,用上次值代替本次值
//优点：能有效克服因偶然因素引起的脉冲干扰
//缺点：无法抑制那种周期性的干扰，且平滑度差
#define LIMIT 10;
uint8 AmplitudeLimiterFilter(uint8 oldValue)
{
    uint8 newValue = getValue();
    if( (newValue - oldValue) > LIMIT || (oldValue - newValue) >LIMIT)
    {
        return oldValue;
    }
    else
    {
        return newValue;
    }
}
//注意oldValue的初始值，可以用第一次的采样值
value = getValue();
while(1)
{
    value = AmplitudeLimiterFilter(value);
}


//-----------------------------------------------------------------------
//2.中位值滤波
//方法：连续采样N次（N取奇数）把N次采样值按大小排列取中间值为本次有效值
//优点：能有效克服因偶然因素引起的波动干扰；对温度、液位等变化缓慢的被测参数有良好的滤波效果
//缺点：对流量，速度等快速变化的参数不宜
#define N 9
uint8 middleValueFilter()
{
    uint8 value_buf[N];
    uint8 i,j,k,temp;
    for( i = 0; i < N; ++i)
    {
        value_buf[i] = getValue();
        delay();
    }
    for(j = 0 ; j < N-1; ++j)
    {
        for(k = 0; k < N-j-1; ++k)
        {
            //从小到大排序，冒泡法排序
            if(value_buf[k] > value_buf[k+1])
            {
                temp = value_buf[k];
                value_buf[k] = value_buf[k+1];
                value_buf[k+1] = temp;
            }
        }
    }
    return value_buf[(N-1)/2];
}


//-----------------------------------------------------------------------
//3.算术平均滤波
//方法：连续取N个采样值进行算术平均运算;
//        N值较大时：信号平滑度较高，但灵敏度较低
//        N值较小时：信号平滑度较低，但灵敏度较高
//        N值的选取：一般流量，N=12；压力：N=4
//优点：试用于对一般具有随机干扰的信号进行滤波。
//        这种信号的特点是有一个平均值，信号在某一数值范围附近上下波动。
//缺点：对于测量速度较慢或要求数据计算较快的实时控制不适用。
        
#define N 12
uint8 averageFilter()
{
    uint8 sum = 0;
    int i;
    for(i = 0; i < N; ++i)
    {
        sum += getValue();
        delay();
    }
    return sum/N;
}


//-----------------------------------------------------------------------
//4.递推平均滤波法（又称滑动平均滤波法）
//方法：把连续取N个采样值看成一个队列，队列的长度固定为N
//         每次采样到一个新数(先进先出原则)
//         把队列中的N个数据进行算术平均运算,就可获得新的滤波结据放入队尾,并扔掉原来队首的一次数据果
//         N值的选取：流量，N=12；压力：N=4；液面，N=4~12；温度，N=1~4
//优点：对周期性干扰有良好的抑制作用，平滑度高；试用于高频振荡的系统
//缺点：灵敏度低；对偶然出现的脉冲性干扰的抑制作用较差，不适于脉冲干扰较严重的场合
//        比较浪费RAM（改进方法，减去的不是队首的值， ）    

#define N 20
uint8 value_buf[N];
uint8 moveAverageFilter(uint8 curValue, uint8 *sum, uint8 *curNum)
{
    uint8 i;
    if(*curNum < N)
    {
        value_buf[*curNum] = curValue;
        (*curNum)++;
        sum += curValue;
        retrun (*sum)/(*curNum);
    }
    else
    {
    //每次把后面的值往前移动一位
    /*    sum -= value_buf[0];
        sum += curValue;
        for(i = 1; i < N; ++i)
        {
            value_buf[i-1] = value_buf[i];
        }
        value_buf[N-1] = curValue;
        return (*sum)/N;
    */
    //把新的值放在curNum%N的位置
        sum -= value_buf[*curNum%N];
        sum += curValue;
        value_buf[*curNum%N] = curValue;
        (*curNum)++;
        if(*curNum == 2N) 
        {
            (*curNum) = N;
        }
    }
}    
//减去的值是上次的平均值
uint8 moveAverageFilter(uint8 *sum, uint8 curValue, uint8 num, uint8 *curNum)
{
    if(num <= 0)
    {
        return 0;
    }
    else
    {
        if(*curNum < num)
        {
            ++(*curNum);
            *sum = *sum + curValue;
            return (*sum)/(*curNum);
        }
        else
        {
            *sum = *sum - (*sum)/num;
            *sum = (*sum + curValue);
            return *sum/num;
        }
    }
}


//-----------------------------------------------------------------------
//5.中位值平均滤波（防脉冲干扰平均滤波法）
//方法：相当于“中位值滤波法”+“算术平均滤波法”
//        连续采样N个数据，去掉一个最大值和一个最小值然后计算N-2个数据的算术平均值
//        N值的选取：3~14
//优点：融合了两种滤波的优点。对于偶然出现的脉冲性干扰，可消除有其引起的
//         采样值偏差。对周期干扰有良好的抑制作用，平滑度高，适于高频振荡的系统。
//缺点：测量速度慢
#define N 10
uint8 middleAverageFilter()
{
    uint8 i,j;
    uint8 temp,value,sum = 0;
    uint8 value_buf[N];
    for(i = 0; i < N; ++i)
    {
        value_buf[i] = getValue();
        delay();
    }
    //从小到大冒泡排序
    for(j = 0; j < N-1; ++j)
    {
        for(i = 0; i < N-j-1; ++i)
        {
            if(value_buf[i] > value_buf[i+1])
            {
                temp = value_buf[i];
                value_buf[i] = value_buf[i+1];
                value_buf[i+1] = temp;
            }
        }
    }
    for(i = 1; i < N-1; ++i)
    {
        sum += value_buf[i];
    }
    return sum/(N-2);
}


//-----------------------------------------------------------------------
//6.递推中位值滤波法
// 优点：对于偶然出现的脉冲性干扰，可消除由其引起的采样值偏差。
// 对周期性干扰有良好的抑制作用，平滑度高；
// 试用于高频振荡的系统。
// 缺点：测量速度慢

//取最近的10个值，去掉最大最小值求平均
//队列queue中，第0个值换成新值，其余值依次往后移一个位置
uint8 recursionMiddleFilter(uint8 newValue, uint8 *queue, uint8 num, uint8 *curNum)
{
    uint8 max, min, i;
    queue[0] = newValue;
    max = newValue;
    min = newValue;
    sum = newValue;
    if( *curNum < num)
    {
        for(i = 0; i < *curNum; ++i)
        {
            
    for(i = num-1; i > 0; --i)
    {
        if(queue[i] > max)    
        {    
            max = queue[i];
        }
        else if(queue[i] < min)     
        {
            min = queue[i];
        }
        sum = sum + queue[i];
        queue[i] = queue[i-1];
    ｝
    sum = sum - max - min;
    return sum/num;
}


//-----------------------------------------------------------------------    
//7.限幅平均滤波法
//方法：相当于“限幅滤波法”+“递推平均滤波法”
//        每次采样到的新数据先进行限幅处理再送入队列进行递推平均滤波处理
//优点：对于偶然出现的脉冲性干扰，可消除有其引起的采样值偏差。    
//缺点：比较浪费RAM    
#define A 10
#define N 12
unsigned char data[];
unsigned char filter(data[])
{
  unsigned char i;
  unsigned char value,sum;
  data[N]=GetAD();
  if(((data[N]-data[N-1])>A||((data[N-1]-data[N])>A))
  data[N]=data[N-1];
  //else data[N]=NewValue;
  for(i=0;i<N;i++)
  {
    data[i]=data[i+1];
    sum+=data[i];
  }
  value=sum/N;
  return(value);
}
        
//8.一阶滞后滤波法
//方法：取a=0~1,本次滤波结果=（1-a）*本次采样值+a*上次滤波结果    
//优点：对周期性干扰具有良好的抑制作用适用于波动频率较高的场合
//缺点：相位滞后，灵敏度低滞后程度取决于a值大小不能消除滤波频率高于采样频率的1/2的干扰信号
float a;
uint8 firstOrderFilter(uint8 newValue, uint8 oldValue)
{
    return  a * newValue + (1-a) * oldValue;
}

//使用
value = getValue();
while(1)
{
    value = firstOrderFilter(getValue(),value);
}


//-----------------------------------------------------------------------
//9.加权递推平均滤波法（并没有递推）
//方法：是对递推平均滤波法的改进，即不同时刻的数据加以不同的权；
//        通常是，越接近现时刻的数值，权取得越大；
//        给予新采样值的权系数越大，则灵敏度越高，但信号平滑度越低。                
//优点：适用于有较大纯滞后时间常数的对象和采样周期较短的系统
//缺点：对于纯滞后时间常数较小，采样周期较长
//        变化缓慢的信号不能迅速反应系统当前所受干扰的严重程度，滤波效果差。

#define N 10
uint8 weight[N] = {1,2,3,4,5,6,7,8,9,10};
uint8 weigth_sum = 1+2+1+2+3+4+5+6+7+8+9+10;
uint8 weightAverageFilter()
{
    uint8 value_buf[N];
    uint8 i, sum = 0;
    for(i = 0; i < N; ++i)
    {
        value_buf[i] = getValue();
        delay();
    }
    for(i = 0; i < N; ++i)
    {
        sum += value_buf[i] * weight[i];
    }
    return sum/weight_sum;
}


//-----------------------------------------------------------------------
//10.消抖滤波法
//方法：比如开关，刚按下去的时候会产生抖动，但是经过一段时间后回到稳态；
//        如果N次后，还不是稳态，就取当前值作为新状态值
//        设置一个滤波计数器，将每次采样值与当前有效值比较：
//        如果采样值＝当前有效值，则计数器清零
//        如果采样值<>当前有效值，则计数器+1，并判断计数器是否>=上限N(溢出)
//        如果计数器溢出,则将本次值替换当前有效值,并清计数器
//优点：对于变化缓慢的被测参数有较好的滤波效果,可避免在临界值附近控制器的反复开/关跳动或显示器上数值抖动
//缺点：对于快速变化的参数不宜
//        如果在计数器溢出的那一次采样到的值恰好是干扰值,则会将干扰值当作有效值    

uint8 glitchFilter(uint8 oldValue)
{
    uint8 newValue = getValue();
    uint8 count = 0;
    while(oldValue != newValue)
    {
        count ++;
        if(count >= N)
        {
            return newValue;
        }
        delay();
        newValue = getValue();
    }
    return oldValue;
}


