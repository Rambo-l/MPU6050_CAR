#include "run.h"
#include "pwm.h"
#include "stm32f10x.h"
#include "usart1.h"	


void motor_Init(void)//����Ӧ��IO�ڽ��г�ʼ��,PA0-3
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��GPIOA��ʱ��

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//���ģʽΪ�����������ƽ�ɸ߿ɵ�
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3;//PA0-3�ܽ�IO��
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//�ܽŴ����ٶ�
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void forward(void)
{
//	TIM_SetCompare2(TIM3,4800);
//	TIM_SetCompare1(TIM4,725);//��Χ(��)200-1250   725���м�
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);//PA2�ߵ�ƽ	     
	GPIO_SetBits(GPIOA,GPIO_Pin_3);//PA1�͵�ƽ  
//	printf("front on!!!");
	
}

void left(void)//�����ת
{
	TIM_SetCompare2(TIM3,4800);
	TIM_SetCompare1(TIM4,400);//��Χ(��)200-1250   725���м�
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);//PA2�ߵ�ƽ	     
	GPIO_SetBits(GPIOA,GPIO_Pin_3);//PA1�͵�ƽ  
	
}

void right(void)//�����ת
{
	TIM_SetCompare2(TIM3,4800);
	TIM_SetCompare1(TIM4,900);//��Χ(��)200-1250   725���м�
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);//PA2�ߵ�ƽ	     
	GPIO_SetBits(GPIOA,GPIO_Pin_3);//PA1�͵�ƽ  
	
}

void back(void)//�����ת
{
	TIM_SetCompare2(TIM3,4800);
	TIM_SetCompare1(TIM4,725);
	GPIO_SetBits(GPIOA,GPIO_Pin_2);//PA2�ߵ�ƽ	     
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);//PA1�͵�ƽ  
	
}
void stop(void)//�����ת
{
	TIM_SetCompare2(TIM3,0);
	TIM_SetCompare1(TIM4,725);
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);//PA2�ߵ�ƽ	     
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);//PA1�͵�ƽ  
	
}

void bale(void)//�����ת
{
	TIM_SetCompare2(TIM3,4800);
	TIM_SetCompare1(TIM4,400);
	GPIO_SetBits(GPIOA,GPIO_Pin_2);//PA2�ߵ�ƽ	     
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);//PA1�͵�ƽ  
	
}

void bari(void)//�����ת
{
	TIM_SetCompare2(TIM3,4800);
	TIM_SetCompare1(TIM4,900);
	GPIO_SetBits(GPIOA,GPIO_Pin_2);//PA2�ߵ�ƽ	     
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);//PA1�͵�ƽ  
	
}
