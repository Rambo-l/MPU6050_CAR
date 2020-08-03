#include "pwm.h"
 
void PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;			//����GPIO�ṹ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;		//����TIMx��ʱ���ṹ��
	TIM_OCInitTypeDef TIM_OCInitStructure;			 //���嶨ʱ��������ƽṹ��
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);						 //ʹ��TIM3ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);//ʹ��GPIOBʱ�Ӻ�AFIO����ʱ��
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);						//TIM3������ӳ�� TIM3_CH2->PB5
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;								//TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 						//�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;						 //�����������
	GPIO_Init(GPIOB,&GPIO_InitStructure);									//��ʼ��GPIOB

	TIM_TimeBaseStructure.TIM_Period = arr;									//�����Զ���װ�ؼĴ������ڵ�ֵ arr=value-1
	TIM_TimeBaseStructure.TIM_Prescaler = psc;								//����Ԥ��Ƶֵ psc=value-1
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;							//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;				//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure); 							//��ʼ��TIMxʱ�����

	//��ʼ��TIM3 Channel2 PWMģʽ??? ?
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;						//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;			//ʹ�ܱȽ����
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;				//�������:TIM����Ƚϼ��Ը�
	TIM_OC2Init(TIM3,&TIM_OCInitStructure); 								//����Tָ���Ĳ�����ʼ������TIM3 OC2
 
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);						//ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
	TIM_Cmd(TIM3, ENABLE);													//ʹ��TIM3
}

/***********���ƶ����pwm���***********/
void TIM4_PWM_Init(u16 arr,u16 psc)//��������main�д���arr��psc����ֵ
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  //��ʱ��TIM�ṹ�嶨��
	TIM_OCInitTypeDef  TIM_OCInitStructure;  //��ʱ��TIMͨ���ṹ�嶨�壬ÿ����ʱ�����ĸ�ͨ��

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);// ʹ�ܶ�ʱ���ĵ�ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��GPIO B��ʱ�� 
	                                                    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//PB6�ܽŵĳ�ʼ�����ܽŶ�Ӧ���ù��ܣ�TIM4_CH1(��ʱ���ĵ�ͨ��һ)
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //��ΪҪ�õ��ܽŵĸ��ù��ܣ����������ǹܽ�ģʽ�Ǹ����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//PB6
	
	
	TIM_TimeBaseStructure.TIM_Period = arr;//; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc;//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx����Ӧģʽ����

  
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse =0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ��TIM4_CH1��ʱ���ĵ�ͨ��һ
         
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);//ʹ��TIM4�� CCR1 �ϵ�Ԥװ�ؼĴ���

  TIM_Cmd(TIM4, ENABLE);  //����TIM4
  }

  


