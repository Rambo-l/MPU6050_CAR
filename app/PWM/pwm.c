#include "pwm.h"
 
void PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;			//定义GPIO结构体
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;		//定义TIMx定时器结构体
	TIM_OCInitTypeDef TIM_OCInitStructure;			 //定义定时器脉宽调制结构体
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);						 //使能TIM3时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);//使能GPIOB时钟和AFIO复用时钟
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);						//TIM3部分重映射 TIM3_CH2->PB5
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;								//TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 						//复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;						 //配置输出速率
	GPIO_Init(GPIOB,&GPIO_InitStructure);									//初始化GPIOB

	TIM_TimeBaseStructure.TIM_Period = arr;									//设置自动重装载寄存器周期的值 arr=value-1
	TIM_TimeBaseStructure.TIM_Prescaler = psc;								//设置预分频值 psc=value-1
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;							//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;				//TIM向上计数模式
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure); 							//初始化TIMx时间基数

	//初始化TIM3 Channel2 PWM模式??? ?
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;						//选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;			//使能比较输出
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;				//输出极性:TIM输出比较极性高
	TIM_OC2Init(TIM3,&TIM_OCInitStructure); 								//根据T指定的参数初始化外设TIM3 OC2
 
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);						//使能TIM3在CCR2上的预装载寄存器
	TIM_Cmd(TIM3, ENABLE);													//使能TIM3
}

/***********控制舵机的pwm输出***********/
void TIM4_PWM_Init(u16 arr,u16 psc)//在主函数main中传入arr和psc的数值
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  //定时器TIM结构体定义
	TIM_OCInitTypeDef  TIM_OCInitStructure;  //定时器TIM通道结构体定义，每个定时器有四个通道

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);// 使能定时器四的时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能GPIO B的时钟 
	                                                    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//PB6管脚的初始化，管脚对应复用功能：TIM4_CH1(定时器四的通道一)
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //因为要用到管脚的复用功能，所以这里是管脚模式是复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//PB6
	
	
	TIM_TimeBaseStructure.TIM_Period = arr;//; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc;//设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的相应模式配置

  
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse =0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化TIM4_CH1定时器四的通道一
         
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);//使能TIM4在 CCR1 上的预装载寄存器

  TIM_Cmd(TIM4, ENABLE);  //开启TIM4
  }

  


