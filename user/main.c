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
 
#define MPU6050_DMP_OPEN  1  //是否开启dmp 0:关闭 1:开启  不开只能读原始数据没加处理

int error=0;
int a=0;
//串口几用printf在sys.c中设置，默认串口1可用printf 
int main()
{	
	delay_init();
	USART1_Init(115200);
	MPU6050_DMP_Init();
	motor_Init();
	TIM4_PWM_Init(19999,71);//舵机调速，m范围(左)200-1250   725在中间
	TIM2_Time_Init(99,7199);//10ms
	PWM_Init(7199,0);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	
	while(1)
	{
		
		error=Yaw;
		//printf("error is:%d\r\n",error);
		if((error>20)||(error< -20)){
				a=3;  						 //偏差角度过大就减速
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
	
	
	

//#if MPU6050_DMP_OPEN==0//只用mpu6050.c mpu6050.h mpu6050_io_iic.c mpu6050_io_iic.h 四个文件就能实现只读原始数据
//	  MPU6050_Test();
//#endif
//#if MPU6050_DMP_OPEN==1 //全部文件都用可以用这个dmp
//	  MPU6050_DMP_Test();
//#endif

	
	
}

