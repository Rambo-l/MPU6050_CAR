#include "sys.h"
#include "delay.h"
#include "usart1.h"	
#include "usart2.h"
#include "usart3.h"
#include "soft_timer.h"
#include "multi_button.h"
#include "mpu6050.h"
#include "mpu6050_dmp.h"
#include "tim_tim.h"
#include "pid.h"
#include "pwm.h"
#include "run.h"
 
#define MPU6050_DMP_OPEN  1  //�Ƿ���dmp 0:�ر� 1:����  ����ֻ�ܶ�ԭʼ����û�Ӵ���

int error=0;
int a=0;
//���ڼ���printf��sys.c�����ã�Ĭ�ϴ���1����printf 
int main()
{	
	delay_init();
	USART1_Init(115200);
	MPU6050_DMP_Init();
	motor_Init();
	TIM4_PWM_Init(19999,71);//������٣�m��Χ(��)200-1250   725���м�
	TIM2_Time_Init(99,7199);//10ms
	PWM_Init(7199,0);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	
	while(1)
	{
		
		error=Yaw;
		//printf("error is:%d\r\n",error);
		if((error>20)||(error< -20)){
				a=3;  						 //ƫ��Ƕȹ���ͼ���
//				OLED_CLS();
//				OLED_DrawBMP(0,0,64,8,BMP3);
//				OLED_ShowStr(70,3,"Slowing",2);
			}
			else{
				a=2.5;
//				OLED_CLS();
//				OLED_DrawBMP(0,0,64,8,BMP3);
//				OLED_ShowStr(70,3,"Running",2);
			}
		pid_control();	
		forward();
		
		
	}
	
	
	

//#if MPU6050_DMP_OPEN==0//ֻ��mpu6050.c mpu6050.h mpu6050_io_iic.c mpu6050_io_iic.h �ĸ��ļ�����ʵ��ֻ��ԭʼ����
//	  MPU6050_Test();
//#endif
//#if MPU6050_DMP_OPEN==1 //ȫ���ļ����ÿ��������dmp
//	  MPU6050_DMP_Test();
//#endif

	
	
}

