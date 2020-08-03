#include "run.h"
#include "pwm.h"
#include "stm32f10x.h"
#include "usart1.h"	


void motor_Init(void)//对相应的IO口进行初始化,PA0-3
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能GPIOA的时钟

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//输出模式为推挽输出，电平可高可低
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3;//PA0-3管脚IO口
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//管脚传输速度
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void forward(void)
{
//	TIM_SetCompare2(TIM3,4800);
//	TIM_SetCompare1(TIM4,725);//范围(左)200-1250   725在中间
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);//PA2高电平	     
	GPIO_SetBits(GPIOA,GPIO_Pin_3);//PA1低电平  
//	printf("front on!!!");
	
}

void left(void)//电机正转
{
	TIM_SetCompare2(TIM3,4800);
	TIM_SetCompare1(TIM4,400);//范围(左)200-1250   725在中间
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);//PA2高电平	     
	GPIO_SetBits(GPIOA,GPIO_Pin_3);//PA1低电平  
	
}

void right(void)//电机正转
{
	TIM_SetCompare2(TIM3,4800);
	TIM_SetCompare1(TIM4,900);//范围(左)200-1250   725在中间
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);//PA2高电平	     
	GPIO_SetBits(GPIOA,GPIO_Pin_3);//PA1低电平  
	
}

void back(void)//电机反转
{
	TIM_SetCompare2(TIM3,4800);
	TIM_SetCompare1(TIM4,725);
	GPIO_SetBits(GPIOA,GPIO_Pin_2);//PA2高电平	     
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);//PA1低电平  
	
}
void stop(void)//电机反转
{
	TIM_SetCompare2(TIM3,0);
	TIM_SetCompare1(TIM4,725);
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);//PA2高电平	     
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);//PA1低电平  
	
}

void bale(void)//电机反转
{
	TIM_SetCompare2(TIM3,4800);
	TIM_SetCompare1(TIM4,400);
	GPIO_SetBits(GPIOA,GPIO_Pin_2);//PA2高电平	     
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);//PA1低电平  
	
}

void bari(void)//电机反转
{
	TIM_SetCompare2(TIM3,4800);
	TIM_SetCompare1(TIM4,900);
	GPIO_SetBits(GPIOA,GPIO_Pin_2);//PA2高电平	     
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);//PA1低电平  
	
}
